//
//  main.cpp
//  AHO-KORASIK-CONTEST
//
//  Created by Alexander Malyshev on 17.11.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#include <iostream>
#define nullptr NULL

typedef long long IDType;
typedef unsigned long long StringSizeType;
typedef char LiteralType;
class Const {
public:
    static char EmptySymbol() { return '\0'; };
    static IDType EmptyNodeID() { return -1; };
    static short DefaultAlphabetSize() { return 26; };
};
#include <vector>

class AKNode {
public:
    AKNode(LiteralType symbol = Const::EmptySymbol(),  AKNode *parent = nullptr);
    void addTerminateString(IDType stringID, IDType lenghtAndSubpatternposition);
    AKNode *getTransition(const LiteralType symbol);
    AKNode *getChild(const LiteralType symbol);
    AKNode *getSuffixLink();
    AKNode *getCompressedSuffixLink();
    std::vector<IDType> & getStringIDs();
    std::vector<IDType> & getStringLenghtAndSubpatterPositions();
    bool isRoot();
    bool isTerminal();
private:
    
    LiteralType charToParent;
    std::vector<AKNode *> childs;
    std::vector<AKNode *> transitions;
    AKNode *parent;
    AKNode *suffixLink;
    AKNode *compressedSuffixLink;
    std::vector<IDType> patternsIDs;
    std::vector<IDType> stringLenghtAndSubpatterPositions;
    
    void    setTransition(const LiteralType symbol, AKNode *newValue);
    void    setChild(AKNode *newValue);
    void setTerminatingString(const IDType stringID);
    AKNode *_nextTransition(AKNode *node, const LiteralType symbol);
    friend class AKAutomata;
};

#include <assert.h>

std::vector<IDType> & AKNode:: getStringLenghtAndSubpatterPositions() {
    return stringLenghtAndSubpatterPositions;
}

bool AKNode:: isRoot() {
    return parent == nullptr;
}

void AKNode:: addTerminateString(IDType stringID, IDType lenghtAndSubpatternposition) {
    patternsIDs.push_back(stringID);
    stringLenghtAndSubpatterPositions.push_back(lenghtAndSubpatternposition);
}

AKNode:: AKNode(LiteralType symbol, AKNode *parent) {
    childs.assign(Const::DefaultAlphabetSize(), nullptr);
    transitions.assign(Const::DefaultAlphabetSize(), nullptr);
    charToParent = (parent != nullptr) ? symbol : '\0';
    this->parent = parent;
    suffixLink = nullptr;
    compressedSuffixLink = nullptr;
}

void AKNode:: setTerminatingString(const IDType stringID) {
    patternsIDs.push_back(stringID);
}

AKNode * AKNode:: getSuffixLink() {
    if (suffixLink == nullptr) {
        if (isRoot()) {
            suffixLink = this;
        } else if (parent->isRoot()) {
            suffixLink = parent;
        } else {
            suffixLink = _nextTransition(parent->getSuffixLink(), charToParent);
        }
    }
    return suffixLink;
}

AKNode * AKNode:: _nextTransition(AKNode *node, const LiteralType symbol) {
    if (node->transitions.at(symbol - 'a') == nullptr) {
        if (node->getChild(symbol)) {
            node->setTransition(symbol, node->getChild(symbol));
        } else if (node->isRoot()) {
            node->setTransition(symbol, node);
        } else {
            node->setTransition(symbol, _nextTransition(node->getSuffixLink(), symbol));
        }
    }
    return node->transitions.at(symbol - 'a');
}

AKNode * AKNode:: getCompressedSuffixLink() {
    if (compressedSuffixLink == nullptr) {
        auto link = getSuffixLink();
        if (link->isTerminal()) {
            compressedSuffixLink = link;
        } else if (link->isRoot()) {
            compressedSuffixLink = link;
        } else {
            compressedSuffixLink = link->getCompressedSuffixLink();
        }
    }
    return compressedSuffixLink;
}

bool AKNode:: isTerminal() {
    return patternsIDs.size() > 0;
}

AKNode * AKNode::getTransition(const LiteralType symbol) {
    assert('a' <= symbol && symbol >= 'A');
    return _nextTransition(this, symbol);
}
void AKNode:: setTransition(const LiteralType symbol, AKNode *newValue) {
    assert('a' <= symbol && symbol >= 'A');
    transitions.at(symbol - 'a') = newValue;
}

AKNode * AKNode::getChild(const LiteralType symbol) {
    assert('a' <= symbol && symbol >= 'A');
    return childs.at(symbol - 'a');
}

std::vector<IDType> & AKNode:: getStringIDs() {
    return patternsIDs;
}

void AKNode:: setChild(AKNode *newValue) {
    assert('a' <= newValue->charToParent && newValue->charToParent >= 'A');
    childs.at(newValue->charToParent - 'a') = newValue;
}

class AKNode;

class AKAutomata {
public:
    AKAutomata();
    
    AKNode *root();
    
    void addString(const std::string string, const IDType lenghtAndSubpatternID);
    void findPattern(IDType patternID);
protected:
    AKNode *_root;
    std::vector<std::string> patterns;
};
AKNode * AKAutomata:: root() {
    if (!_root) {
        _root = new AKNode();
    }
    return _root;
}

AKAutomata:: AKAutomata() {
    _root = new AKNode();
}


void AKAutomata:: addString(const std::string string, const IDType lenghtAndSubpatternID) {
    patterns.push_back(string);
    AKNode *currentNode = _root;
    for (StringSizeType i = 0; i < string.size(); ++i) {
        if (currentNode->getChild(string[i]) == nullptr) {
            AKNode *child = new AKNode(string[i], currentNode);
            currentNode->setChild(child);
        }
        currentNode = currentNode->getChild(string[i]);
    }
    currentNode->addTerminateString(patterns.size() - 1, lenghtAndSubpatternID);
}

class AKMaskAutomata: public AKAutomata {
public:
    AKMaskAutomata(const std::string &regExp);
    void processTextAndPrintResult(const std::string &text);
private:
    
    StringSizeType maskRegExpSize;
    std::vector<StringSizeType> startPatternPositions;
};

#include <iostream>

AKMaskAutomata:: AKMaskAutomata(const std::string& regExp) {
    std::string subPattern;
    for (unsigned long long i = 0; i < regExp.size(); ++i) {
        if ((regExp[i] >= 'a' && regExp[i] <= 'z') || regExp[i] == '?') {
            if (regExp[i] == '?') {
                if (subPattern != "") {
                    addString(subPattern, subPattern.length() + startPatternPositions.back());
                    subPattern = "";
                }
            } else {
                if (subPattern == "") {
                    startPatternPositions.push_back(i);
                }
                subPattern += regExp[i];
            }
        }
    }
    if (subPattern != "") {
        addString(subPattern, subPattern.size() + startPatternPositions.back());
    }
    
    maskRegExpSize = regExp.size();
}

void AKMaskAutomata:: processTextAndPrintResult(const std::string &text) {
    std::vector<StringSizeType> subPatternCounter(text.length(), 0);
    auto currentState = root();
    for (unsigned long long i = 0; i < text.size(); ++i) {
        if ('a'<= text[i] && text[i] <= 'z') {
            currentState = currentState->getTransition(text[i]);
            auto movingState = currentState;
            while (movingState != root()) {
                if (movingState->isTerminal()) {
                    auto lenghtAndSubpatternSizes = movingState->getStringLenghtAndSubpatterPositions();
                    for (auto lenghtAndSubpatternSize = lenghtAndSubpatternSizes.begin(); lenghtAndSubpatternSize != lenghtAndSubpatternSizes.end(); ++lenghtAndSubpatternSize) {
                        long long index = i + 1 - *lenghtAndSubpatternSize;
                        if (index >= 0) {
                            ++subPatternCounter[index];
                        }
                    }
                }
                movingState = movingState->getCompressedSuffixLink();
            }
        }
    }
    
    for (long long i = 0; i < (long long)subPatternCounter.size() + 1 - (long long)maskRegExpSize; ++i) {
        if (startPatternPositions.size() <= subPatternCounter[i]) {
            std::cout<< i << " ";
        }
    }
}

int main(int argc, const char * argv[]) {
    std::ios::sync_with_stdio(false);
    std::string pattern;
    std::string textToProcess;
    
    std::cin>> pattern;
    std::cin>> textToProcess;
    
    AKMaskAutomata blackNiggerAutomata(pattern);
    
    blackNiggerAutomata.processTextAndPrintResult(textToProcess);

    return 0;
}
