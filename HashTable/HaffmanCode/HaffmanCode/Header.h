//
//  CNode.h
//  HaffmanCode
//
//  Created by Александр Малышев on 07.12.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//

#ifndef HaffmanCode_CNode_h
#define HaffmanCode_CNode_h

template <class T>
class CNode {
public:
    T value;
    CNode<T> *next;
};

#endif
