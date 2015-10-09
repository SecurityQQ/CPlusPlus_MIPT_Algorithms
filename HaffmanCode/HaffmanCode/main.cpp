//
//  main.cpp
//  HaffmanCode
//
//  Created by Александр Малышев on 06.12.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//

#include <iostream>
#include "HaffmanMethods.h"
#include <codecvt>

const char* testTextFilePath = "/Users/Security/Coding/MIPT C++/HaffmanCode/HaffmanCode/FilesForWorking/testTextFile.txt";
void testHaffmanEncodingDecoding();
void append(char* &str, char* sym);
int tmpFun(Array<int> a);
void doCalc() ;
int main(int argc, const char * argv[]) {
    testHaffmanEncodingDecoding();
    return 0;
}

void append(char* &str, char* sym) {
    strcat(str, sym);
}



void testHaffmanEncodingDecoding() {
    encode(testTextFilePath, "/Users/Security/Coding/MIPT C++/HaffmanCode/HaffmanCode/FilesForWorking/testTextFile.hf");
}
