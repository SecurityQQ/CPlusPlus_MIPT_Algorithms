//
//  main.cpp
//  SuffixAutomaton
//
//  Created by Alexander Malyshev on 16.12.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#include <iostream>
#include "SuffixAutomata.hpp"

int main(int argc, const char * argv[]) {
    auto suffixAutomata = SuffixAutomata("abcbc");
    std::cout<<suffixAutomata.getNumberOfSubstrings()<<std::endl;
    return 0;
}
