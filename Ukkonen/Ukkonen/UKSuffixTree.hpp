//
//  UKSuffixTree.hpp
//  Ukkonen
//
//  Created by Alexander Malyshev on 02.12.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef UKSuffixTree_hpp
#define UKSuffixTree_hpp

#include <iostream>
#include "Constants.h"
#include "UKSuffixTreeNode.hpp"
#include <string.h>

class UKSuffixTree {
public:
    UKSuffixTree(const std::string string);
    std::string LCS(const std::string stringForLCS);
private:
    char getTransitionCharAtIndex(const StringSizeType i);
    ReferencePair update(UKSuffixTreeNode* node, StringSizeType leftBound, StringSizeType rightBound);
    ReferencePair canonize(UKSuffixTreeNode* node, StringSizeType leftBound, StringSizeType rightBound);
    bool tryToSplitAndReturnIsEndPoint(const char symbol, ReferencePair pair, UKSuffixTreeNode** node); //changes node
    std::string _string;
    UKSuffixTreeNode *joker;
    UKSuffixTreeNode *root;
};

#endif /* UKSuffixAutomata_hpp */
