//
//  UKSuffixTreeNode.cpp
//  Ukkonen
//
//  Created by Alexander Malyshev on 01.12.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#include "UKSuffixTreeNode.hpp"
#include <assert.h>

UKSuffixTreeNode:: UKSuffixTreeNode() {
    _nextTransitions = std::vector<ReferencePair>(ALPHABET_SIZE);
}

ReferencePair UKSuffixTreeNode:: getTransition(const char symbol) {
    assert(symbol >= 'a' && symbol >= 'Z');
    return _nextTransitions[symbol - 'a'];
}

void UKSuffixTreeNode:: setTransition(ReferencePair transition, const char symbol) {
    assert(symbol >= 'a' && symbol >= 'Z');
    _nextTransitions[symbol - 'a'] = transition;
}