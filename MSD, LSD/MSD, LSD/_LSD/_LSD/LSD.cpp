//
//  main.cpp
//  MSD, LSD
//
//  Created by Александр Малышев on 09.11.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//

#include <iostream>
#include <assert.h>
#include <memory.h>

#define show(arr, n) for( int i = 0; i < n; ++i ) {\
std::cout <<arr[i] <<" ";\
}\
std::cout<<std::endl;

#define getArr(arr, n) for( int i = 0; i < n; ++i) {\
scanf("%lld", &arr[i]);\
}

typedef unsigned long long ll;

template <class T>
void LSD(T* arr, int d, int sizeOfArray);

void countSort(ll* data, int n, int byteNumber);

int byte(ll a, ll d) {
    
    return ( (a>> (8 * d) ) % 256);
}


int main(int argc, const char * argv[]) {
    int n;
    
    scanf("%d", &n);
    ll* arr = (ll*) malloc(n * sizeof(ll));
    getArr(arr, n);
    LSD(arr, 7, n);
    show(arr, n);
    return 0;
}


template <class T>
void LSD(T* arr, int d, int sizeOfArray) {
    for( int i = 0; i <= d; ++i) {
        countSort(arr, sizeOfArray, i);
    }
}


void countSort(ll* data, int n, int byteNumber) {
    assert(n > 0);
    int minValue = byte(data[0], byteNumber);
    int maxValue = byte(data[0], byteNumber);
    
    //Finding min and max values in array
    for( int i = 1; i < n; ++i) {
        minValue = std::min(byte(data[i], byteNumber), minValue);
        maxValue = std::max(byte(data[i], byteNumber), maxValue);
    }
    
    int valuesCount = maxValue - minValue + 1;
    int* valuesData = (int*)calloc(valuesCount, sizeof(int));
    
    for( int i = 0; i < n; ++i) {
        ++valuesData[byte(data[i], byteNumber) - minValue];
    }
    
    for( int i = 1; i < valuesCount; ++i) {
        valuesData[i] += valuesData[i - 1];
    }
    
    ll* tempData = (ll*) malloc(n * sizeof(ll));
    for( int i = n - 1; i >= 0; --i) {
        int value = byte(data[i], byteNumber) - minValue;
        --valuesData[value];
        tempData[valuesData[value]] = data[i];
    }
    memcpy(data, tempData, n * sizeof(ll));
    
    free(tempData);
    free(valuesData);
}
