//
//  main.cpp
//  MIPT_TASK_3_4_GREEDY2
//
//  Created by Александр Малышев on 05.12.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//

#include <iostream>

typedef long long ll;

struct athlet {
    int mass;
    int strength;
};

template <typename T>
void quickSort(T *arr, int l, int r, bool comp(T a, T b));

bool compareAthlets(athlet at1, athlet at2) {
    return at1.mass < at2.mass;
}

int main(int argc, const char * argv[]) {
    const int n = 100000;
    int numOfAthlets = 0;
    int ans;
    ll totalMass = 0;
    athlet* buf = (athlet*)malloc( n * sizeof(athlet) );
    
    while( scanf("%d%d", &buf[numOfAthlets].mass, &buf[numOfAthlets].strength) == 2 ) {
        ++numOfAthlets;
    }
    
    quickSort(buf, 0, numOfAthlets - 1, compareAthlets);
    
    for( int i = 0; i < numOfAthlets; ++i ) {
        if( buf[i].strength >= totalMass ) {
            ++ans;
            totalMass += buf[i].mass;
        }
    }
    
    free(buf);
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
