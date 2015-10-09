//
//  main.cpp
//  CTopResult
//
//  Created by Александр Малышев on 03.03.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <iostream>
#include "Comparator.h"
#include "CTopResult.h"


#define defaultTopSize 10

int stringsCompareFunction(const std::string a, const std::string b) {
    return a.compare(b);
}

int scoreCompare(const int a, const int b) {
    if( a < b ) {
        return 1;
    }
    if( a > b) {
        return -1;
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    char ch;
    Comparator<int> comparator(scoreCompare);
    
    CTopResult<std::string, int> top(defaultTopSize, comparator);
    std::string key;
    int value;
    
    for( int i = 0; i < defaultTopSize * 3; ++i ) {
        top.add(std::string("The guy ") + std::string(std::to_string(i)), rand() % 20);
    }

    for( CTopResult<std::string, int>::iterator it = top.begin(); it != top.end(); ++it ) {
        std::cout<<(*it).value <<std::endl;
    }
    
    
    while( !std::cin.fail() ) {
        ch = EOF;
        std::cin>> ch;
        switch (ch) {
            case '+':
                std::cin>> key >> value;
                top.add(key, value);
                break;

            case '.':
                top.show();
                break;
            default:
                exit(0);
                break;
        }
    }

    
    return 0;
}
