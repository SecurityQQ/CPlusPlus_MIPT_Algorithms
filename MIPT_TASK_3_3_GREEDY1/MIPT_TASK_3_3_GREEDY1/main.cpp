//
//  main.cpp
//  MIPT_TASK_3_3_GREEDY1
//
//  Created by Александр Малышев on 01.12.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//

#include <iostream>
#include <memory.h>

struct timeRange {
    int start;
    int end;
};

template <typename T>
void quickSort(T *arr, int l, int r, bool comp(T a, T b));

bool compareTimeRange(timeRange firstElement, timeRange secondElement) {
    
    return firstElement.end < secondElement.end;
}

void scanInput(timeRange *tRange, int &tRangeSize, int &maxSize ) {
    while( scanf("%d%d", &tRange[tRangeSize].start, &tRange[tRangeSize].end) == 2) {
        ++tRangeSize;
    }
}


int main(int argc, const char * argv[]) {
    timeRange* tRange = (timeRange*) malloc( 20000 * sizeof(timeRange) );
    int tRangeSize = 0;
    int maxSize = 1;
    int ans = 0;
    
    scanInput(tRange, tRangeSize, maxSize);

    //sorting by right edge:
    quickSort(tRange, 0, tRangeSize - 1, compareTimeRange);
    int tmpEnd = 0;
    for( int i = 0; i < tRangeSize; ++i) {
        if( tmpEnd <= tRange[i].start ) {
            ++ans;
            tmpEnd = tRange[i].end;
        }
    }
    
    
    free(tRange);
    printf("%d", ans);
    
    return 0;
}

template <typename T>
void quickSort(T *arr, int l, int r, bool comp(T a, T b)) {
    int i = l, j = r;
    int mid = (l + ((r - l) >> 1));
    T pivot = arr[mid];
    while (i <= j) {
        while( comp( arr[i], pivot) ) {
            ++i;
        }
        while( comp( pivot, arr[j] ) ) {
            --j;
        }
        if (i <= j) {
            std::swap(arr[i], arr[j]);
            ++i;
            --j;
        }
    };
    
    if( l < j ) {
        quickSort(arr, l, j, comp);
    }
    if (i < r) {
        quickSort(arr, i, r, comp);
    }
}
