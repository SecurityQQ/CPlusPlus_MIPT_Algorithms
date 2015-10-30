//
//  main.cpp
//  RandomTestGenerator
//
//  Created by Alexander Malyshev on 29.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#include <iostream>

int main(int argc, const char * argv[]) {
    const int NUM_OF_TESTS = 20;
    for (int i = 1; i < NUM_OF_TESTS; ++i) {
        std::cout<<i <<" " << i + 1 <<" "<< rand() % 50<<std::endl;
        if (i + 2 < NUM_OF_TESTS) {
            std::cout<<i <<" " << i + 2<< " " << rand() % 50 <<std::endl;
        }
    }
    
    return 0;
}
