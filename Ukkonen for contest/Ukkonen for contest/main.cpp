//
//  main.cpp
//  Ukkonen for contest
//
//  Created by Alexander Malyshev on 16.12.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//
#define nullptr NULL
#include <iostream>
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
//
//  Constants.h
//  Ukkonen
//
//  Created by Alexander Malyshev on 01.12.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef Constants_h
#define Constants_h


#define ALPHABET_SIZE 26
#define INFINITY 1000000000
typedef long long StringSizeType;

#endif /* Constants_h */


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
#include <assert.h>

UKSuffixTreeNode:: UKSuffixTreeNode() {
    _nextTransitions = std::vector<ReferencePair>(ALPHABET_SIZE);
}

ReferencePair UKSuffixTreeNode:: getTransition(const char symbol) {
//    assert(symbol >= 'a' && symbol >= 'Z');
    return _nextTransitions[symbol - 'a'];
}

void UKSuffixTreeNode:: setTransition(ReferencePair transition, const char symbol) {
//    assert(symbol >= 'a' && symbol >= 'Z');
    _nextTransitions[symbol - 'a'] = transition;
}

//
//  UKSuffixTree.cpp
//  Ukkonen
//
//  Created by Alexander Malyshev on 02.12.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

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


UKSuffixTree:: UKSuffixTree(const std::string string) {
    root = new UKSuffixTreeNode;
    joker = new UKSuffixTreeNode;
    _string = string;
    
    for (StringSizeType i = 0; i < ALPHABET_SIZE; ++i) {
        auto transition = ReferencePair(-i - 1, -i - 1, root);
        joker->setTransition(transition, i + 'a');
    }
    root->setSuffixLink(joker);
    auto activePoint = ReferencePair(0, -1, root);
    
    for (StringSizeType i = 0; i < string.size(); ++i) {
        activePoint = update(activePoint.getAncestorNode(), activePoint.getLeftStringBound(), i);
        activePoint = canonize(activePoint.getAncestorNode(), activePoint.getLeftStringBound(), i);
    }
}

char UKSuffixTree:: getTransitionCharAtIndex(const StringSizeType i) {
    return i < 0 ? (-i - 1) : _string[i]; //returns alphabet or char for joker
}

ReferencePair UKSuffixTree:: update(UKSuffixTreeNode *node, StringSizeType leftBound, StringSizeType rightBound) {
    UKSuffixTreeNode* oldNode = root;
    UKSuffixTreeNode* currentNode = nullptr;
    
    while (!tryToSplitAndReturnIsEndPoint(getTransitionCharAtIndex(rightBound), ReferencePair(leftBound, rightBound - 1, node), &currentNode)) {
        UKSuffixTreeNode* newState = new UKSuffixTreeNode();
        currentNode->setTransition(ReferencePair(rightBound, INFINITY, newState), getTransitionCharAtIndex(rightBound));
        if (oldNode != root) {
            oldNode->setSuffixLink(currentNode);
        }
        oldNode = currentNode;
        auto canonizedNode = canonize(node->getSuffixLink(), leftBound, rightBound - 1);
        leftBound = canonizedNode.getLeftStringBound();
        node = canonizedNode.getAncestorNode();
    }
    
    if (oldNode != root) {
        oldNode->setSuffixLink(node);
    }
    return ReferencePair(leftBound, 0, node);
}

ReferencePair UKSuffixTree:: canonize(UKSuffixTreeNode* node, StringSizeType leftBound, StringSizeType rightBound) {
    if (leftBound > rightBound) {
        return ReferencePair(leftBound, 0, node);
    }
    
    auto leftReferencePair = node->getTransition(getTransitionCharAtIndex(leftBound));
    if (leftReferencePair.getRightStringBound() <= rightBound) {
        while (leftReferencePair.getRightStringBound() - leftReferencePair.getLeftStringBound() <= rightBound - leftBound) {
            leftBound += leftReferencePair.getRightStringBound() - leftReferencePair.getLeftStringBound() + 1;
            node = leftReferencePair.getAncestorNode();
            if (leftBound <= rightBound) {
                leftReferencePair = node->getTransition(getTransitionCharAtIndex(leftBound));
            }
        }
    }
    return ReferencePair(leftBound, 0, node);
}

bool UKSuffixTree:: tryToSplitAndReturnIsEndPoint(const char symbol, ReferencePair pair, UKSuffixTreeNode** node) {
    if (pair.getLeftStringBound() <= pair.getRightStringBound()) { //normal pair, not joker
        ReferencePair next = pair.getAncestorNode()->getTransition(getTransitionCharAtIndex(pair.getLeftStringBound()));
        if (symbol == getTransitionCharAtIndex(next.getLeftStringBound() + pair.getRightStringBound() - pair.getLeftStringBound() + 1)) {
            *node = pair.getAncestorNode();
            return true;
        }
        
        UKSuffixTreeNode* newNode = new UKSuffixTreeNode;
        long long branchingPoint = next.getLeftStringBound() + pair.getRightStringBound() - pair.getLeftStringBound() + 1;
        
        pair.getAncestorNode()->setTransition(ReferencePair(next.getLeftStringBound(), branchingPoint - 1, newNode)
                                              , getTransitionCharAtIndex(next.getLeftStringBound()));
        newNode->setTransition(ReferencePair(branchingPoint, next.getRightStringBound(), next.getAncestorNode()), getTransitionCharAtIndex(branchingPoint));
        *node = newNode;
        return false;
    }
    else { //joker transition
        *node = pair.getAncestorNode();
        return pair.getAncestorNode() == nullptr ? false : (pair.getAncestorNode()->getTransition(symbol).getAncestorNode() != nullptr);
    }
}

std::string UKSuffixTree:: LCS(const std::string stringForLCS) {
    StringSizeType lengthOfMax = 0;
    StringSizeType leftBoundOfMax = 0;
    StringSizeType leftBound = 0;
    StringSizeType length = 0;
    UKSuffixTreeNode *currentNode = root;
    for (StringSizeType i = 0; i < stringForLCS.size(); ++i) {
        auto edge = currentNode->getTransition(stringForLCS[i]);
        if (edge.getAncestorNode() != nullptr) {
            StringSizeType j = 0;
            while (stringForLCS[i + j] == _string[edge.getLeftStringBound() + j] && j < edge.getRightStringBound() - edge.getLeftStringBound() + 1) {
                ++j;
                ++length;
            }
            if (j != 0) {
                i += j - 1;
            }
            if (lengthOfMax < length) {
                leftBoundOfMax = leftBound;
                lengthOfMax = length;
            }
            if (j == edge.getRightStringBound() - edge.getLeftStringBound() + 1) { //reached node state
                currentNode = edge.getAncestorNode();
                continue;
            }
            leftBound = i + 1;
            length = 0;
            if (currentNode != root) {
                currentNode = currentNode->getSuffixLink();
            }
        } else {
            leftBound = i + 1;
            length = 0;
            if (currentNode != root) {
                currentNode = currentNode->getSuffixLink();
            }
        }
    }
    return std::string(stringForLCS, leftBoundOfMax, lengthOfMax);
}

int main(int argc, const char * argv[]) {
    std::string string;
    std::string anotherOne;
    std::cin>>string >>anotherOne;
    UKSuffixTree tree(string);
    std::cout<<tree.LCS(anotherOne)<<std::endl;
    return 0;
}
