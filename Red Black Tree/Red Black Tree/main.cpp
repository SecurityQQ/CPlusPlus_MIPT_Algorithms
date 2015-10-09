//
//  main.cpp
//  Red Black Tree
//
//  Created by Александр Малышев on 18.05.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <iostream>
#include "RBTree.h"
#include <set>
#include "AVL Tree.h"

int compInt(const int a, const int b) {
    return a - b;
}

void debug() {
    RBTree<int> tree(compInt);
    int value;
    
    char ch;
    int k, prior;
    
    for (int i = 0; i < 30; ++i) {
        int a = rand() % 70;
        std::cout<<"Adding: "<<a <<std::endl;
        tree.add(a);
    }
    
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
//                if (tree.find(k)) {
//                    std::cout<<"OK\n";
//                } else {
                    std::cout<<"FALSE\n";
//                }
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
//    debug();
    const int NUM_OF_TESTS = 100000;
    RBTree<int> myTree(compInt);
    std::set<int> stlTree;
    AVLTree<int> myAVL(compInt);
    
    time_t myStart = clock();
    for (int i = 0; i < NUM_OF_TESTS; ++i) {
        myTree.add(rand() % NUM_OF_TESTS);
        myTree.remove(rand() % NUM_OF_TESTS);
    }
    time_t myFinish = clock();
    
    time_t stlStart = clock();
    for (int i = 0; i < NUM_OF_TESTS; ++i) {
        stlTree.insert(rand() % NUM_OF_TESTS);
        stlTree.erase(rand() % NUM_OF_TESTS);
    }
    time_t stlFinish = clock();
    
    time_t myAVLStart = clock();
    for (int i = 0; i < NUM_OF_TESTS; ++i) {
        myAVL.add(rand() % NUM_OF_TESTS);
        myAVL.remove(rand() % NUM_OF_TESTS);
    }
    time_t myAVLFinish = clock();
    
    std::cout<<"My score: " <<myFinish - myStart <<std::endl;
    std::cout<<"STL score: "<<stlFinish - stlStart <<std::endl;
    std::cout<<"My AVL score: "<<myAVLFinish - myAVLStart<<std::endl;
    return 0;
}
