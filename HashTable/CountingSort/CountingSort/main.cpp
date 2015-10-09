//
//  main.cpp
//  CountingSort
//
//  Created by Александр Малышев on 10.11.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

const int MaxSize = 1000;
void countSort(int* arr, int n);

int main(int argc, const char * argv[]) {
    int n = 0;
    int* data = (int*) malloc(MaxSize * sizeof(int));
    while( scanf("%d", &data[n]) == 1) {
        ++n;
    }
    countSort(data, n);
    
    for( int i = 0; i < n; ++i ) {
        std::cout<<data[i] << " ";
    }
    
    free(data);
    return 0;
}

void countSort(int* data, int n) {
    assert(n > 0);
    int minValue = data[0];
    int maxValue = data[0];
    
    //Finding min and max values in array
    for( int i = 0; i < n; ++i) {
        minValue = std::min(data[i], minValue);
        maxValue = std::max(data[i], maxValue);
    }
    
    int valuesCount = maxValue - minValue + 1;
    int* valuesData = (int*)calloc(valuesCount, sizeof(int));
    
    for( int i = 0; i < n; ++i) {
        ++valuesData[data[i] - minValue];
    }
        
    for( int i = 1; i < valuesCount; ++i) {
        valuesData[i] += valuesData[i - 1];
    }
    
    int* tempData = (int*) malloc(n * sizeof(int));
    for( int i = n - 1; i >= 0; --i) {
        int value = data[i] - minValue;
        --valuesData[value];
        tempData[valuesData[value]] = data[i];
    }
    memcpy(data, tempData, n * sizeof(int));
    
    free(tempData);
    free(valuesData);
}
