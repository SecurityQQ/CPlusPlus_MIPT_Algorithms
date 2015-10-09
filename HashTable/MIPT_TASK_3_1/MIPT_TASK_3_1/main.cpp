//
//  main.cpp
//  MIPT_TASK_3_1
//
//  Created by Александр Малышев on 24.11.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//

#include <iostream>
#include <memory.h>

typedef long long ll;

ll getAmountOfAwesomeNumbers(int n);
void dynamicPlusWithKnightMove(ll* arr, const int arrLen);

int main() {
    int n;
    scanf("%d", &n);
    printf("%lld", getAmountOfAwesomeNumbers(n));
    return 0;
}


ll getAmountOfAwesomeNumbers(int n) {
    const int BUTTONS_NMB = 10;
    ll* arr = (ll*)calloc(BUTTONS_NMB, sizeof(ll));
    ll ans = 0;
    
    //starting terms
    for( int i = 0; i < BUTTONS_NMB; ++i ) {
        if( (i != 0) && (i != 8) ) {
            arr[i] = 1;
        }
    }
    
    for( int j = 0; j < n; ++j) {
        if( j != 0 ) {
            dynamicPlusWithKnightMove(arr, BUTTONS_NMB);
        }
    }
    for( int i = 0; i < BUTTONS_NMB; ++i ) {
        ans += arr[i];
    }
    
    
    free(arr);
    return ans;
}

// 1 2 3
// 4 5 6
// 7 8 9
//   0



void dynamicPlusWithKnightMove(ll* arr, const int arrLen) {
    ll* tmp = (ll*)malloc(arrLen * sizeof(ll));
    memcpy(tmp, arr, arrLen * sizeof(ll));
    tmp[0] = arr[4] + arr[6];
    tmp[1] = arr[6] + arr[8];
    tmp[2] = arr[7] + arr[9];
    tmp[3] = arr[4] + arr[8];
    tmp[4] = arr[3] + arr[9] + arr[0];
    tmp[5] = 0;
    tmp[6] = arr[1] + arr[7] + arr[0];
    tmp[7] = arr[2] + arr[6];
    tmp[8] = arr[1] + arr[3];
    tmp[9] = arr[4] + arr[2];
    memcpy(arr, tmp, arrLen * sizeof(ll));
    free(tmp);
}