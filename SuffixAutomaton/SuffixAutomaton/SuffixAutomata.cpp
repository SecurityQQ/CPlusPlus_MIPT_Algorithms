//
//  SuffixAutomata.cpp
//  SuffixAutomaton
//
//  Created by Alexander Malyshev on 16.12.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#include "SuffixAutomata.hpp"

SuffixAutomata:: SuffixAutomata(const std::string str) {
    maxID = 0;
    root = new SuffixAutomataNode((LengthType)0, this);
    joker = new SuffixAutomataNode(-1, this);
    root->setSuffixLink(joker);
    _nodes.push_back(root);
    _nodes.push_back(joker);
    auto last = root;
    for (StringSizeType i = 0; i < str.length(); ++i) {
        auto cur = new SuffixAutomataNode(last->getLength() + 1, this);
        _nodes.push_back(cur);
        auto firstNodeWithTransition = last;
        for (; firstNodeWithTransition->getTransitionAt(str[i]) == nullptr; firstNodeWithTransition = firstNodeWithTransition->getSuffixLink()) {
            if (firstNodeWithTransition == joker) {
                break;
            }
            firstNodeWithTransition->setTransition(str[i], cur);
        }
        if (firstNodeWithTransition == joker) {
            cur->setSuffixLink(root);
            last = cur;
            continue;
        }
        auto transitedNode = firstNodeWithTransition->getTransitionAt(str[i]);
        if (transitedNode->getLength() == firstNodeWithTransition->getLength() + 1) {
            cur->setSuffixLink(transitedNode);
            last = cur;
            continue;
        }
        auto clone = new SuffixAutomataNode(transitedNode, this);
        _nodes.push_back(clone);
        clone->setLength(firstNodeWithTransition->getLength() + 1);
        transitedNode->setSuffixLink(clone);
        cur->setSuffixLink(clone);
        for(auto it = firstNodeWithTransition; it->getTransitionAt(str[i]) == transitedNode; it = it->getSuffixLink()) {
            it->setTransition(str[i], clone);
        }
        last = cur;
    }
}

long long SuffixAutomata:: getNumberOfSubstrings() {
    std::vector<long long> subAnswer(_nodes.size(), NOT_CALCULATED);
    _getNumberOfSubstring(subAnswer, root);
    return subAnswer[root->getID()] - 1;
}

long long SuffixAutomata:: _getNumberOfSubstring(std::vector<long long> &subAnswer, SuffixAutomataNode *node) {
    if (subAnswer[node->getID()] != NOT_CALCULATED) {
        return subAnswer[node->getID()];
    }
    auto currentState = node;
    for(char c = 'a'; c <= 'z'; ++c) {
        auto next = currentState->getTransitionAt(c);
        if (next != nullptr) {
            subAnswer[node->getID()] += _getNumberOfSubstring(subAnswer, next);
        }
    }
    ++subAnswer[node->getID()];
    return subAnswer[node->getID()];
}