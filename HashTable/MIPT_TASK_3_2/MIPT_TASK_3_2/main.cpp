//
//  main.cpp
//  MIPT_TASK_3_2
//
//  Created by Александр Малышев on 24.11.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//

#include <iostream>


typedef long long ll;

ll getNumbersOfPartitions(int n, int t);

int main(int argc, const char * argv[]) {
    int n;
    scanf("%d", &n);
    printf("%lld", getNumbersOfPartitions(n, n));
    return 0;
}


ll getNumbersOfPartitions(int n, int t) {
    ll numbersOfPartitions[n + 1][t + 1];
    for( int i = 0; i < t + 1; ++i ) {
        numbersOfPartitions[0][i] = 1;
    }
    for( int i = 1; i < n + 1; ++i ) {
        numbersOfPartitions[i][0] = 0;
    }
    numbersOfPartitions[1][1] = 1;
    
    for( int i = 1; i < n + 1; ++i) {
        for( int j = 1; j < t + 1; ++j ) {
            if( i - j < 0 ) {
                if( j >= 1) {
                    numbersOfPartitions[i][j] = numbersOfPartitions[i][j - 1];
                } else {
                    numbersOfPartitions[i][j] = 0;
                }
            } else {
                if( j >= 1 ) {
                    numbersOfPartitions[i][j] = numbersOfPartitions[i - j][j] + numbersOfPartitions[i][j - 1];
                } else {
                    numbersOfPartitions[i][j] = numbersOfPartitions[i - j][j];
                }
            }
        }
    }
    return numbersOfPartitions[n][t];
}