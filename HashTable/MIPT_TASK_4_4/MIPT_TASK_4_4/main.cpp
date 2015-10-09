//
//  main.cpp
//  MIPT_TASK_4_4
//
//  Created by Александр Малышев on 16.02.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <iostream>
#include "BigInt.h"
int main(int argc, const char * argv[]) {
//    BigInt a(MAX_BigInt_BUFFER);
//    BigInt b(11);
//    BigInt c = a + b;
//    c.show();

    
    //
    BigInt a(99999999);
    BigInt b(11111111);
    BigInt ten(10);
    
//    b.show();
//    printf("\n");
//    a.show();
//    printf("\n");
//    
//    BigInt c = a + b;
    
//    std::cout<< c;
 
    BigInt qw, er;
    std::cin>> qw;
    std::cin >> er;
//    std::cin>> er;
//    qw.show();
    std::cout<< qw / er;
    
//    std::cout<<qw + er;
//    std::cout<< (a / b);
    
    
//    BigInt a(392);
//    a -= 390;
//    BigInt b(BUF_SIZE);
//    
//    a *= b;
//    BigInt c(40);
//    a = a + c;
//    
//    a.show();
    return 0;
}