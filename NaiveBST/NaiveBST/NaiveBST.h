//
//  NaiveBST.h
//  NaiveBST
//
//  Created by Александр Малышев on 09.04.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#ifndef __NaiveBST__NaiveBST__
#define __NaiveBST__NaiveBST__

#include <stdio.h>
#include <functional>
#include <vector>

typedef int IndexType;

template <class T>
class NaiveBST;

template <class T>
class NaiveBST {
    
public:
    typedef std::function<int (const T elem, const T elem2)> CompareFunction;
    
    NaiveBST(int compareFunction(const T elem, const T elem2));
    NaiveBST(CompareFunction _compFunc);
    ~NaiveBST();
    
    void add(T value);
    void remove(T value);
    bool isEmpty() const { return _isEmpty; }
    bool search(T value);
    IndexType height() const;
    IndexType width() const;
    void visit(std::function<void ()> callBack);
    
    void erase() { _deinit(root); }
    
private:
    bool _isEmpty;
    struct CNode {
        CNode *left;
        CNode *right;
        T value;
        int level;
        CNode() {
            left = nullptr;
            right = nullptr;
            level = 0;
        }
        CNode(T _value) {
            left = nullptr;
            right = nullptr;
            value = _value;
            level = 0;
        }
    };
    void _deinit(CNode *&node);
    CNode *root;
    CompareFunction compFunc;
    CNode *   _search(CNode *&node, T value);
    IndexType _height(CNode *node) const;
    IndexType _width(CNode *node, int level) const;
    void       _prepareLevelsCount(CNode *node, std::vector<IndexType> &levelsCount, int level) const;
    //not allowed constructors:
    NaiveBST();
    NaiveBST(NaiveBST&);
};

template <class T>
NaiveBST<T>:: NaiveBST(int compareFunction(const T elem, const T elem2)) {
    root = nullptr;
    _isEmpty = true;
    compFunc = compareFunction;
}

template <class T>
NaiveBST<T>:: NaiveBST(CompareFunction _compFunc) {
    root = nullptr;
    _isEmpty = true;
    compFunc = _compFunc;
}


template <class T>
NaiveBST<T>:: ~NaiveBST() {
    _deinit(root);
}


template <class T>
void NaiveBST<T>:: _deinit(CNode *&node) {
    if (node == nullptr) {
        return;
    }
    if (node->left != nullptr) {
        _deinit(node->left);
    }
    if (node->right != nullptr) {
        _deinit(node->right);
    }
    delete node;
    node = nullptr;
    _isEmpty = true;
}

template <class T>
void NaiveBST<T>:: add(T value) {
    if (_isEmpty) {
        root = new CNode(value);
        _isEmpty = false;
        return;
    }
    CNode *insElem = root;
    
    while (true) {
        int compResult = compFunc(value, insElem->value);
        if (compResult == 0) {
            return;
        }
        if (compResult < 0) {
            if (insElem->left == nullptr) {
                insElem->left = new CNode(value);
                return;
            } else {
                insElem = insElem->left;
            }
        }
        if (compResult > 0) {
            if (insElem->right == nullptr) {
                insElem->right = new CNode(value);
                return;
            } else {
                insElem = insElem->right;
            }
        }
    }
}
//
template <class T>
void NaiveBST<T>:: remove(T value) {
    if (_isEmpty) {
        return;
    }
    CNode *delNode = root;
    CNode *prev = delNode;
    while (true) {
        int compResult = compFunc(value, delNode->value);
        if (compResult < 0) {
            if (delNode->left == nullptr) {
                return;
            }
            prev = delNode;
            delNode = delNode->left;
        }
        if (compResult > 0) {
            if (delNode->right == nullptr) {
                return;
            }
            prev = delNode;
            delNode = delNode->right;
        }
        
        /// Node found:
        if (compResult == 0) {
            /// case 1:
            if (delNode->left == nullptr && delNode->right == nullptr) {
                if (prev != delNode) {
                    if (prev->left == delNode) {
                        prev->left = nullptr;
                    } else {
                        prev->right = nullptr;
                    }
                } else {
                    _isEmpty = true;
                    root = nullptr;
                }
                delete delNode;
                return;
            }
            /// case 2r:
            if (delNode->right != nullptr) {
                if (delNode->right->left == nullptr) {
                    prev->right = delNode->right;
                    prev->right->left = delNode->left;
                    delete delNode;
                    return;
                }
                /// case 3r:
                CNode *top = delNode;
                prev = delNode;
                delNode = delNode->right;
                while (delNode->left != nullptr) {
                    prev = delNode;
                    delNode = delNode->left;
                }
                std::swap(top->value, delNode->value);
                prev->left = delNode->right;
                delete delNode;
                return;
            }
            /// case 2l:
            if (delNode->left != nullptr) {
                if (delNode->left->right == nullptr) {
                    prev->left = delNode->left;
                    prev->left->right = delNode->right;
                    delete delNode;
                    return;
                }
                /// case 3l:
                CNode *top = delNode;
                prev = delNode;
                delNode = delNode->left;
                while (delNode->right != nullptr) {
                    prev = delNode;
                    delNode = delNode->right;
                }
                std::swap(top->value, delNode->value);
                prev->right = delNode->left;
                delete delNode;
                return;
            }
        }
    }
    
}



template <class T>
bool NaiveBST<T>:: search(T value) {
    CNode *temp = _search(root, value);
    return temp != nullptr;
}

template <class T>
typename NaiveBST<T>::CNode* NaiveBST<T>:: _search(CNode *&node, T value) {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->value == value) {
        return node;
    }
    return _search(compFunc(value, node->value) < 0 ? node->left : node->right, value);
}

template <class T>
IndexType NaiveBST<T>::height() const {
    return _height(root);
}

template <class T>
IndexType NaiveBST<T>:: _height(CNode *node) const{
    IndexType h1 = 0, h2 = 0;
    if (node == nullptr) {
        return 0;
    }
    h1 = _height(node->left);
    h2 = _height(node->right);
    return std::max(h1, h2) + 1;
}

template <class T>
IndexType NaiveBST<T>:: width() const{
    int h = height();
    IndexType width = 0;
    std::vector<IndexType> levels(h + 1, 0);
    _prepareLevelsCount(root, levels, 1);
    for (int i = 1; i <= h; ++i) {
        width = std::max(width, levels[i]);
    }
    return width;
}

template <class T>
void NaiveBST<T>:: _prepareLevelsCount(CNode *node, std::vector<IndexType> &levelsCount, int level) const {
    ++levelsCount[level];
    if (node->left != nullptr) {
        _prepareLevelsCount(node->left, levelsCount, level + 1);
    }
    if (node->right != nullptr) {
        _prepareLevelsCount(node->right, levelsCount, level + 1);
    }
}

#endif /* defined(__NaiveBST__NaiveBST__) */
