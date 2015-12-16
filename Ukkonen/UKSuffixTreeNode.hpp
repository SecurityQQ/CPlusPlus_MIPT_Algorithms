//
//  UKSuffixTreeNode.hpp
//  Ukkonen
//
//  Created by Alexander Malyshev on 01.12.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef UKSuffixTreeNode_hpp
#define UKSuffixTreeNode_hpp

#include <stdio.h>
#include <vector>
#include "Constants.h"

class UKSuffixTreeNode;

class ReferencePair {
public:
    ReferencePair(const StringSizeType leftStringBound = 0, const StringSizeType rightStringBound = 0, UKSuffixTreeNode *nextNode = nullptr):
    _leftStringBound(leftStringBound),
    _rightStringBound(rightStringBound),
    _ancestorNode(nextNode) {};
    
    
    UKSuffixTreeNode *getAncestorNode() { return _ancestorNode; }
    const StringSizeType getRightStringBound() { return _rightStringBound; }
    const StringSizeType getLeftStringBound() { return _leftStringBound; }
    
private:
    UKSuffixTreeNode *_ancestorNode;
    StringSizeType _leftStringBound;
    StringSizeType _rightStringBound;
};


class UKSuffixTreeNode {
    
public:
    UKSuffixTreeNode();
    
    ReferencePair getTransition(const char symbol);
    void setTransition(ReferencePair transition, const char symbol);
    
    UKSuffixTreeNode *getSuffixLink() { return _suffixLink; }
    void setSuffixLink(UKSuffixTreeNode *link) { _suffixLink = link; }
    
private:
    
    std::vector<ReferencePair> _nextTransitions;
    UKSuffixTreeNode *_suffixLink;
    
};


#endif /* UKSuffixTreeNode_hpp */
