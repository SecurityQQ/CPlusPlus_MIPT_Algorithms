//
//  Graph.cpp
//  PrefixParser
//
//  Created by Alexander Malyshev on 25.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#include <iostream>
#include "Graph.h"
#include <stack>

Graph:: Graph(const std::string regularExpression) {
    vertexesSize = 0;
    std::stack<SubNode> parseStack;
    for (unsigned int i = 0; i < regularExpression.size(); ++i) {
        char currentSymbol = regularExpression.at(i);
        switch (currentSymbol) {
            case 'a':
            case 'b':
            case 'c': {
                auto begin = createNewNode(Node::Eps());
                auto end = createNewNode(Node::Eps());
                auto symbol = createNewNode(currentSymbol);
                begin->next.push_back(symbol);
                symbol->next.push_back(end);
                parseStack.push(SubNode(begin, end));
            }
            break;
            case '1':
                parseStack.push(SubNode(createNewNode(Node::Eps()), createNewNode(Node::Eps())));
                break;
            case '+': {
                if(parseStack.size() < 2) {
                    throw RegularExpressionParseError::defaultError();
                }
                auto secondSubExp = parseStack.top(); parseStack.pop();
                auto firstSubExp = parseStack.top(); parseStack.pop();
                firstSubExp.begin->next.push_back(secondSubExp.begin);
                secondSubExp.end->next.push_back(firstSubExp.end);
                parseStack.push(SubNode(firstSubExp.begin, firstSubExp.end));
            }
                break;
            case '*': {
                auto subExp = parseStack.top(); parseStack.pop();
                subExp.begin->next.push_back(subExp.end);
                subExp.end->next.push_back(subExp.begin);
                parseStack.push(subExp);
            }
                break;
            case '.': {
                auto secondSubExp = parseStack.top(); parseStack.pop();
                auto firstSubExp = parseStack.top(); parseStack.pop();
                firstSubExp.end->next.push_back(secondSubExp.begin);
                parseStack.push(SubNode(firstSubExp.begin, secondSubExp.end));
            }
                break;
            default:
                throw RegularExpressionParseError("Regular Expression may contains only 'a', 'b', 'c', '1', '.', '*', '+'");
                break;
        }
    }
    auto regExp = parseStack.top(); parseStack.pop();
    this->begin = regExp.begin;
    this->end = regExp.end;
}

unsigned int Graph:: findMaxPrefixInWord(std::string word) {
    return 0;
}

Node * Graph:: createNewNode(const char symbol) {
    auto instance = new Node(symbol, vertexesSize);
    vertexesSize++;
    return instance;
}