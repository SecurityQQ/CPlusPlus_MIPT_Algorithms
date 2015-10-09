//
//  BinarySearchTree.h
//  HaffmanCode
//
//  Created by Александр Малышев on 07.12.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//

#ifndef __HaffmanCode__BinarySearchTree__
#define __HaffmanCode__BinarySearchTree__

//#include <stdio.h>
#include "CNode.h"

template <class T>
class BinarySearchTree: CNode<T> {
    
public:
    BinarySearchTree() {
        root = new CNode<T>*(sizeof(CNode<T>));
        root->value = NULL;
        root->left = NULL;
        root->right = NULL;
    }
    ~BinarySearchTree() {
        //
    }
    
    CNode<T>* root;
    
    //! Methods:
    
    CNode<T>* search(CNode<T>* node, T key) {
        if( key == node->value) {
            return node;
        }
        if( key > node->value ) {
            return search(node->right, key);
        } else {
            return search(node->left, key);
        }
    }
    
    CNode<T>* min(CNode<T>* root) {
        
    }
    
    CNode<T>* max(CNode<T>* root) {
        
    }
    
    CNode<T>* insert(CNode<T>* root, T value) {
        if( root-> value >= value ) {
            if( root->right == NULL ) {
                CNode<T>* insertingNode = new CNode<T>*(sizeof(CNode<T>));
                insertingNode->value = value;
                root->right = insertingNode;
            } else {
                return insert(root->right, value);
            }
        } else {
            if( root-> left == NULL ) {
                CNode<T>* insertingNode = new CNode<T>*(sizeof(CNode<T>));
                insertingNode->value = value;
                root->left = insertingNode;
            } else {
                return insert(root->left, value);
            }
        }
    }
    
    CNode<T>* remove(CNode<T>* root, CNode<T>* node) {
        
    }
    
    int getRandomNumber(size_t seed) {
        
        return 41;
    }
};




#endif /* defined(__HaffmanCode__BinarySearchTree__) */
