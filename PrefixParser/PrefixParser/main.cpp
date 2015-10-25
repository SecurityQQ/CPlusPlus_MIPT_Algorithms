//
//  main.cpp
//  PrefixParser
//
//  Created by Alexander Malyshev on 25.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#include <iostream>
#include "Graph.h"

int main(int argc, const char * argv[]) {
    std::string regularExpression;
    std::string word;
    std::cin>> regularExpression;
    std::cin>> word;
    try {
        auto g = Graph(regularExpression);
        std::cout<<g.findMaxPrefixInWord(word) <<std::endl;
    } catch (RegularExpressionParseError error) {
        std::cerr << error.description() << std::endl;
    }
    return 0;
}
