//
//  CNodeHeap.h
//  HaffmanCode
//
//  Created by Александр Малышев on 11.12.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//

#ifndef HaffmanCode_CNodeHeap_h
#define HaffmanCode_CNodeHeap_h

#include "CNode.h"
#include "Heap\Array.h"

template <class T>
class CNodeHeap {
public:
    CNode<T>* root;
    CNode<T> buildHeap(T* const data, size_t sizeOfData) {
        
        for( int i = 0; i < sizeOfData; ++i ) {
            CNode<T> foo;
            foo.value = data[i].value;
            foo.propability = data[i].propability;
            heap.push_back(foo);
        }
        heap.buildHeap();
    }
    
    CNode<T> heapify();
    
private:
    Array<CNode<T>> heap;
};





#endif