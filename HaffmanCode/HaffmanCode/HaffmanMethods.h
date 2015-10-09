//
//  HaffmanMethods.h
//  HaffmanCode
//
//  Created by Александр Малышев on 11.12.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//

#ifndef __HaffmanCode__HaffmanMethods__
#define __HaffmanCode__HaffmanMethods__

#include <stdio.h>
#include <assert.h>
#include "CNode.h"
#include "CNodeArray.h"
#include "WorkingWithFile.h"

//const char* FILEPATH = "/Users/Security/Coding/MIPT C++/HaffmanCode/HaffmanCode/testTextFile.txt";
void encode(const char* inputFilePath, const char* outputFilePath);
void decode(const char* inputFilePath, const char* outputFilePath, CNode<int> &encodingBinarySearchTreeRoot);

int getBinaryFromChar(char* &encodedMsg, int &numOfChar, int &usedChar);

template <class T>
int decodeChar(char* &encodedMsg, CNode<T>* root, int &numOfChar, int &usedChar) {
    assert( root != NULL );
    int ch = -1;
    if( usedChar == 0 ) {
        ch = getBinaryFromChar(encodedMsg, numOfChar, usedChar);
    }
    //printf("Used char: %d\n", usedChar);
    if( usedChar >= numOfChar ) {
        return root->value;
    }
    //printf("getBinaryFromChar returned %d\n", ch);
    
    if( ch == 0 ) {
        if( root->left != NULL) {
           // printf("%d", ch);
            ch = getBinaryFromChar(encodedMsg, numOfChar, usedChar);
            return decodeChar(encodedMsg, root->left, numOfChar, usedChar);
        } else {
           // printf("%c", root->value);
            return root->value;
        }
    }
    if( ch == 1 ) {
        if( root->right != NULL) {
//            printf("%d", ch);
            ch = getBinaryFromChar(encodedMsg, numOfChar, usedChar);
            return decodeChar(encodedMsg, root->right, numOfChar, usedChar);
        } else {
            //printf("%c", root->value);
            return root->value;
        }
    }
    
    //printf("%c", root->value);
    return root->value;
}


template <class T>
void visitWithEncoding(CNode<T>* root) {
    if( root == NULL ) {
        return;
    } else {
        if( root-> left != NULL ) {
            strcat(root->left->code, root->code);
            strcat(root->left->code, "0");
            visitWithEncoding(root->left);
        }
        if( root->value != -1 ) {
//            printf("--\n");
//            printf("value: %d propability: %f\n", root->value, root->propability);
            printf("value: %c Code: ", root->value);
            puts(root->code);
//            printf("--\n");
        }
        if( root-> right != NULL ) {
            strcat(root->right->code, root->code);
            strcat(root->right->code, "1");
            visitWithEncoding(root->right);
        }
    }
}

template <class T>
void encodeTree(CNode<T>* root, Array<unsigned char> &encodedTree) {
    if( root == NULL ) {
        return;
    } else {
        if( root-> left != NULL ) {
            encodeTree(root->left, encodedTree);
        }
        if( root->value != -1 ) {
            encodedTree.push_back('1');
            encodedTree.push_back(root->value);
        } else {
            encodedTree.push_back('0');
        }
        if( root-> right != NULL ) {
            encodeTree(root->right, encodedTree);
        }
    }
}

template <class T>
CNodeArray<int> decodeTree(char* encodedTree) {
    CNodeArray<int> stack;
    CNodeArray<int> binarySearchTree;
    for( int i = 0; i < strlen(encodedTree); ++i ) {
        CNode<int> node;
        char ch = encodedTree[i];
        switch (ch) {
            case '0': {
                binarySearchTree.push_back(stack.pop(stack.size() - 1));
                binarySearchTree.push_back(stack.pop(stack.size() - 1));
                CNode<int> node;
                binarySearchTree.push_back(node);
                binarySearchTree[binarySearchTree.size() - 1].left = &binarySearchTree[binarySearchTree.size() - 3];
                binarySearchTree[binarySearchTree.size() - 1].right = &binarySearchTree[binarySearchTree.size() - 2];
                stack.push_back(binarySearchTree[binarySearchTree.size() - 1]);
            }
            case '1':
                break;
            default: {
                node.value = ch;
                stack.push_back(node);
                break;
            }
        }
    }
    return binarySearchTree;
}

template <class T>
void doEncodingTableWithBinarySearchTree(char** &encodingTable, CNode<T>* root) {
    if( encodingTable == NULL ) {
        encodingTable = (char**)malloc(_MaxSizeConst_ * sizeof(char*));
    }
    assert( root != NULL );
    if( root-> left != NULL ) {
        doEncodingTableWithBinarySearchTree(encodingTable, root->left);
    }
    if( root->value != EmptyNodeIdentifier) {
        encodingTable[root->value] = (char*)malloc(MaxCodeSize * sizeof(char));
        strcpy(encodingTable[root->value], root->code);
        //printf("Added cell #%d Code: ", root->value);
        //puts(root->code);
        //printf("\n");
        //puts(encodingTable[root->value]);
    }
    encodingTable[root->value] = root->code;
    if( root-> right != NULL ) {
        doEncodingTableWithBinarySearchTree(encodingTable, root->right);
    }
}

#endif /* defined(__HaffmanCode__HaffmanMethods__) */
