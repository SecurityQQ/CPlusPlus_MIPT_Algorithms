//
//  RBTree.h
//  Red Black Tree
//
//  Created by Александр Малышев on 18.05.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#ifndef Red_Black_Tree_RBTree_h
#define Red_Black_Tree_RBTree_h

template <class T>
class RBTree;


template <class T>
class RBTree {
    enum Color {
        BLACK = 0,
        RED = 1
    };
    
    struct CNode {
        CNode *parent;
        CNode *left;
        CNode *right;
        Color color;
        T key;
        CNode(T key) : parent(nullptr), left(nullptr), right(nullptr), key(key), color(RED){}
        CNode(CNode *parent, T key) : parent(parent), left(nullptr), right(nullptr), key(key), color(RED){}
    };
    typedef std::function<int (const T elem, const T elem2)> CompareFunction;

public:
    RBTree(CompareFunction compareFunction) : compFunc(compareFunction), root(nullptr) {}
    RBTree(int compareFunction(const T elem, const T elem2)) : compFunc(compareFunction), root(nullptr) {}
    ~RBTree();
    
    void add(const T key);
    bool search(const T key) const;
    void remove(const T key);

private:
    
    CNode *root;
//  CNode *getGrandparent(CNode *node);
//  CNode *getUncle(CNode *node);

    CompareFunction compFunc;

    void _insertCase1(CNode *node);
    void _insertCase2(CNode *node);
    void _insertCase3(CNode *node);
    void _insertCase4(CNode *node);
    void _insertCase5(CNode *node);
    void _rotateLeft (CNode *node);
    void _rotateRight(CNode *node);
  
    
    void _deleteCase0(CNode *&node);
    void _deleteCase1(CNode *&node);
    void _deleteCase2(CNode *&node);
    void _deleteCase3(CNode *&node);
    void _deleteCase4(CNode *&node);
    void _deleteCase5(CNode *&node);
    void _deleteCase6(CNode *&node);
    
    void _deinit(CNode *&node);
    
///-----------------------------------------
///-----------------------------------------
    
    

    
CNode* getGrandparent(const CNode *node) const {
    if ((node != nullptr) && (node->parent != nullptr)) {
        return node->parent->parent;
    } else {
        return nullptr;
    }
}

CNode *getUncle(const CNode *node) const {
    CNode *granny = getGrandparent(node);
    if (granny == nullptr) {
        return granny;
    }
    if (granny->left == node->parent) {
        return granny->right;
    } else {
        return granny->left;
    }
}
    
CNode *getBrother(const CNode *node) const {
    if (node->parent == nullptr) {
        return nullptr;
    }
    return (node->parent->left == node) ? node->parent->right : node->parent->left;
}
  
CNode * _find(CNode *node, const T key) const{
    if (node == nullptr) {
        return nullptr;
    }
    int compRes = compFunc(key, node->key);
    if (compRes == 0) {
        return node;
    } else if (compRes < 0) {
        return _find(node->left, key);
    }
    return _find(node->right, key);
}
    
CNode *_getMin(CNode *node) const {
    
    if (node == nullptr) {
        return nullptr;
    }
    
    if (node->right == nullptr) {
        return node;
    }
    CNode *tmp = node->right;
    while (tmp->left != nullptr) {
        tmp = tmp->left;
    }
    return tmp;
}

Color getColor(CNode *node) {
    if (node == nullptr) {
        return BLACK;
    }
    return node->color;
}

    
CNode *_search(CNode *node, T key) const{
    if (node == nullptr) {
        return nullptr;
    }
    if (node->value == key) {
        return node;
    }
    return _search(compFunc(key, node->value) < 0 ? node->left : node->right, key);
}
    
};



template <class T>
RBTree<T>::~RBTree() {
    _deinit(root);
}

template <class T>
void RBTree<T>:: _deinit(CNode *&node) {
    if (node == nullptr) {
        return;
    }
    _deinit(node->left);
    _deinit(node->right);
    delete node;
    node = nullptr;
}

template <class T>
void RBTree<T>:: add(const T key) {
    CNode *prev = root;
    CNode *curNode = root;
    
    while (curNode != nullptr) {
        int compRes = compFunc(key, curNode->key);
        if (compRes < 0) {
            prev = curNode;
            curNode = curNode->left;
        }
        if (compRes > 0) {
            prev = curNode;
            curNode = curNode->right;
        }
        if (compRes == 0) {
            return;
        }
    }
    
    if (prev == curNode) {
        root = new CNode(nullptr, key);
        curNode = root;
    } else {
        curNode = new CNode(prev, key);
        if (compFunc(prev->key, curNode->key) < 0) {
            prev->right = curNode;
        } else {
            prev->left = curNode;
        }
    }
    
    _insertCase1(curNode);
    
    
}


template <class T>
void RBTree<T>:: _insertCase1(CNode *node) {
    
    if (node->parent == nullptr) {
        node->color = BLACK;
    } else {
        _insertCase2(node);
    }
}

template <class T>
void RBTree<T>:: _insertCase2(CNode *node) {
    
    if (getColor(node->parent) == BLACK)
        return;
    else {
        _insertCase3(node);
    }
}

template <class T>
void RBTree<T>:: _insertCase3(CNode *node) {
    
    CNode *uncle = getUncle(node);
    if ((uncle != nullptr) && (getColor(uncle) == RED) && (getColor(node->parent) == RED)) {
        node->parent->color = BLACK;
        uncle->color = BLACK;
        CNode *granny = getGrandparent(node);
        granny->color = RED;
        
        _insertCase1(granny);
    } else {
        _insertCase4(node);
    }
}

template <class T>
void RBTree<T>:: _insertCase4(CNode *node) {
    
    CNode *granny = getGrandparent(node);
    if ((node == node->parent->right) && (granny->left == node->parent)) {
        _rotateLeft(node->parent);
        node = node->left;
    } else if ((node == node->parent->left) && (node->parent == granny->right)) {
        _rotateRight(node->parent);
        node = node->right;
    }
    _insertCase5(node);
}

template <class T>
void RBTree<T>:: _insertCase5(CNode *node) {
    
    CNode *granny = getGrandparent(node);
    node->parent->color = BLACK;
    granny->color = RED;
    if ((node == node->parent->left) && (node->parent == granny->left)) {
        
        _rotateRight(granny);
        
    } else {
        _rotateLeft(granny);
    }
}


template <class T>
void RBTree<T>:: _rotateLeft(CNode* node) {
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
}

template <class T>
void RBTree<T>:: _rotateRight(CNode *node) {
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
}
template <class T>
void RBTree<T>:: remove(const T key) {
    
    CNode *node = _find(root, key);
    if (node == nullptr) {
        return;
    }
    CNode *realDel = _getMin(node);
    std::swap(node->key, realDel->key);
    
    _deleteCase0(realDel);
    
    
}

template <class T>
void RBTree<T>:: _deleteCase0(CNode *&node) {
    CNode *child;
    
    if (node->right == nullptr) {
        child = node->left;
    } else {
        child = node->right;
    }
    
    
    if (child != nullptr) {
        //replacing child and node:
        
        child->parent = node->parent;
        if (node == node->parent->left) {
            node->parent->left = child;
        } else {
            node->parent->right = child;
        }
        
        
        if (getColor(node) == BLACK) {
            if (getColor(child) == RED) {
                child->color = BLACK;
            } else {
                _deleteCase1(child);
            }

        }
        delete node;
    } else { //child is nullptr:
        
        if (node->parent->left == node) {
            node->parent->left = nullptr;
        } else {
            node->parent->right = nullptr;
        }
        
        if (getColor(node) == RED) {
            delete node;
        } else {
            CNode *parent = node->parent;
            delete node;
            _deleteCase1(parent);
            
        }
    }
}

template <class T>
void RBTree<T>:: _deleteCase1(RBTree::CNode *&node) {
    //if root all ok, else :
    if (node->parent != NULL) {
        _deleteCase2(node);
    }
    
}

template <class T>
void RBTree<T>:: _deleteCase2(RBTree::CNode *&node) {
    //bro is RED
    CNode *bro = getBrother(node);
    if (bro != nullptr) {
        if (getColor(bro) == RED) {
            bro->color = BLACK;
            node->parent->color = RED;
            if (node == node->parent->left) {
                _rotateLeft(node->parent);
            } else {
                _rotateRight(node->parent);
            }
        }
    }
    _deleteCase3(node);
}

template <class T>
void RBTree<T>:: _deleteCase3(RBTree::CNode *&node) {
    //all blacks
    CNode *bro = getBrother(node);
    if (getColor(node->parent) == BLACK) {
        if (bro != nullptr) {
            if ((getColor(bro) == BLACK) &&
                (getColor(bro->left) == BLACK) &&
                (getColor(bro->right) == BLACK)) {
                bro->color = RED;
            }
        }
        _deleteCase1(node->parent);
    } else {
        _deleteCase4(node);
    }
}

template <class T>
void RBTree<T>:: _deleteCase4(RBTree::CNode *&node) {
    //their's parent is red
    CNode *bro = getBrother(node);
    
    if (getColor(node->parent) == RED) {
        if (bro != nullptr) {
            if (    (getColor(bro) == BLACK) &&
                    (getColor(bro->left) == BLACK) &&
                    (getColor(bro->right) == BLACK)) {
                bro->color = RED;
            }
        }
        node->parent->color = BLACK;
    } else {
        _deleteCase5(node);
    }
}

template <class T>
void RBTree<T>:: _deleteCase5(RBTree::CNode *&node) {
    //bro has a red left child
    CNode *bro = getBrother(node);
    if (bro != nullptr) {
        if  (getColor(bro) == BLACK) {
            if (    (node == node->parent->left) &&
                    (getColor(bro->right) == BLACK) &&
                    (getColor(bro->left) == RED)
                ) {
                bro->color = RED;
                bro->left->color = BLACK;
                _rotateRight(bro);
            } else if ((getColor(bro->left) == BLACK) &&
                       (getColor(bro->right) == RED)) {
                    bro->color = RED;
                    bro->right->color = BLACK;
                    _rotateLeft(bro);
            }
        }
    }
    _deleteCase6(node);
}

template <class T>
void RBTree<T>:: _deleteCase6(RBTree::CNode *&node) {
    CNode *bro = getBrother(node);
    
    if (bro != nullptr) bro->color = node->parent->color;
    node->parent->color = BLACK;
    
    if (node == node->parent->left) {
        if (bro != nullptr) bro->right->color = BLACK;
        _rotateLeft(node->parent);
    } else {
        if (bro != nullptr) bro->left->color = BLACK;
        _rotateRight(node->parent);
    }
}

template <class T>
bool RBTree<T>:: search(const T key) const {
    return (_search(root, key) == nullptr) ? false : true;
}


#endif
