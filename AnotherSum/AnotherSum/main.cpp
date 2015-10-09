//
//  main.cpp
//  AnotherSum
//
//  Created by Alexander Malyshev on 21.09.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#include <iostream>

int main(int argc, const char * argv[]) {
    int a, b;
    
    std::cin>>a >> b;
    
    
    double sum = 0;
    for (int k = 0; k <= b/2; ++k) {
        double product = 1;
        for (int i = 0; i <= 2 * k - 1; ++i) {
            product *= (b - i) / (double) (a +b -i);
        }
        
        sum += a / (double)(a+b-2*k) * product;
    }
    
    std::cout<<sum <<std::endl;
    std::cout<<a / (double) (a + b) <<std::endl;
    
    return 0;
}
