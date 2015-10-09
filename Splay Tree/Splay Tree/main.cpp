//
//  main.cpp
//  Splay Tree
//
//  Created by Александр Малышев on 01.05.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <iostream>
#include <functional>



template <class T>
class SplayTree {
    
    typedef std::function<int (const T elem, const T elem2)> CompareFunction;
    
private:
    
    struct CNode {
        CNode *left;
        CNode *right;
        CNode *parent;
        T value;
        CNode(T value): value(value), left(nullptr), right(nullptr), parent(nullptr) {}
    };
    
    CNode *root;
    CompareFunction compFunc;
    
    CNode *rotateLeft(CNode* node) {
        CNode *r = node->right;
        if( r != nullptr ) {
            node->right = r->left;
            if( r->left != nullptr ) {
                r->left->parent = node;
            }
            r->parent = node->parent;
        }
        
        if( node->parent == nullptr ) {
            root = r;
        } else {
            if( node == node->parent->left ) {
                node->parent->left = r;
            } else {
                node->parent->right = r;
            }
        }
        
        if( r != nullptr ) {
            r->left = node;
        }
        node->parent = r;
        return r;
    }
    
    CNode *rotateRight(CNode *node) {
        CNode *l = node->left;
        if( l != nullptr ) {
            node->left = l->right;
            if( l->right != nullptr ) {
                l->right->parent = node;
            }
            l->parent = node->parent;
        }
        
        if( node->parent == nullptr ) {
            root = l;
        } else {
            if( node == node->parent->right ) {
                node->parent->right = l;
            } else {
                node->parent->left = l;
            }
        }
        
        if( l != nullptr ) {
            l->right = node;
        }
        node->parent = l;
        return l;
    }
    
    
    
    void splay(CNode *node) {
        while (node->parent != nullptr) {
            
            if( node->parent->parent == nullptr ) { //zig
                if (node->parent->left == node) {
                    node = rotateRight(node->parent);
                    continue;
                } else {
                    node = rotateLeft(node->parent);
                    continue;
                }
            }
            CNode *g = node->parent->parent;
            CNode *p = node->parent;
            
            if( g->left == p && p->left == node ) { //left zig-zig
                p = rotateRight(g);
                node = rotateRight(p);
                continue;
            }
            if (g->right == p && p->right == node) { //right zig-zig
                p = rotateLeft(g);
                node = rotateLeft(p);
                continue;
            }
            if (g->left == p && p->right == node) { //left-right zig-zag
                node = rotateLeft(p);
                node = rotateRight(g);
                continue;
            }
            if (g->right == p && p->left == node) { //right-left zig-zag
                node = rotateRight(p);
                node = rotateLeft(g);
                continue;
            }
        }
        
    }
    
    CNode *_find(CNode *node, T value) {
        if (node == nullptr) {
            return nullptr;
        }
        int cmpRes = compFunc(node->value, value);
        if ( cmpRes == 0 ) {
            return node;
        }
        if ( cmpRes < 0 ) {
            return _find(node->right, value);
        }
        return _find(node->left, value);
    }
    
    CNode *_findMin(CNode *node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    
    void _deinit(CNode *&node);
    
    void _swap(CNode *&u, CNode *&v) {
        if (u->parent == nullptr) {
            root = v;
        } else {
            if (u == u->parent->left) {
                u->parent->left = v;
            } else {
                u->parent->right = v;
            }
        }
        if (v != nullptr) {
            v->parent = u->parent;
        }
    }
    
public:
    
    SplayTree(CompareFunction compareFunction) : compFunc(compareFunction), root(nullptr) {}
    SplayTree(int compareFunction(const T elem, const T elem2)) : compFunc(compareFunction), root(nullptr) {}
    ~SplayTree();
    
    void add(const T value);
    bool find(const T value);
    void remove(const T value);
};

template <class T>
void SplayTree<T>:: _deinit(SplayTree::CNode *&node) {
    if (node == nullptr) {
        return;
    }
    _deinit(node->left);
    _deinit(node->right);
    delete node;
    node = nullptr;
}


template <class T>
SplayTree<T>:: ~SplayTree<T>() {
    _deinit(root);
}

template <class T>
void SplayTree<T>:: add(const T value) {
    if (root == nullptr) {
        root = new CNode(value);
        return;
    }
    
    CNode *parent = nullptr;
    CNode *newNode = root;
    
    while (newNode != nullptr) {
        if (compFunc(value, newNode->value) < 0) {
            parent = newNode;
            newNode = newNode->left;
            continue;
        }
        if (compFunc(value, newNode->value) > 0) {
            parent = newNode;
            newNode = newNode->right;
            continue;
        }
        if (compFunc(value, newNode->value) == 0) {
            return;
        }
    }
    
    newNode = new CNode(value);
    newNode->parent = parent;
    if (parent != nullptr) {
        if (compFunc(newNode->value, parent->value) < 0) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    }
    splay(newNode);
}

template <class T>
bool SplayTree<T>:: find(const T value) {
    CNode *elem = _find(root, value);
    if (elem == nullptr) {
        return false;
    }
    splay(elem);
    return true;
}

template <class T>
void SplayTree<T>:: remove(const T value) {
    CNode *delNode = _find(root, value);
    if (delNode == nullptr) {
        return;
    }
    
    splay(delNode);
    
    
    if (delNode->right == nullptr) {
        _swap(delNode, delNode->left);
    } else {
        if (delNode->left == nullptr) {
            _swap(delNode, delNode->right);
        } else {
            CNode *min = _findMin(delNode->right);
            if (min->parent != delNode) {
                _swap(min, min->right);
                min->right = delNode->right;
                min->right->parent = min;
            }
            _swap(delNode, min);
            min->left = delNode->left;
            min->left->parent = min;
        }
    }
    delete delNode;
}


int compInt(const int a, const int b) {
    return a - b;
}

void debug() {
    SplayTree<int> tree(compInt);
    int value;
    
    char ch;
    int k, prior;
    while( !std::cin.fail() ) {
        ch = EOF;
        std::cin>> ch >> k;
        switch (ch) {
            case '+':
//                if ( tree.add(k) == AVL_OK ) {
                    tree.add(k);
                    std::cout<<"OK\n";
//                }
                break;
            case '?':
                if (tree.find(k)) {
                    std::cout<<"OK\n";
                } else {
                    std::cout<<"FALSE\n";
                }
                break;
            case '-':
                    tree.remove(k);
                    std::cout<<"OK\n";
                break;
                //            case '.':
                //                std::cout<<"Height: " <<bst.height() <<std::endl;
                //                break;
                //            case ',':
                //                std::cout<<"Width: " <<bst.width() <<std::endl;
                //                break;
            default:
                exit(0);
                try {
                    throw "Incorrect operation";
                } catch (char * errorMsg) {
                    std::cerr<< errorMsg <<std::endl;
                    exit(1);
                }
                break;
        }
    }
}

int main(int argc, const char * argv[]) {
    debug();
    return 0;
}
