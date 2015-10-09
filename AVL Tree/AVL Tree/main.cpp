//
//  main.cpp
//  AVL Tree
//
//  Created by Александр Малышев on 06.04.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <iostream>

#define AVL_OK 0
#define AVL_ERR 1

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
    bool search(T value);
    
private:
    
    struct CNode {
        CNode *left;
        CNode *right;
        short height;
        T value;
        CNode(T value): value(value), left(nullptr), right(nullptr), height(1) {}
    };
    
    CNode *root;
    CompareFunction compFunc;
    
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
    
    CNode* rotateLeft(CNode* p) {
        CNode* q = p->right;
        p->right = q->left;
        q->left = p;
        fixHeight(p);
        fixHeight(q);
        return q;
    }
    CNode* rotateRight(CNode* p) {
        CNode* q = p->left;
        p->left = q->right;
        q->right = p;
        fixHeight(p);
        fixHeight(q);
        return q;
    }
    
    CNode* balance(CNode *node) {
        fixHeight(node);
        if( balanceFactor(node) == 2 ) {
            if( balanceFactor(node->right) < 0 ) {
                node->right = rotateRight(node->left);
            }
            return rotateLeft(node);
        }
        if( balanceFactor(node) == -2 ) {
            if( balanceFactor(node->left) > 0 ) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }
        return node;
    }
    
    CNode *add(CNode *node, T value) {
        if( node == nullptr ) {
            return new CNode(value);
        }
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
        if (root == nullptr) {
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


int compInt(const int a, const int b) {
    return a - b;
}

int main(int argc, const char * argv[]) {
    AVLTree<int> tree(compInt);
    int value;
    
    char ch;
    int k, prior;
    while( !std::cin.fail() ) {
        ch = EOF;
        std::cin>> ch >> k;
        switch (ch) {
            case '+':
                if ( tree.add(k) == AVL_OK ) {
                    std::cout<<"OK\n";
                }
                break;
//            case '?':
//                if (bst.search(k) == true) {
//                    std::cout<<"OK\n";
//                } else {
//                    std::cout<<"FAIL\n";
//                }
//                break;
            case '-':
                if (tree.remove(k) == AVL_OK) {
                    std::cout<<"OK\n";
                }
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
    
    
    return 0;
}
