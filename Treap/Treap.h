//
//  Treap.h
//  Treap
//
//  Created by Александр Малышев on 19.04.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#ifndef __Treap__Treap__
#define __Treap__Treap__

#include <stdio.h>
#include "NaiveBST.h"

typedef int IndexType;
typedef int PriorType;

template <class T>
class Treap: public NaiveBST<T> {

    
public:
    typedef std::function<int (const T elem, const T elem2)> CompareFunction;
    
    Treap(CompareFunction CompareFunction);
    Treap(int compareFunction(const T elem, const T elem2));
    ~Treap();
    
    void add(T value, PriorType prior = rand());
    void remove(T value);
    bool search(T value);
    
    
private:
    struct CNode {
        T value;
        PriorType prior;
        CNode *left;
        CNode *right;
        CNode() : left(nullptr), right(nullptr) { }
        CNode(T value, IndexType prior): value(value), prior(prior), left(nullptr), right(nullptr) {}
    };
    CompareFunction compFunc;
    CNode *root;
    
    IndexType  _height(CNode *node) const;
    IndexType  _width (CNode *node, IndexType level) const;
    void       _split (CNode *node, int value, CNode * &leftTree, CNode * &rightTree);
    void       _merge (CNode * &node, CNode *&left, CNode *&right);
    void       _add   (CNode * &node, CNode *&elem);
    void       _remove(CNode * &node, T value);
    CNode *    _search(CNode * &node, T value);
    void       _deinit(CNode * &node);
    
    //for width2:
    void _prepareLevelsCount(CNode *node, std::vector<IndexType> &levelsCount) const;
    void      _indexLevels(CNode * &node, int level);
    
    //not allowed constructors:
    Treap();
    Treap(Treap&);
};

template <class T>
Treap<T>::Treap(CompareFunction compareFunction) : NaiveBST<T>(compareFunction) {
    root = nullptr;
    compFunc = compareFunction;
}

template <class T>
Treap<T>::Treap(int compareFunction(const T elem, const T elem2)) : NaiveBST<T>(compareFunction) {
    root = nullptr;
    compFunc = compareFunction;
}

template <class T>
Treap<T>::~Treap() {
    _deinit(root);
}

template <class T>
void Treap<T>:: _deinit(CNode *&node) {
    if (root == nullptr) {
        return;
    }
    _deinit(node->left);
    _deinit(node->right);
    delete node;
    node = nullptr;
}


template <class T>
void Treap<T>:: _split(CNode *node, int value, CNode * &leftTree, CNode * &rightTree) {
    if (node == nullptr) {
        leftTree = nullptr;
        rightTree = nullptr;
        return;
    }
    if (value > node->value) {
        _split(node->right, value, node->right, rightTree);
        leftTree = node;
    } else {
        _split(node->left, value, leftTree, node->left);
        rightTree = node;
    }
}

template <class T>
void Treap<T>:: _merge(CNode * &node, CNode *&left, CNode *&right) {
    if (left == nullptr || right == nullptr) {
        node = (left != nullptr) ? left : right;
        return;
    }
    if (left->prior > right->prior) {
        _merge(left->right, left->right, right);
        node = left;
    } else {
        _merge(right->left, left, right->left);
        node = right;
    }
}

template <class T>
void Treap<T>:: add(T value, PriorType prior) {
    CNode *elem = new CNode(value, prior);
    _add(root, elem);
    
}

template <class T>
void Treap<T>:: _add(CNode * &node, CNode *&elem) {
    if (node == nullptr) {
        node = elem;
        return;
    }
    if (elem->prior > node->prior) {
        _split(node, elem->value, elem->left, elem->right);
        node = elem; 
    } else {
        _add(compFunc(node->value, elem->value) < 0 ? node->right : node->left, elem);
    }
}

template <class T>
void Treap<T>:: remove(T value) {
    _remove(root, value);
}

template <class T>
void Treap<T>:: _remove(Treap::CNode *&node, T value) {
    if (compFunc(node->value, value) == 0) {
        _merge(node, node->left, node->right);
    } else {
        _remove((compFunc(value, node->value) < 0 ? node->left : node->right), value);
    }
}

template <class T>
bool Treap<T>:: search(T value) {
    return NaiveBST<T>:: search(value);
}

#endif /* defined(__Treap__Treap__) */
