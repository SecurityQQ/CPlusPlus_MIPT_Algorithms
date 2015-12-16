//
//  main.cpp
//  Ukkonen
//
//  Created by Alexander Malyshev on 30.11.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#include <iostream>
#include "UKSuffixTree.hpp"
#include "SuffixTree.h"
#include "EnglishAlphabetConfig.h"

int main(int argc, const char * argv[]) {
    auto s1 = "lookatmyhorsemyhorseisamazing";
    auto s2 = "amazingsemyhorse";
    UKSuffixTree automata(s1);
    std::cout<<automata.LCS(s2)<<std::endl;
    
    EnglishAlphabetConfig conf;
    SuffixTree tree(conf, s1);
    std::cout<<tree.LCSWith(s2)<<std::endl;
    
    return 0;
}
