//
//  main.cpp
//  Treap
//
//  Created by Александр Малышев on 19.04.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <iostream>
#include "Treap.h"

int compFunc(const int a, const int b) {
    return a - b;
}

int main(int argc, const char * argv[]) {
        Treap<int> bst(compFunc);
        char ch;
        int k, prior;
        while( !std::cin.fail() ) {
            ch = EOF;
            std::cin>> ch >> k >> prior;
            switch (ch) {
                case '+':
                    if (bst.search(k) == false) {
                        bst.add(k, prior);
                        std::cout<<"OK\n";
                    } else {
                        std::cout<<"FAIL\n";
                    }
                    break;
                case '?':
                    if (bst.search(k) == true) {
                        std::cout<<"OK\n";
                    } else {
                        std::cout<<"FAIL\n";
                    }
                    break;
                case '-':
                    if (bst.search(k) == false) {
                        std::cout<<"FAIL\n";
                    } else {
                        bst.remove(k);
                        std::cout<<"OK\n";
                    }
                    break;
                case '.':
                    std::cout<<"Height: " <<bst.height() <<std::endl;
                    break;
                case ',':
                    std::cout<<"Width: " <<bst.width() <<std::endl;
                    break;
                default:
                    exit(0);
                    try {
                        throw "Incorrect operation";
                    } catch (char * errorMsg) {
                        std::cerr<< errorMsg <<std::endl;
                        exit(1);
                    }
                    break;
            }
        }
    
    return 0;
}
