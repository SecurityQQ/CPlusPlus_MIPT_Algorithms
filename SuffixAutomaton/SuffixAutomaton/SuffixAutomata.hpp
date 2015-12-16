//
//  SuffixAutomata.hpp
//  SuffixAutomaton
//
//  Created by Alexander Malyshev on 16.12.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef SuffixAutomata_hpp
#define SuffixAutomata_hpp
#include "Constants.hpp"
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
