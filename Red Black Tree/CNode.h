//
//  CNode.h
//  Red Black Tree
//
//  Created by Александр Малышев on 23.05.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#ifndef Red_Black_Tree_CNode_h
#define Red_Black_Tree_CNode_h

enum Color {
    BLACK = 0,
    RED = 1
};

template <class T>
struct CNode {
    CNode *parent;
    CNode *left;
    CNode *right;
    Color color;
    T key;
    CNode() : parent(nullptr), left(nullptr), right(nullptr) {}
};

#endif
