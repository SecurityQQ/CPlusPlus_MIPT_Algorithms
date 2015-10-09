 //
//  CNodeArray.h
//  HaffmanCode
//
//  Created by Александр Малышев on 11.12.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//

#ifndef HaffmanCode_CNodeArray_h
#define HaffmanCode_CNodeArray_h

#include <iostream>
#include "CNode.h"
#include "Heap\Array.h"
#include <assert.h>


template <class T>
class CNodeArray: public Array<CNode<T>> {
public:
    CNodeArray<T>() : Array<CNode<T>>() {}
    CNodeArray<T>(int size) : Array<CNode<T>>(size) {}
    CNodeArray<T>(int size, int defaultParam) {
        for( int i = 0; i < size; ++i ) {
            CNode<T> defaultNode;
            defaultNode.value = defaultParam;
            defaultNode.propability = 0;
            Array<CNode<T>>::push_back(defaultNode);
        }
    }
    
    void deleteUnusedItems() {
        int i = Array<CNode<T>>::length - 1;
        while( i >= 0 ) {
            if( Array<CNode<T>>::buffer[i].propability == 0 || Array<CNode<T>>::buffer[i].value == EmptyNodeIdentifier ) {
                Array<CNode<T>>::pop(i);
            }
            --i;
        }
    }
    
    //<#TODO: DEFINES AND WRAPPERS#>
    CNode<T> transformHeapIntoBinarySearchTree(Array<CNode<T>> &binarySearchTree) {
        CNode<T> root;
        while( Array<CNode<T>>::length > 1 ) {
            int indMin = 2;
            if( ( Array<CNode<T>>::buffer[2].propability > Array<CNode<T>>::buffer[1].propability ) ||
               ( Array<CNode<T>>::length == 2 ) ) {
                indMin = 1;
            }
            float extractedProp = Array<CNode<T>>::buffer[0].propability + Array<CNode<T>>::buffer[indMin].propability;
            CNode<T> node;
            node.propability = extractedProp;
            node.value = EmptyNodeIdentifier;
            
            binarySearchTree.push_back(Array<CNode<T>>::buffer[0]);
            node.left = &binarySearchTree[binarySearchTree.size() - 1];
            binarySearchTree.push_back(Array<CNode<T>>::buffer[indMin]);
            node.right = &binarySearchTree[binarySearchTree.size() - 1];
            binarySearchTree.push_back(node);
            Array<CNode<T>>::buffer[0] = binarySearchTree[binarySearchTree.size() - 1];
        
            std::swap(Array<CNode<T>>::buffer[indMin], Array<CNode<T>>::buffer[Array<CNode<T>>::length - 1]);
            Array<CNode<T>>::pop(Array<CNode<T>>::length - 1);
            
            //restoring heap properties:
            if( indMin != Array<CNode<T>>::length - 1 ) {
                Array<CNode<T>>::heapify(indMin);
            }
            Array<CNode<T>>::heapify(0);
        }
        root = binarySearchTree[binarySearchTree.size() - 1];
        
        return root;
}


//    void makeLinks() {
//        for( int i = 0; i < heap.size(); ++i ) {
//            heap[i].left = heap[2 * i + 1];
//            heap[i].right = heap[2 * i + 2];
//        }
//    }


};
#endif