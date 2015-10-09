//
//  main.cpp
//  Naive VS Treap (Height)
//
//  Created by Александр Малышев on 20.04.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <functional>
#include <vector>

#define nullptr NULL

int compFunc(const long long a, const long long b) {
    if (a < b) {
        return -1;
    }
    if (a == b) {
        return 0;
    }
    return 1;
}

typedef long long IndexType;
typedef long long PriorType;

template <class T>
class Treap {
    
    
public:
    typedef std::function<int (const T elem, const T elem2)> CompareFunction;
    
    Treap(int CompareFunction);
    Treap(int compareFunction(const T elem, const T elem2));
    ~Treap();
    void add(T value, PriorType prior = rand());
    void remove(T value);
    bool search(T value);
    
    IndexType height() const;
    IndexType width() const;
    
    IndexType width2();
private:
    struct CNode {
        T value;
        IndexType prior;
        CNode *left;
        CNode *right;
        int level;
        CNode() : left(nullptr), right(nullptr), level(0){ }
        CNode(T value, IndexType prior): value(value), prior(prior), left(nullptr), right(nullptr) , level(0){}
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
Treap<T>::Treap(int compareFunction) {
    root = nullptr;
    compFunc = compareFunction;
}

template <class T>
Treap<T>::Treap(int compareFunction(const T elem, const T elem2)) {
    root = nullptr;
    compFunc = compareFunction;
}

template <class T>
Treap<T>::~Treap() {
    _deinit(root);
}

template <class T>
void Treap<T>:: _deinit(CNode *&node) {
    if (node->left != nullptr) {
        _deinit(node->left);
    }
    if (node->right != nullptr) {
        _deinit(node->right);
    }
    if (node != nullptr) {
        delete node;
        node = nullptr;
    }
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
bool Treap<T>:: search(T value) {
    CNode *temp = _search(root, value);
    return temp != nullptr;
}

template <class T>
typename Treap<T>::CNode* Treap<T>:: _search(CNode *&node, T value) {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->value == value) {
        return node;
    }
    return _search(compFunc(value, node->value) < 0 ? node->left : node->right, value);
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
IndexType Treap<T>::height() const {
    return _height(root);
}

template <class T>
IndexType Treap<T>:: _height(CNode *node) const{
    IndexType h1 = 0, h2 = 0;
    if (node == nullptr) {
        return 0;
    }
    h1 = _height(node->left);
    h2 = _height(node->right);
    return std::max(h1, h2) + 1;
}

template <class T>
IndexType Treap<T>:: width() const{
    IndexType width = 0;
    IndexType height = this->height();
    for (int i = 1; i <= height; ++i) {
        width = std::max(width, _width(root, i));
    }
    return width;
}

template <class T>
IndexType Treap<T>:: _width(CNode *node, IndexType level) const {
    if (node == nullptr) {
        return 0;
    }
    if (level == 1) {
        return 1;
    }
    if (level > 1) {
        return _width(node->left, level - 1) + _width(node->right, level - 1);
    }
    return 0;
}

template <class T>
IndexType Treap<T>:: width2() {
    _indexLevels(root, 1);
    int h = height();
    IndexType width = 0;
    std::vector<IndexType> levels(h + 1, 0);
    _prepareLevelsCount(root, levels);
    for (int i = 1; i <= h; ++i) {
        width = std::max(width, levels[i]);
    }
    return width;
}

template <class T>
void Treap<T>:: _prepareLevelsCount(CNode *node, std::vector<IndexType> &levelsCount) const {
    ++levelsCount[node->level];
    if (node->left != nullptr) {
        _prepareLevelsCount(node->left, levelsCount);
    }
    if (node->right != nullptr) {
        _prepareLevelsCount(node->right, levelsCount);
    }
}

template <class T>
void Treap<T>:: _indexLevels(CNode * &node, int level) {
    if (node == nullptr) {
        return;
    }
    node->level = level;
    if (node->left != nullptr) {
        _indexLevels(node->left, level + 1);
    }
    if (node->right != nullptr) {
        _indexLevels(node->right, level + 1);
    }
}

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
    
    IndexType width2();
    
    void visit(std::function<void ()> callBack);
    
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
    CNode * _search(T value);
    IndexType _height(CNode *node) const;
    IndexType _width(CNode *node, IndexType level) const;
    
    //for width2:
    void _prepareLevelsCount(CNode *node, std::vector<IndexType> &levelsCount) const;
    void      _indexLevels(CNode * &node, int level);
    
    //not allowed constructors:
    NaiveBST();
    NaiveBST(NaiveBST&);
};

template <class T>
NaiveBST<T>:: NaiveBST(int compareFunction(const T elem, const T elem2)) {
    root = new CNode;
    _isEmpty = true;
    compFunc = compareFunction;
}

template <class T>
NaiveBST<T>:: NaiveBST(CompareFunction _compFunc) {
    root = new CNode;
     _isEmpty = true;
    compFunc = _compFunc;
}


template <class T>
NaiveBST<T>:: ~NaiveBST() {
    _deinit(root);
}

template <class T>
void NaiveBST<T>:: _deinit(CNode *&node) {
    if (root == nullptr) {
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
}

template <class T>
void NaiveBST<T>:: add(T value) {
    if (_isEmpty) {
        this->root->value = value;
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
    if (_search(value) == nullptr) {
        return false;
    } else {
        return true;
    }
}

template <class T>
typename NaiveBST<T>::CNode * NaiveBST<T>:: _search(T value) {
    if (_isEmpty) {
        return nullptr;
    }
    CNode *iter = root;
    
    while (true) {
        int compResult = compFunc(value, iter->value);
        if (compResult == 0) {
            return iter;
        }
        if (compResult < 0) {
            if (iter->left == nullptr) {
                return nullptr;
            }
            iter = iter->left;
        }
        if (compResult > 0) {
            if (iter->right == nullptr) {
                return nullptr;
            }
            iter = iter->right;
        }
    }
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
    IndexType width = 0;
    IndexType height = this->height();
    for (int i = 1; i <= height; ++i) {
        width = std::max(width, _width(root, i));
    }
    return width;
}

template <class T>
IndexType NaiveBST<T>:: _width(CNode *node, IndexType level) const {
    if (node == nullptr) {
        return 0;
    }
    if (level == 1) {
        return 1;
    }
    if (level > 1) {
        return _width(node->left, level - 1) + _width(node->right, level - 1);
    }
    return 0;
}

template <class T>
IndexType NaiveBST<T>:: width2() {
    _indexLevels(root, 1);
    int h = height();
    IndexType width = 0;
    std::vector<IndexType> levels(h + 1, 0);
    _prepareLevelsCount(root, levels);
    for (int i = 1; i <= h; ++i) {
        width = std::max(width, levels[i]);
    }
    return width;
}

template <class T>
void NaiveBST<T>:: _prepareLevelsCount(CNode *node, std::vector<IndexType> &levelsCount) const {
    if (node == nullptr) {
        return;
    }
    ++levelsCount[node->level];
    _prepareLevelsCount(node->left, levelsCount);
    _prepareLevelsCount(node->right, levelsCount);
}

template <class T>
void NaiveBST<T>:: _indexLevels(CNode * &node, int level) {
    if (node == nullptr) {
        return;
    }
    node->level = level;
    if (node->left != nullptr) {
        _indexLevels(node->left, level + 1);
    }
    if (node->right != nullptr) {
        _indexLevels(node->right, level + 1);
    }
}

int main(int argc, const char * argv[]) {
    NaiveBST<long long> naive(compFunc);
    Treap<long long> treap(compFunc);
    int N;
    long long x, y;
    
//    srandom(time(NULL));
//    N = 1000000;
//    for (int i = 0; i < N; ++i) {
//        x = random();
//        y = random();
//        treap.add(x, y);
//        naive.add(x);
//    }
    
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%lld %lld", &x, &y);
        treap.add(x, y);
        naive.add(x);
    }
    
    printf("%lld\n", treap.width2() - naive.width2() );
//    printf("%lld\n", treap.height() - naive.height() );
    
    return 0;
}
