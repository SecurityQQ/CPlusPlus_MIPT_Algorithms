//
//  HaffmanMethods.cpp
//  HaffmanCode
//
//  Created by Александр Малышев on 11.12.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//

#include "HaffmanMethods.h"
#define DecodedEncodedFilePath "/Users/Security/Coding/MIPT C++/HaffmanCode/HaffmanCode/FilesForWorking/DecodedEncodedFile.txt"
void encode(const char* inputFilePath, const char* outputFilePath) {
    Array<CNode<int>> binarySearchTree(512);
    file input(inputFilePath);
    file output(outputFilePath);
    input.open("r");
    output.open("w+");
    Array<int> bytesArray = input.getBytesFromFile();
    
    //Making encodingTable:
    CNodeArray<int> heap = input.initCNodeArrayWithCountingPropability(bytesArray);
    heap.deleteUnusedItems();
    heap.makeHeap();
    CNode<int> root = heap.transformHeapIntoBinarySearchTree(binarySearchTree);
    visitWithEncoding(&root);
    char** encodingTable;
    doEncodingTableWithBinarySearchTree(encodingTable, &root);
    //---
    //Encoding:
    Array<unsigned char> encodedMsg;
    int sizeOfOutput = 0;
    int i = 0;
    int j = 0;
    int sz = 0;
    while( i < bytesArray.size() ){
        unsigned char ch = 0;
        for( sz = 7; sz >= 0; --sz ) {
            ch |= (((encodingTable[bytesArray[i]][j++]) - '0') << sz);
            
            if( encodingTable[bytesArray[i]][j] == '\0' ) {
                ++i;
                j = 0;
            }
            if( i >=bytesArray.size() ) {
                break;
            }
        }
        //output.putCh(ch);
        ++sizeOfOutput;
        encodedMsg.push_back(ch);
    }
    output.putInt(8 * sizeOfOutput - sz);
    output.putC('\n');
    
//! encodingTree:
//    output.putCh(' ');
//    Array<unsigned char> encodedTree;
//    encodeTree(&root, encodedTree);
//    for( int i = 0; i < encodedTree.size(); ++i ) {
//        output.putC(encodedTree[i]);
//    }
//    output.putCh('\n');
//!
    
    //output.putCh(EOF);
    for( int i = 0; i <encodedMsg.size(); ++i ) {
        output.putCh(encodedMsg[i]);
    }
    input.close();
    output.close();
    decode(outputFilePath, DecodedEncodedFilePath, root);
}

void decode(const char* inputFilePath, const char* outputFilePath, CNode<int> &encodingBinarySearchTreeRoot) {
    file input(inputFilePath);
    file output(outputFilePath);
    input.open("r");
    output.open("w");
    int numOfChar = input.getInt();
    char* encodedMsg = input.getStr();
    printf("encoded Message is ");
    puts(encodedMsg);
    printf("numOfChar is %d\n", numOfChar);
    char* encodedMsgPtr = encodedMsg;
    int usedChar = 0;
    while(numOfChar > usedChar) {
        int ch = decodeChar(encodedMsg, &encodingBinarySearchTreeRoot, numOfChar, usedChar);
        printf("CH: %c\n", ch);
        output.putCh(ch);
    }
    
    free(encodedMsgPtr);
    input.close();
    output.close();
}

int getBinaryFromChar(char* &encodedMsg, int &numOfChar, int &usedChar) {
    static int i = 7;
    if( i < 0) {
        i = 7;
        encodedMsg += 1;
        //printf("|%d|", *encodedMsg);
    }
    if( numOfChar < usedChar ) {
        return -1;
    }
    unsigned char binCh;
    if( *encodedMsg >= 0) {
        binCh = ((*encodedMsg & (1<<i)) >>i);
    } else {
        binCh = (((int)(*encodedMsg) + 256  & (1<<i)) >>i);
       // printf("%d", binCh);
    }
    //printf("encMsg: %d ", *encodedMsg);
    //printf("binch: %d\n", binCh);
    --i;
    //printf("%d", binCh);
    ++usedChar;
    return binCh;
}
