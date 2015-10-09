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

typedef long long ll;

struct timeRange {
    ll start;
    ll end;
};

template <typename T>
void quickSort(T *arr, ll l, ll r, bool comp(T a, T b));
bool compareTimeRange(timeRange firstElement, timeRange secondElement);
// for infinite input:
void scanInputInf(timeRange *tRange, ll &tRangeSize, ll &maxSize );
void scanInput(timeRange *tRange, ll n);

bool isInRange(ll t, timeRange range);
ll solveProblem(timeRange *tRange, ll tRangeSize);


//!==============================
//!=============MAIN=============
//!==============================
int main(int argc, const char * argv[]) {
    ll n;
    scanf("%lld", &n);
    timeRange* tRange = (timeRange*) malloc( n * sizeof(timeRange) );
    scanInput(tRange, n);
    quickSort(tRange, 0, n - 1, compareTimeRange);

//    for( ll i = 0; i < n; ++i ) {
//        printf("%d %d\n", tRange[i].start, tRange[i].end);
//    }

    printf("%lld", solveProblem(tRange, n));
    free(tRange);
    return 0;
}
//!==============================
//!=========END_OF_MAIN==========
//!==============================


ll solveProblem(timeRange *tRange, ll tRangeSize) {
    ll ans = 2;
    ll firstAdv = tRange[0].end - 1;
    ll secondAdv = tRange[0].end;
    for( ll i = 1; i < tRangeSize; i++ ) {
        if( tRange[i].start <= secondAdv ) {
            if (tRange[i].start > firstAdv) {
                ++ans;
                firstAdv = secondAdv;
                secondAdv = tRange[i].end;
            }
        } else {
            ans += 2;
            firstAdv = tRange[i].end - 1;
            secondAdv = tRange[i].end;
            
        }
    }
    return ans;
}

template <typename T>
void quickSort(T *arr, ll l, ll r, bool comp(T a, T b)) {
    ll i = l, j = r;
    ll mid = (l + ((r - l) >> 1));
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

bool isInRange(ll t, timeRange range) {
    return range.start <= t ? t <= range.end : false;
}

bool compareTimeRange(timeRange firstElement, timeRange secondElement) {
    
    return firstElement.end < secondElement.end ? 1 : firstElement.end == secondElement.end ? firstElement.start > secondElement.start : 0;
}

// for infinite input:
void scanInputInf(timeRange *tRange, ll &tRangeSize, ll &maxSize ) {
    while( scanf("%lld%lld", &tRange[tRangeSize].start, &tRange[tRangeSize].end) == 2) {
        ++tRangeSize;
    }
}

void scanInput(timeRange *tRange, ll n) {
    for( ll i = 0; i < n; ++i ) {
        scanf("%lld%lld", &tRange[i].start, &tRange[i].end);
    }
}
