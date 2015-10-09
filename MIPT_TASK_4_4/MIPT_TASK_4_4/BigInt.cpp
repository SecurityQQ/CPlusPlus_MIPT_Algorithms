//
//  BigInt.cpp
//  MIPT_TASK_4_4
//
//  Created by Александр Малышев on 16.02.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include "BigInt.h"

BigInt operator + (const BigInt &aNumber, const BigInt &aNumber2);
BigInt operator - (const BigInt &aNumber, const BigInt &aNumber2);
BigInt operator * (const BigInt &aNumber, const BigInt &aNumber2);
BigInt operator / (const BigInt &aNumber, const BigInt &aNumber2);
BigInt operator % (const BigInt &aNumber, const BigInt &aNumber2);

BigInt::BigInt() {
    sign = ZERO;
    maxBuf = 0;
    buffer = new uchar;
}

BigInt::BigInt(const long long aNumber) {
    if( aNumber == 0 ) {
        sign = ZERO;
        maxBuf = 1;
        buffer = new uchar[maxBuf];
        buffer[0] = 0;
        return;
    } else {
        if( aNumber < 0 ) {
            sign = NEGATIVE;
        } else {
            sign = POSITIVE;
        }
    }
    long long absNumber = llabs(aNumber);
    uint maxDeg = (uint) (log(absNumber) / log(BUF_SIZE));
    maxBuf = maxDeg + 1;
    maxDeg = (uint) pow(BUF_SIZE, maxDeg);
    buffer = new uchar[maxBuf];
    for( int i = maxBuf - 1; i >= 0; --i ) {
        buffer[i] = absNumber / maxDeg;
        absNumber -= buffer[i] * maxDeg;
        maxDeg /= BUF_SIZE;
    }
    
}
BigInt::BigInt(uchar defVal, uint size) {
    maxBuf = size;
    buffer = new uchar[maxBuf];
    for( int i = 0; i < maxBuf; ++i ) {
        buffer[i] = defVal;
    }
}

BigInt::~BigInt() {
    maxBuf = 0;
    sign = ZERO;
    delete [] buffer;
}


void BigInt::show() const{
    if( sign == ZERO ) {
        printf("0");
    } else {
        for( int i = 0; i < maxBuf - 1; ++i ) {
            printf("%d * 255**%d + ", buffer[i], i);
        }
        printf("%d * 255**%d ", buffer[maxBuf - 1], maxBuf - 1);
        printf("(SIGN: %d )", sign);
    }
}

void BigInt::reverseSign() {
    if( sign == POSITIVE ) {
        sign = NEGATIVE;
    } else {
        if( sign == NEGATIVE ) {
            sign = POSITIVE;
        }
    }
}
void BigInt::reverse() {
    for( int i = 0; i < (maxBuf >> 1); ++i ) {
        std::swap(buffer[i], buffer[maxBuf - i - 1]);
    }
    deleteUnusedZeroes();
}

BigInt::BigInt(const BigInt& aBigNumber) {
    *this = aBigNumber;
}

void BigInt::operator = (const BigInt& aBigNumber) {
    sign = aBigNumber.sign;
    maxBuf = aBigNumber.maxBuf;
    buffer = new uchar[maxBuf];
    memcpy(buffer, aBigNumber.buffer, maxBuf * sizeof(uchar));
}

void BigInt::operator=(const long long aBigNumber) {
    *this = BigInt(aBigNumber);
}

BigInt operator - (const BigInt &aNumber, const BigInt &aNumber2) {
    BigInt difference(0);
    if( aNumber.sign == ZERO ) {
        
        difference = aNumber2;
        difference.reverseSign();
        
        return difference;
    }
    
    if( aNumber2.sign == ZERO ) {
        return aNumber;
    }
    
    compBigInt compareNumbers = aNumber.compTo(aNumber2);
    BigInt lessNumber, moreNumber;
    switch (compareNumbers) {
        case LESS:
            lessNumber = aNumber;
            moreNumber = aNumber2;
            difference = moreNumber;
            difference.sign = NEGATIVE;
            break;
        case MORE:
            lessNumber = aNumber2;
            moreNumber = aNumber;
            difference = moreNumber;
            difference.sign = POSITIVE;
            break;
        case EQUAL:
            return difference;
            break;
        default:
            throw "Unexpected error on operator -";
            break;
    }
    
    if( lessNumber.sign != moreNumber.sign ) {
        BigIntSign difSign = difference.sign;
        lessNumber.reverseSign();
        difference = lessNumber + moreNumber;
        difference.sign = difSign;
        return difference;
    }
    
    bool isTakenDigit = false;
    for( int i = 0; i < moreNumber.maxBuf; ++i ) {
        int digit;
        if( i < lessNumber.maxBuf ) {
            digit = moreNumber.buffer[i] - lessNumber.buffer[i];
        } else {
            digit = moreNumber.buffer[i];
        }
        if( isTakenDigit ) {
            --digit;
        }
        
        if( digit < 0 ) {
            digit += BUF_SIZE;
            isTakenDigit = true;
        } else {
            isTakenDigit = false;
        }
        difference.buffer[i] = digit;
    }
    difference.deleteUnusedZeroes();
    return difference;
}


BigInt operator+ (const BigInt &aNumber, const BigInt &aNumber2) {
    if( aNumber.sign == ZERO ) {
        return aNumber2;
    }
    if( aNumber2.sign == ZERO ) {
        return aNumber;
    }
    
    compBigInt compareNumbers = aNumber.compTo(aNumber2);
    BigInt lessNumber, moreNumber;
    switch (compareNumbers) {
        case LESS:
            lessNumber = aNumber;
            moreNumber = aNumber2;
            break;
        case MORE:
            lessNumber = aNumber2;
            moreNumber = aNumber;
            break;
        case EQUAL:
            break;
        default:
            throw "Unexpected error on operator +";
            break;
    }
    
    if( aNumber.sign != aNumber2.sign ) {
        lessNumber.reverseSign();
        return moreNumber - lessNumber;
    }
    
            
    BigInt summary(0, moreNumber.maxBuf);
    summary.sign = moreNumber.sign;
    uint subBuf = 0;
    int i = 0;
    for( ; i < lessNumber.maxBuf; ++i ) {
        subBuf += moreNumber.buffer[i] + lessNumber.buffer[i];
        summary.buffer[i] = subBuf % BUF_SIZE;
        subBuf /= BUF_SIZE;
    }
    
    for( ; i < moreNumber.maxBuf; ++i ) {
        subBuf += moreNumber.buffer[i];
        summary.buffer[i] = subBuf;
        subBuf /= BUF_SIZE;
    }
    if( subBuf > 0 ) {
        summary.addDigit();
        summary.buffer[summary.maxBuf - 1] = subBuf;
    }
    
   return summary;
}
    
BigInt& BigInt::operator += (const BigInt &aNumber) {
    *this = *this + aNumber;
    return *this;
}
BigInt& BigInt::operator -= (const BigInt &aNumber) {
    *this = *this - aNumber;
    return *this;
}

BigInt& BigInt::operator *= (const BigInt &aNumber) {
    *this = *this * aNumber;
    return *this;
}
BigInt& BigInt::operator /= (const BigInt &aNumber) {
    *this = *this / aNumber;
    return *this;
}

BigInt operator * (const BigInt &aNumber, const BigInt &aNumber2) {
    BigInt product;
    if( aNumber.sign == ZERO || aNumber2.sign == ZERO ) {
        return product;
    }
    if( aNumber.sign == aNumber2.sign ) {
        product.sign = POSITIVE;
    } else {
        product.sign = NEGATIVE;
    }
    compBigInt compareNumbers = aNumber.compTo(aNumber2);
    BigInt lessNumber, moreNumber;
    switch (compareNumbers) {
        case EQUAL:
        case LESS:
            lessNumber = aNumber;
            moreNumber = aNumber2;
            break;
        case MORE:
            lessNumber = aNumber2;
            moreNumber = aNumber;
            break;
        default:
            throw "Unexpected error on operator *";
            break;
    }
    for( int i = 0; i < lessNumber.maxBuf; ++i ) {
        BigInt subProduct(0, lessNumber.maxBuf + moreNumber.maxBuf);
        subProduct.sign = product.sign;
        int nextDigit = 0;
        for( int j = 0; j < moreNumber.maxBuf; ++j ) {
            int subPr = moreNumber.buffer[j] * lessNumber.buffer[i] + nextDigit;
            subProduct.buffer[j + i] += subPr % BUF_SIZE;
            nextDigit = subPr / BUF_SIZE;
        }
        subProduct.buffer[subProduct.maxBuf - 1] = nextDigit;
        subProduct.deleteUnusedZeroes();
        product += subProduct;
        
    }
    
    return product;
}

//returns div on [0] and mod on [1];
BigInt* divideWithRemainder (const BigInt &aNumber, const BigInt &aNumber2) {
    BigInt* result = new BigInt[2];
    
    if( aNumber < aNumber2 ) {
        result[0] = 0;
        result[1] = aNumber;
        return result;
    }
    
    BigInt quotient;
    if( aNumber.sign == ZERO ) {
        result[0] = quotient;
        result[1] = aNumber2;
        return result;
    }
    if( aNumber.sign == aNumber2.sign ) {
        quotient.sign = POSITIVE;
    } else {
        quotient.sign = NEGATIVE;
    }
    
    if( aNumber2.sign == ZERO ) {
        throw "Arithmetical error: dividing by 0";
    }
    
    BigInt subDev(0, aNumber2.maxBuf);
    BigInt intBufSize(BUF_SIZE);
    subDev.sign = POSITIVE;
    
    int i = aNumber.maxBuf - 1;
    for( int j = subDev.maxBuf - 1; j >= 0; --j ) {
        subDev.buffer[j] = aNumber.buffer[i];
        --i;
    }
    if( subDev < aNumber2 ) {
        subDev *= intBufSize;
        subDev.buffer[0] = aNumber.buffer[i];
        --i;
    }
    do {
//        printf("Subdev1: ");
//        subDev.show();
//        printf("\n");
        quotient.addDigit();
        quotient.buffer[quotient.maxBuf - 1] =  searchLargestDigitForDivisor(subDev, aNumber2);
//        printf("dig found: %d\n",         quotient.buffer[quotient.maxBuf - 1]);
        BigInt temp(quotient.buffer[quotient.maxBuf - 1]);
        subDev -= temp * aNumber2;
//        printf("Subdev2: ");
//        subDev.show();
//        printf("\n");
        if( i < 0 ) {
            break;
        }
        subDev *= intBufSize;
//        printf("adding: %d\n", aNumber.buffer[i]);
        subDev += BigInt(aNumber.buffer[i]);
        --i;
//        printf("Subdev3: ");
//        subDev.show();
//        printf("\n");
    } while( i >= -1);
    
    quotient.reverse();
    result[0] = quotient;
    result[1] = subDev;
//    printf("-----------------\n");
//    printf("quotient: "); quotient.show(); printf("\n");
//    printf("-----------------\n");
    return result;
}

BigInt operator / (const BigInt &aNumber, const BigInt &aNumber2) {
    return divideWithRemainder(aNumber, aNumber2)[0];
}

BigInt operator % (const BigInt &aNumber, const BigInt &aNumber2) {
    return divideWithRemainder(aNumber, aNumber2)[1];
}

uchar searchLargestDigitForDivisor(const BigInt &dividend, const BigInt &divisor) {
    uchar digit = 127;
    uchar rightEdge = BUF_SIZE;
    uchar leftEdge = 0;
    BigInt remainder;
    do {
        BigInt subQuotient(digit);
        BigInt checkMul = subQuotient * divisor;
        remainder = dividend - checkMul;
        if( remainder.sign != NEGATIVE && remainder < divisor ) {
            break;
        } else {
            if( checkMul < dividend ) {
                leftEdge = digit;
                digit = ((digit + rightEdge) >> 1);
            } else {
                if( checkMul > dividend ) {
                    rightEdge = digit;
                    digit = ((digit + leftEdge) >> 1);
                } else {
                    break;
                }
            }
        }
//    <# How to do it better?#>
    } while( true );
    return digit;
}

void BigInt::addDigit() {
    maxBuf += 1;
    uchar *newBuf = new uchar[maxBuf];
    memcpy(newBuf, buffer, sizeof(uchar) * (maxBuf - 1));
    delete [] buffer;
    buffer = newBuf;
}

BigInt operator + (const BigInt &aNumber, const long long aNumber2) {
    return aNumber + BigInt(aNumber2);
}
BigInt operator - (const BigInt &aNumber, const long long aNumber2) {
    return aNumber - BigInt(aNumber2);
}
BigInt operator * (const BigInt &aNumber, const long long aNumber2) {
    return aNumber * BigInt(aNumber2);
}
BigInt operator / (const BigInt &aNumber, const long long aNumber2) {
    return aNumber / BigInt(aNumber2);
}
BigInt operator % (const BigInt &aNumber, const long long aNumber2) {
    return aNumber % BigInt(aNumber2);
}


bool   operator <  (const BigInt &aNumber, const BigInt &aNumber2) {
    if( aNumber.compTo(aNumber2) == LESS ) {
        return true;
    }
    return false;
}

bool   operator >  (const BigInt &aNumber, const BigInt &aNumber2) {
    if( aNumber.compTo(aNumber2) == MORE ) {
        return true;
    }
    return false;
}

bool   operator <=  (const BigInt &aNumber, const BigInt &aNumber2) {
    return !operator >(aNumber, aNumber2);
}

bool   operator >=  (const BigInt &aNumber, const BigInt &aNumber2) {
    return !operator <(aNumber, aNumber2);
}

bool   operator ==  (const BigInt &aNumber, const BigInt &aNumber2) {
    if( aNumber.compTo(aNumber2) == EQUAL ) {
        return true;
    }
    return false;
}

bool   operator != (const BigInt &aNumber, const BigInt &aNumber2) {
    return !operator==(aNumber, aNumber2);
}

compBigInt BigInt::compTo(const BigInt &aNumber) const {
    if( sign == POSITIVE && (aNumber.sign == ZERO || aNumber.sign == NEGATIVE )) {
        return MORE;
    }
    if( sign == NEGATIVE && (aNumber.sign == ZERO || aNumber.sign == POSITIVE )) {
        return LESS;
    }
    
    if( sign == POSITIVE && aNumber.sign == POSITIVE ) {
        if( maxBuf < aNumber.maxBuf ) {
            return LESS;
        }
        if( maxBuf > aNumber.maxBuf ) {
            return MORE;
        }
        for( int i = maxBuf - 1; i >= 0; --i ) {
            if( buffer[i] == aNumber.buffer[i] ) {
                continue;
            } else {
                if( buffer[i] < aNumber.buffer[i] ) {
                    return LESS;
                } else {
                    return MORE;
                }
            }
        }
    }
    return EQUAL;
}

std::ostream& operator << (std::ostream &stream, const BigInt &aNumber) {
    BigInt temp(aNumber);
    std::string numFormatedByString;
    while( temp != 0 ) {
        int ch = (temp % 10).buffer[0];
        temp /= 10;
        numFormatedByString.push_back(ch + '0');
    }
    for( int i = 0; i < numFormatedByString.size() / 2; ++i ) {
        std::swap(numFormatedByString[i], numFormatedByString[numFormatedByString.size() - i - 1]);
    }
    stream << numFormatedByString;
    return stream;
}

std::istream& operator >> (std::istream &stream, BigInt &aNumber) {
    BigInt numberFromStream(0);
    std::string numFormatedByString;
    stream >> numFormatedByString;
    
    for( long long i = 0; i < numFormatedByString.size() - 1; ++i ) {
        if( numFormatedByString[i] > '9' || numFormatedByString[i] < '0' ) {
            throw "Incorrect input for BigInt";
        }
        numberFromStream += (numFormatedByString[i] - '0');
        numberFromStream *= 10;
    }
    numberFromStream += (numFormatedByString[numFormatedByString.size() - 1] - '0');
    aNumber = numberFromStream;
    return stream;
}


void BigInt::deleteUnusedZeroes() {
    BigInt zeroInt(0);
    while( buffer[maxBuf - 1] == 0 && maxBuf > 0) {
        --maxBuf;
        if( maxBuf == 0) {
            *this = zeroInt;
            return;
        }
    }
    uchar *newBuf = new uchar[maxBuf];
    memcpy(newBuf, buffer, sizeof(uchar) * maxBuf);
    delete [] buffer;
    buffer = newBuf;
}
