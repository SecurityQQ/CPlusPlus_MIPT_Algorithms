//
//  eratosphen_O(n).cpp
//  MIPT C++
//
//  Created by Александр Малышев on 29.09.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//

#include <iostream>
#include <vector>

std::vector<int> primes(int N){
    std::vector<int> pr;
    int lp[N+1];
    for (int i=2; i<=N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back (i);
        }
        for (int j=0; j<(int)pr.size() && pr[j]<=lp[i] && i*pr[j]<=N; ++j){
            lp[i * pr[j]] = pr[j];
        }
    }
    
    //for (int i = 2; i <= N; ++i) //std::cout<<lp[i] <<" ";
    for (int i = 0; i < pr.size(); ++i){
        std::cout<<pr[i] <<" ";
    }
    std::cout<<std::endl;
    return pr;
}
int main() {
    primes(100);
    return 0;
}