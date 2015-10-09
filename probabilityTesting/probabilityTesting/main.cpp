//
//  main.cpp
//  probabilityTesting
//
//  Created by Alexander Malyshev on 06.09.15.
//  Copyright (c) 2015 Alexander Malyshev. All rights reserved.
//

#include <iostream>
#include <cmath>

unsigned int binKoef(unsigned int n, unsigned int k);

int main(){
    int n = 3;
    unsigned long long ans = 0;
    for (int k = 0; k <= n; ++k) {
        ans+= binKoef(n, k) * (1 << (n - k));
    }
    std::cout<<ans / double((1 << (n * 2)))<<std::endl;
    return 0;
}

unsigned int binKoef(unsigned int n, unsigned k){
    const unsigned int N = 1000;
    unsigned int *tempKoef = (unsigned int *) malloc(N * sizeof(int));
    unsigned int *koef = (unsigned int *) malloc(N * sizeof(int));
    for (int i = 0; i < N; ++i) { tempKoef[i] = koef[i] = 0; }
    unsigned int sz = 1;
    koef[0] = koef[1] = 1;
    tempKoef[0] = 1;
    while (sz<=n){
        sz++;
        for (int i = 1; i < sz; ++i){
            koef[i] = tempKoef[i] + tempKoef[i-1];
        }
        for (int i = 1; i < sz; ++i) tempKoef[i] = koef[i];
    }
    return koef[k];
}