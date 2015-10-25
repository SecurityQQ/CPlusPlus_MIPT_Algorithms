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
    std::stack<SubNode> parsingStack;
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
                parsingStack.push(SubNode(begin, end));
            }
            break;
            case '1': {
                auto begin = createNewNode(Node::Eps());
                auto end = createNewNode(Node::Eps());
                begin->next.push_back(end);
                parsingStack.push(SubNode(begin, end));
            }
                break;
            case '+': {
                if (parsingStack.size() < 2) {
                    throw RegularExpressionParseError::defaultError();
                }
                auto secondSubExp = parsingStack.top(); parsingStack.pop();
                auto firstSubExp = parsingStack.top(); parsingStack.pop();
                firstSubExp.begin->next.push_back(secondSubExp.begin);
                secondSubExp.end->next.push_back(firstSubExp.end);
                parsingStack.push(SubNode(firstSubExp.begin, firstSubExp.end));
            }
                break;
            case '*': {
                if (parsingStack.size() < 1) {
                    throw RegularExpressionParseError::defaultError();
                }
                auto subExp = parsingStack.top(); parsingStack.pop();
                subExp.begin->next.push_back(subExp.end);
                subExp.end->next.push_back(subExp.begin);
                parsingStack.push(subExp);
            }
                break;
            case '.': {
                if (parsingStack.size() < 2) {
                    throw RegularExpressionParseError::defaultError();
                }
                auto secondSubExp = parsingStack.top(); parsingStack.pop();
                auto firstSubExp = parsingStack.top(); parsingStack.pop();
                firstSubExp.end->next.push_back(secondSubExp.begin);
                parsingStack.push(SubNode(firstSubExp.begin, secondSubExp.end));
            }
                break;
            default:
                throw RegularExpressionParseError("Regular Expression may contains only 'a', 'b', 'c', '1', '.', '*', '+'");
                break;
        }
    }
    auto regExp = parsingStack.top(); parsingStack.pop();
    this->begin = regExp.begin;
    this->end = regExp.end;
}

unsigned int Graph:: findMaxPrefixInWord(std::string word) {
    unsigned int ans = 0;
    std::vector<std::vector<char>> reachedVertex(vertexesSize, std::vector<char>(word.size() + 1, 0));
    std::stack<AnsNode> stack;
    stack.push(AnsNode(this->begin, 0));
    
    while (!stack.empty()) {
        auto curAns = stack.top(); stack.pop();
        if (curAns.node == this->end) {
            ans = ans > curAns.ans ? ans : curAns.ans;
        }
        
        for (auto it = curAns.node->next.begin(); it != curAns.node->next.end(); ++it) {
            if (curAns.ans == word.size()) {
                continue;
            }
            if(!reachedVertex[(*it)->id][curAns.ans] && (*it)->symbol == Node::Eps()) {
                reachedVertex[(*it)->id][curAns.ans] = 1;
                stack.push(AnsNode(*it, curAns.ans));
            }
            if (((*it)->symbol == word[curAns.ans]) && !reachedVertex[(*it)->id][curAns.ans + 1]) {
                reachedVertex[(*it)->id][curAns.ans + 1] = 1;
                stack.push(AnsNode(*it, curAns.ans + 1));
            }
        }
    }
    
    return ans;
}

Node * Graph:: createNewNode(const char symbol) {
    auto instance = new Node(symbol, vertexesSize);
    vertexesSize++;
    return instance;
}