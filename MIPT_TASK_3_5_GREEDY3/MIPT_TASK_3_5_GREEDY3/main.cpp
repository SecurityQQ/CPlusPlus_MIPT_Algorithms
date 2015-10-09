//
//  main.cpp
//  MIPT_TASK_3_5_GREEDY3
//
//  Created by Александр Малышев on 05.12.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//

#include <iostream>
#include <memory.h>
#include <assert.h>

struct timeRange {
    int start;
    int end;
};

template <typename T>
void quickSort(T *arr, int l, int r, bool comp(T a, T b));
bool compareTimeRange(timeRange firstElement, timeRange secondElement);
// for infinite input:
void scanInputInf(timeRange *tRange, int &tRangeSize, int &maxSize );
void scanInput(timeRange *tRange, int n);

bool isInRange(int t, timeRange range);
int solveProblem(timeRange *tRange, int tRangeSize);

int main(int argc, const char * argv[]) {
    int n;
    scanf("%d", &n);
    timeRange* tRange = (timeRange*) malloc( n * sizeof(timeRange) );
//  int tRangeSize = 0;

    
//    5
//    1 5
//    2 6
//    5 7
//    5 10
//    8 9

    scanInput(tRange, n);
    //sorting by right edge:
    quickSort(tRange, 0, n - 1, compareTimeRange);
    for( int i = 0; i < n; ++i ) {
        printf("%d %d\n", tRange[i].start, tRange[i].end);
    }
    printf("%d", solveProblem(tRange, n));
    
    return 0;
}

int solveProblem(timeRange *tRange, int tRangeSize) {
    int ans = 2;
    int firstAdv, secondAdv;
    firstAdv = tRange[0].start;
    secondAdv = tRange[0].end;
    for( int i = 0; i < tRangeSize; ++i ) {
        assert(firstAdv < secondAdv);
        if( !isInRange(firstAdv, tRange[i]) ) {
            if( isInRange(secondAdv, tRange[i]) ) {
                if( secondAdv == tRange[i].start) {
                    printf("Adv on %d \n", firstAdv);
                    ++ans;
                    secondAdv = tRange[i].end;
                }
                firstAdv = std::max(tRange[i].start, firstAdv);
                
            } else {
                printf("Adv on %d and %d\n", firstAdv, secondAdv);
                firstAdv = tRange[i].start;
                secondAdv = tRange[i].end; //always initiallized, because this code starts after first timeRange
                ans += 2;
            }
        }
    }
                        printf("Adv on %d and %d\n", firstAdv, secondAdv);
    return ans;
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

bool isInRange(int t, timeRange range) {
    return range.start <= t ? t <= range.end : 0;
}

bool compareTimeRange(timeRange firstElement, timeRange secondElement) {
    
    return firstElement.end < secondElement.end ? 1 : firstElement.end == secondElement.end ? firstElement.start > secondElement.start : 0;
}

// for infinite input:
void scanInputInf(timeRange *tRange, int &tRangeSize, int &maxSize ) {
    while( scanf("%d%d", &tRange[tRangeSize].start, &tRange[tRangeSize].end) == 2) {
        ++tRangeSize;
    }
}

void scanInput(timeRange *tRange, int n) {
    for( int i = 0; i < n; ++i ) {
        scanf("%d%d", &tRange[i].start, &tRange[i].end);
    }
}
