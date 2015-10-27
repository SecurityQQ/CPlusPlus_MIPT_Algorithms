//
//  main.cpp
//  PrefixParser
//
//  Created by Alexander Malyshev on 25.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#include <iostream>
#include "Graph.h"


class Presentator {
public:
    static Presentator &sharedInstance() {
        static auto instance = Presentator();
        return instance;
    }
    
    void prepareForProgram() {
        std::string description = "You can use any regular expression contains 'a', 'b', 'c', '.'(concatination), '*' (repitition), '+' (combination) or 1 (empty word)\n";
        std::cout<<description;
    }
    void prepareForEnteringRegExp() {
        std::cout<<"Enter regular expression:\n";
    }
    void prepareForEnteringWord() {
        std::cout<<"Enter word:\n";
    }
    
    void presentAnswer(unsigned int answer) {
        std::cout<<"Maximum length of prefix in your word is ";
        std::cout<<answer<<std::endl;
    }
};

int main(int argc, const char * argv[]) {
    Presentator::sharedInstance().prepareForProgram();
    std::string regularExpression;
    std::string word;
    Presentator::sharedInstance().prepareForEnteringRegExp();
    std::cin>> regularExpression;
    Presentator::sharedInstance().prepareForEnteringWord();
    std::cin>> word;
    try {
        auto g = Graph(regularExpression);
        Presentator::sharedInstance().presentAnswer(g.findMaxPrefixInWord(word));
    } catch (RegularExpressionParseError error) {
        std::cerr << error.description() << std::endl;
    }
    return 0;
}
