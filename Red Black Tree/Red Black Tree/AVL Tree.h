//
//  AVL Tree.h
//  Red Black Tree
//
//  Created by Александр Малышев on 25.05.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#ifndef Red_Black_Tree_AVL_Tree_h
#define Red_Black_Tree_AVL_Tree_h

#define AVL_OK 0
#define AVL_ERR (-1)

template <class T>
class AVLTree {
public:
    typedef std::function<int (const T elem, const T elem2)> CompareFunction;
    
    AVLTree(CompareFunction compareFunction);
    AVLTree(int compareFunction(const T elem, const T elem2));
    ~AVLTree();
    
    int add(T value) {
        root = add(root, value);
        return AVL_OK;
    }
    
    int remove(T value) {
        root = remove(root, value);
        return AVL_OK;
    }
    
    T getKthStat(int k) {
        if (k > num(root)) {
            return (T)AVL_ERR;
        }
        int index = (root == nullptr) ? 0 : num(root->left);
        CNode *kth = getKthStat(root, k, index);
        if (kth == nullptr) {
            return (T)AVL_ERR;
        }
        return kth->value;
    }
    
    bool search(T value);
    
    
private:
    
    struct CNode {
        CNode *left;
        CNode *right;
        short height;
        T value;
        int nums;
        CNode(T value): value(value), left(nullptr), right(nullptr), height(1), nums(1) {}
    };
    
    CNode *root;
    CompareFunction compFunc;
    
    CNode *getKthStat(CNode *node, int k, int nodeIndex) {
        
        if ( nodeIndex == k ) {
            return node;
        }
        if ( nodeIndex < k ) {
            if (node->right == nullptr) {
                return nullptr;
            }
            return getKthStat(node->right, k, nodeIndex + num(node->right->left) + 1);
        }
        if (node->left == nullptr) {
            return nullptr;
        }
        return getKthStat(node->left, k, nodeIndex - num(node->left->right) - 1);
    }
    
    short height(CNode * node) {
        return node == nullptr ? 0: node->height;
    }
    
    short balanceFactor(CNode *node) {
        return height(node->right) - height(node->left);
    }
    void fixHeight(CNode *node) {
        short heightLeft = height(node->left);
        short heightRight = height(node->right);
        node->height = std::max(heightLeft, heightRight) + 1;
    }
    
    
    int num(CNode *node) {
        return node == nullptr ? 0: node->nums;
    }
    void fixNums(CNode *node) {
        int numLeft = num(node->left);
        int numRight = num(node->right);
        node->nums = numLeft + numRight + 1;
    }
    
    CNode* rotateLeft(CNode* p) {
        CNode* q = p->right;
        p->right = q->left;
        q->left = p;
        
//        fixNums(p);
//        fixNums(q);
        
        fixHeight(p);
        fixHeight(q);
        return q;
    }
    CNode* rotateRight(CNode* p) {
        CNode* q = p->left;
        p->left = q->right;
        q->right = p;
        
        
//        fixNums(p);
//        fixNums(q);
        
        fixHeight(p);
        fixHeight(q);
        return q;
    }
    
    CNode* balance(CNode *node) {
        fixHeight(node);
        if( balanceFactor(node) == 2 ) {
            if( balanceFactor(node->right) < 0 ) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }
        if( balanceFactor(node) == -2 ) {
            if( balanceFactor(node->left) > 0 ) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }
//        fixNums(node);
        return node;
    }
    
    CNode *add(CNode *node, T value) {
        if( node == nullptr ) {
            return new CNode(value);
        }
        
        ++node->nums;
        if( compFunc(value, node->value) < 0 ) {
            node->left = add(node->left,value);
        } else {
            node->right = add(node->right,value);
        }
        return balance(node);
    }
    
    CNode *findMin(CNode *node) {
        return node->left == nullptr ? node : findMin(node->left);
    }
    
    CNode *removeMin(CNode *node) {
        if( node->left == nullptr ) {
            return node->right;
        }
        node->left = removeMin(node->left);
        return balance(node);
    }
    
    CNode *remove(CNode *node, T value) {
        if( node == nullptr ) {
            return nullptr;
        }
        int compRes = compFunc(value, node->value);
        if ( compRes < 0) {
            node->left = remove(node->left, value);
            return balance(node);
        }
        if ( compRes > 0) {
            node->right = remove(node->right, value);
            return balance(node);
        }
        if (node->right == nullptr) {
            return node->left;
        }
        CNode *lnode = node->left;
        CNode *rnode = node->right;
        delete node;
        CNode *min = findMin(rnode);
        min->right = removeMin(rnode);
        min->left = lnode;
        return balance(min);
    }
    
    void _deinit(CNode *&node) {
        if (node == nullptr) {
            return;
        }
        _deinit(node->left);
        _deinit(node->right);
        delete node;
        node = nullptr;
    }
};

template <class T>
AVLTree<T>:: AVLTree(CompareFunction compareFunction) {
    root = nullptr;
    compFunc = compareFunction;
}

template <class T>
AVLTree<T>:: AVLTree(int compareFunction(const T elem, const T elem2)) {
    root = nullptr;
    compFunc = compareFunction;
}

template <class T>
AVLTree<T>:: ~AVLTree<T>() {
    _deinit(root);
}

#endif
