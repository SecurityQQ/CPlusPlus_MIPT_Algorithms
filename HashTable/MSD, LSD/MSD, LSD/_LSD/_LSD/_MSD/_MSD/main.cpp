//
//  main.cpp
//  _MSD
//
//  Created by Александр Малышев on 16.11.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <cstring>
#include <cstdlib>

#define show(arr, n) for( int i = 0; i < n; ++i ) {\
std::cout <<arr[i] <<"\n";\
}\


void MSD(char** strs, int N,int pos);
void countSort(char** data, int n, int pos);

int strLen(char* str) {
    int len = 0;
    while(str[len++] != '\0') {
        
    }
    return len - 1;
}
char** getArr(int& sz) {
    int n = 10000;
    sz = 0;
    char** foo = (char**) malloc(n * sizeof(char*));
    for( int i = 0; i < n; ++i ) {
        foo[i] = (char*) malloc(257 * sizeof(char));
    }
    
    char** arr = (char**) malloc(sizeof(char*));
    while( gets(foo[sz]) ) {
        int sLen = strLen(foo[sz]);
        arr = (char**) realloc(arr, (sz + 1) * sizeof(char*));
        arr[sz] = (char*) malloc((sLen + 1)* sizeof(char));
        memmove(arr[sz], foo[sz], sLen);
        arr[sz][sLen] = '\0';
        free(foo[sz]);
        if( foo[sz++][0] == '\0' ) {
            break;
        }
    }
    free(foo);
    
    return arr;
}

int main(int argc, const char * argv[]) {
    char** arr;
    int sz = 0;
    arr = getArr(sz);
    MSD(arr, sz, 0);
    show(arr, sz);
    
    return 0;
}

//! Stable counting sort for char* with charPos key
void countSort(char** data, int n, int charPos)
{
    assert(n > 0);
    int minValue = data[0][charPos];
    int maxValue = data[0][charPos];
    for (int i = 0; i < n; i++)
    {
        minValue = std::min((int)data[i][charPos], minValue);
        maxValue = std::max((int)data[i][charPos], maxValue);
    }
    int valuesCount = maxValue - minValue + 1;
    int* valuesData = (int*)calloc(valuesCount, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        valuesData[(data[i][charPos]) - minValue]++;
    }
    for (int i = 1; i < valuesCount; i++) {
        valuesData[i] += valuesData[i - 1];
    }
    char ** tempData = (char**)malloc(n * sizeof(char*));
    assert(tempData);
    for( int i = n - 1; i >= 0; --i ) {
        int value = (data[i][charPos]) - minValue;
        valuesData[value]--;
        tempData[valuesData[value]] = data[i];
    }
    for (int i = 0; i < n; i++) {
        data[i] = tempData[i];
    }
    free(valuesData);
    free(tempData);
}

//! charPos = [0, strlen], n = length of arrOfStr
void MSD(char** arrOfStr, int arrayLen, int charPos) {
    int i = 0;
    
    //first sorting (all strings are not empty)
    countSort(arrOfStr, arrayLen, charPos);
    
    while( i < arrayLen ) {
        int j = i;
        //skipping sorted elements
        char firstChar = arrOfStr[i][charPos];
        while( ( arrOfStr[j][charPos] == firstChar) && ( ++j < arrayLen ) ) {
        }
        
        //sorting with size = j - i
        if( firstChar != '\0' ) {
            int sz = j - i;
            if( sz > 1 ) {
                //MSD(&arrOfStr[i], sz, charPos +1);
                MSD(arrOfStr + i, sz, charPos + 1 );
            }
            i = j;
        }
    }
}