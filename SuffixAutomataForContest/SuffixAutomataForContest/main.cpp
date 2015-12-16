//
//  main.cpp
//  SuffixAutomataForContest
//
//  Created by Alexander Malyshev on 16.12.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//
#define nullptr NULL
#include <iostream>
//
//  SuffixAutomata.hpp
//  SuffixAutomaton
//
//  Created by Alexander Malyshev on 16.12.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef SuffixAutomata_hpp
#define SuffixAutomata_hpp
//
//  Constants.hpp
//  SuffixAutomaton
//
//  Created by Alexander Malyshev on 16.12.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef Constants_h
#define Constants_h


#define ALPHABET_SIZE (26)
#define NOT_CALCULATED (-1)
typedef long long LengthType;
typedef long long StringSizeType;
typedef long long IDType;
#endif /* Constants_h */

#include <iostream>
#include <vector>
#include <assert.h>

class SuffixAutomata;
class SuffixAutomataNode {
public:
    friend class SuffixAutomata;
    SuffixAutomataNode(const LengthType length, SuffixAutomata* automata);
    
    SuffixAutomataNode(const SuffixAutomataNode *anotherOne, SuffixAutomata* automata);
    
    SuffixAutomataNode *getSuffixLink() { return _suffixLink; }
    void                setSuffixLink(SuffixAutomataNode *suffixLink) { _suffixLink = suffixLink; }
    
    LengthType getLength() { return _length; }
    void       setLength(LengthType length) { _length = length; }
    
    SuffixAutomataNode *getTransitionAt(char symbol) { return _transitions[symbol - 'a']; }
    void                setTransition(char symbol, SuffixAutomataNode *node) {_transitions[symbol - 'a'] = node; }
    
    IDType getID() { return _id; }
    
private:
    LengthType _length;
    IDType _id;
    SuffixAutomataNode *_suffixLink;
    std::vector<SuffixAutomataNode *> _transitions;
};


class SuffixAutomata {
public:
    friend class SuffixAutomataNode;
    SuffixAutomata(const std::string str);
    long long getNumberOfSubstrings();
private:
    long long _getNumberOfSubstring(std::vector<long long> &subAnswer, SuffixAutomataNode *node);
    SuffixAutomataNode *root;
    SuffixAutomataNode *joker;
    std::vector<SuffixAutomataNode *> _nodes;
    IDType maxID;
};

SuffixAutomataNode:: SuffixAutomataNode(const LengthType length, SuffixAutomata* automata) : _length(length), _suffixLink(nullptr), _transitions(ALPHABET_SIZE, nullptr) {
    automata->_nodes.push_back(this);
    automata->maxID++;
    _id = automata->maxID;
}

SuffixAutomataNode:: SuffixAutomataNode(const SuffixAutomataNode *anotherOne, SuffixAutomata* automata): _length(anotherOne->_length), _suffixLink(anotherOne->_suffixLink), _transitions(anotherOne->_transitions) {
    automata->_nodes.push_back(this);
    automata->maxID++;
    _id = automata->maxID;
}

#endif /* SuffixAutomata_hpp */

//
//  SuffixAutomata.cpp
//  SuffixAutomaton
//
//  Created by Alexander Malyshev on 16.12.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

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
    subAnswer[node->getID()] = 0;
    for(char c = 'a'; c <= 'z'; ++c) {
        auto next = currentState->getTransitionAt(c);
        if (next != nullptr) {
            subAnswer[node->getID()] += _getNumberOfSubstring(subAnswer, next);
        }
    }
    ++subAnswer[node->getID()];
    return subAnswer[node->getID()];
}

int main(int argc, const char * argv[]) {
    std::string str;
    std::cin>>str;
    auto suffixAutomata = SuffixAutomata(str);
    std::cout<<suffixAutomata.getNumberOfSubstrings()<<std::endl;
    return 0;
}
