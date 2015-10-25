//
//  Graph.h
//  PrefixParser
//
//  Created by Alexander Malyshev on 25.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef Graph_h
#define Graph_h
#include <vector>
#include <string>

typedef unsigned int IDType;

class Node {
public:
    Node(const char symbol, const IDType id): symbol(symbol), id(id) {}
    char symbol;
    IDType id;
    std::vector<Node *> next;
    static char Eps() {
        return 'e';
    }
};

class SubNode { //Need for creating sub-regExp automata
public:
    Node *begin;
    Node *end;
    SubNode(Node *begin, Node *end): begin(begin), end(end) {}
};

class AnsNode {
public:
    Node *node;
    unsigned int ans;
    AnsNode(Node *node, const unsigned int ans): node(node), ans(ans) {}
};

class Graph {
public:
    Graph(const std::string regularExpression); ///throws
                                                //regexp should be in Reverse Polish notation https://en.wikipedia.org/wiki/Reverse_Polish_notation
    ~Graph() {}
    Node *begin;
    Node *end;
    unsigned int findMaxPrefixInWord(const std::string word);
private:
    Node *createNewNode(const char symbol);
    IDType vertexesSize;
};

class RegularExpressionParseError: public std::string {
    
public:
    static RegularExpressionParseError defaultError() {
        static auto instance = RegularExpressionParseError("(Can't parse regular expression. Regular Expression should be in Reverse Polish notation (https://en.wikipedia.org/wiki/Reverse_Polish_notation))");
        return instance;
    }
    
    RegularExpressionParseError(std::string message) {
        this->message = message;
    }

    const std::string description() {
        return "Program ended with exit code: 1 (" + message + ")";
    }
    
private:
    std::string message;
};


#endif /* Graph_h */
