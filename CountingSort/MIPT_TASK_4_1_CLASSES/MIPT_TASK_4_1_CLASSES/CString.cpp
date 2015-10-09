//
//  CString.cpp
//  MIPT_TASK_4_1_CLASSES
//
//  Created by Александр Малышев on 11.02.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include "CString.h"

#pragma mark - implementation of CString

//Constructors:

CString::CString() {
    length = 0;
    maxSize = 1;
    buffer = new char;
}

CString::CString(const char *string) {
    length = strlen(string);
    maxSize = length + 1;
    buffer = new char[maxSize];
    strcpy(buffer, string);
}

CString::CString(const std::string string) {
    length = string.length();
    maxSize = string.length();
    buffer = new char[maxSize];
    strcpy(buffer, string.data());
}

CString::CString(const CString& string) {
    length = string.length;
    maxSize = string.maxSize;
    buffer = new char[maxSize];
    strcpy(buffer, string.buffer);
}

CString& CString::operator=(const CString &string) {
    length = string.length;
    maxSize = string.maxSize;
    buffer = new char[maxSize];
    strcpy(buffer, string.buffer);
    return *this;
}

//Destructors:
CString::~CString() {
    delete [] buffer;
}

//methods:
void CString::replaceAtIndex (const char* string, __indexType__ index) {
    __indexType__ stringLen = strlen( string );
    length = std::max(length, index + stringLen );
    
    //allocating memmory:
    while( length >= maxSize ) {
        resize();
    }
    
    memcpy( buffer + index, string, stringLen * sizeof(char) );
}

void CString::insertSubstringAtIndex (const char* string, __indexType__ index) {
    __indexType__ stringLen = strlen(string);
    char *newBuffer = new char[length + stringLen];
    memcpy(newBuffer, buffer, index * sizeof(char));
    memcpy(newBuffer + index, string, stringLen * sizeof(char));
    memcpy(newBuffer + index + stringLen, buffer + index, (length - index) * sizeof(char));
    delete [] buffer;
    buffer = newBuffer;
    length = length + stringLen;
    maxSize = length;
}

void CString::deleteWithIndexes (__indexType__ firstIndex, __indexType__ secondIndex) {
    memcpy( buffer + firstIndex, buffer + secondIndex, (length - secondIndex) * sizeof(char));
    length = length - ( secondIndex - firstIndex );
}

char& CString::operator[] (__indexType__ index) {
    return buffer[index];
}

//another operators:
//<#FIXME: memcpy, memcmp#>
bool CString::operator== (CString& string) {
    if( length != string.size() ) {
        return false;
    }
    for ( __indexType__ i = 0; i < length; ++i ) {
        if( buffer[i] != string[i] ) {
            return false;
        }
    }
    return true;
}

bool CString::operator< (CString& string) {
    for( __indexType__ i = 0; i < std::min( length, string.size()); ) {
        if( buffer[i] < string[i] ) {
            return true;
        }
        if( buffer[i] == string[i] ) {
            ++i;
        } else {
            return false;
        }
    }
    return false;
}

bool CString::operator> (CString& string) {
    for( __indexType__ i = 0; i < std::min( length, string.size()); ) {
        if( buffer[i] > string[i] ) {
            return true;
        }
        if( buffer[i] == string[i] ) {
            ++i;
        } else {
            return false;
        }
    }
    return false;
}

bool CString::operator>= (CString& string) {
    for( __indexType__ i = 0; i < std::min( length, string.size()); ) {
        if( buffer[i] > string[i] ) {
            return true;
        }
        if( buffer[i] == string[i] ) {
            ++i;
        } else {
            return false;
        }
    }
    return true;
}

bool CString::operator<= (CString& string) {
    for( __indexType__ i = 0; i < std::min( length, string.size()); ) {
        if( buffer[i] < string[i] ) {
            return true;
        }
        if( buffer[i] == string[i] ) {
            ++i;
        } else {
            return false;
        }
    }
    return true;
}

CString CString::operator+ (CString& string) {
    CString sumString(*this);
    sumString.length += string.size();
    while( sumString.length >= sumString.maxSize )  {
        sumString.resize();
    }
    
    memcpy(sumString.buffer, buffer, length * sizeof(char) );
    memcpy(sumString.buffer + length, string.buffer, string.size() * sizeof(char));

    return sumString;
}

CString& CString::operator+= (CString& string) {
    __indexType__ newLength = length + string.size();
    while( newLength >= maxSize ) {
        resize();
    }
    char *newBuffer = new char[maxSize];
    memcpy(newBuffer, buffer, length * sizeof(char) );
    memcpy(newBuffer + length, string.buffer, string.size() * sizeof(char));
    length = newLength;
    delete [] buffer;
    buffer = newBuffer;
    
    return *this;
}
__indexType__ CString::size() {
    return length;
}

void CString::resize() {
    maxSize = maxSize << 1;
    char *newBuffer = new char[maxSize];
    memcpy(newBuffer, buffer, length * sizeof(char));
    buffer = newBuffer;
}

std::ostream &operator << (std::ostream &stream, CString &string) {
    for (int i = 0; i < string.size(); ++i ) {
        stream<< string[i];
    }
    return stream;
}
std::istream &operator >> (std::istream &stream, CString &string) {
    std::string tempString;
    stream>> tempString;
    string = CString(tempString);
    return stream;
}