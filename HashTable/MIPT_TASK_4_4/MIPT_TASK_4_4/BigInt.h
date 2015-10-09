//
//  BigInt.h
//  MIPT_TASK_4_4
//
//  Created by Александр Малышев on 16.02.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#ifndef __MIPT_TASK_4_4__BigInt__
#define __MIPT_TASK_4_4__BigInt__

#include <iostream>
#include <cmath>

#define BUF_SIZE 255

typedef unsigned char uchar;
typedef unsigned long ulong;
typedef unsigned int uint;

enum BigIntSign {

    NEGATIVE = -1,
    ZERO = 0,
    POSITIVE = 1

};

enum compBigInt {
    
    LESS = -2,
    LESS_OR_EQUAL = -1,
    EQUAL = 0,
    MORE_OR_EQUAL = 1,
    MORE = 2
};

#pragma mark - BigInt interface
#pragma mark --


class BigInt {
    
public:
    //constructors:
    BigInt();
    BigInt(const long long aNumber);
    BigInt(uchar defVal, uint size);
    
    BigInt(const BigInt& aBigNumber);
    void operator=(const BigInt& aBigNumber);
    void operator=(const long long aBigNumber);
    //destructor:
    ~BigInt();
    
    void show() const;

    void reverseSign();
    void reverse();
    
    BigInt& operator += (const BigInt &aNumber);
    BigInt& operator -= (const BigInt &aNumber);
    BigInt& operator *= (const BigInt &aNumber);
    BigInt& operator /= (const BigInt &aNumber);
    
    friend BigInt operator + (const BigInt &aNumber, const BigInt &aNumber2);
    friend BigInt operator - (const BigInt &aNumber, const BigInt &aNumber2);
    friend BigInt operator * (const BigInt &aNumber, const BigInt &aNumber2);
    friend BigInt operator / (const BigInt &aNumber, const BigInt &aNumber2);
    friend BigInt operator % (const BigInt &aNumber, const BigInt &aNumber2);
    
    friend BigInt operator + (const BigInt &aNumber, const long long aNumber2);
    friend BigInt operator - (const BigInt &aNumber, const long long aNumber2);
    friend BigInt operator * (const BigInt &aNumber, const long long aNumber2);
    friend BigInt operator / (const BigInt &aNumber, const long long aNumber2);
    friend BigInt operator % (const BigInt &aNumber, const long long aNumber2);
    
    //comparator operators:
    friend bool   operator <   (const BigInt &aNumber, const BigInt &aNumber2);
    friend bool   operator <=  (const BigInt &aNumber, const BigInt &aNumber2);
    friend bool   operator >   (const BigInt &aNumber, const BigInt &aNumber2);
    friend bool   operator >=  (const BigInt &aNumber, const BigInt &aNumber2);
    friend bool   operator ==  (const BigInt &aNumber, const BigInt &aNumber2);
    friend bool   operator !=  (const BigInt &aNumber, const BigInt &aNumber2);
    
    friend std::ostream& operator << (std::ostream &stream, const BigInt &aNumber);
    friend std::istream& operator >> (std::istream &stream, BigInt &aNumber);
    
private:
    uchar *buffer;
    int maxBuf;
    void addDigit();
    void deleteUnusedZeroes();
    compBigInt compTo(const BigInt &aNumber) const;
    BigIntSign sign;
    friend BigInt* divideWithRemainder (const BigInt &aNumber, const BigInt &aNumber2); //returns div on [0] and mod on [1];
    friend uchar searchLargestDigitForDivisor(const BigInt &dividend, const BigInt &divisor);
};

#endif /* defined(__MIPT_TASK_4_4__BigInt__) */
