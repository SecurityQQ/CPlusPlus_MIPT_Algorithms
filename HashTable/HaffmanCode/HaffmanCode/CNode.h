//
//  CNode.h
//  HaffmanCode
//
//  Created by Александр Малышев on 07.12.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//

#ifndef HaffmanCode_CNode_h
#define HaffmanCode_CNode_h

#define EmptyNodeIdentifier (-1)
#define MaxCodeSize (32)
template <class T>
class CNode {
public:
    T value;
    float propability;
    CNode<T> *left;
    CNode<T> *right;
    char code[MaxCodeSize] = "";
    CNode() {
        left = NULL;
        right = NULL;
        value = 0;
        propability = 0;
    }
};

#endif
