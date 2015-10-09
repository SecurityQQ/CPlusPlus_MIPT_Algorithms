//
//  WorkingWithFIle.h
//  HaffmanCode
//
//  Created by Александр Малышев on 10.12.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//

#ifndef __HaffmanCode__WorkingWithFile__
#define __HaffmanCode__WorkingWithFile__

#include "assert.h"
#include "CNodeArray.h"

#define _MaxSizeConst_ 100000000
#define _MaxIntBytesSizeConst_ 256
#define _MaxFilePathSize_ 256
#define defaultPath "/Users/Security/Coding/MIPT C++/HaffmanCode/HaffmanCode/testTextFile.txt"

class file: public FILE {
    public:
    
    file() {
        _filePath = (char*) malloc(_MaxFilePathSize_ * sizeof(char));
        strcpy(_filePath, defaultPath);
    }
    
    file(const char* filePath) {
        _filePath = (char*) malloc(_MaxFilePathSize_ * sizeof(char));
        assert(isCorrectFilePath(filePath));
        strcpy(_filePath, filePath);
    }
    ~file(){
        if( pFile ) {
           fclose(pFile);
        }
        free(_filePath);
    }
    
    void open(const char* format) {
        assert(pFile = fopen(_filePath, format));
    }
    
    void close() {
        fclose(pFile);
    }
    
    char* getStr() {
        char* str = (char*) malloc(_MaxSizeConst_ * sizeof(char));
        char rc;
        for( int i = 0; (rc = getc(pFile)) != EOF && i < _MaxSizeConst_; ++i ) {
            str[i] = rc;
        }
        return str;
    }
    char* getLn() {
        char* str = (char*) malloc(_MaxSizeConst_ * sizeof(char));
        fgets(str, _MaxSizeConst_, pFile);
//        char rc;
//        for( int i = 0; (rc = getc(pFile)) != EOF && i < _MaxSizeConst_; ++i ) {
//            str[i] = rc;
//        }
        return str;
    }
    
    void putCh(int ch) {
        putc(ch, pFile);
    }
    void putInt(int num) {
        fprintf(pFile, "%d", num);
    }
    
    int getInt() {
        char* str = (char*) malloc(20 * sizeof(char));
        char rc;
        for( int i = 0; (rc = getc(pFile)) != EOF && i < _MaxSizeConst_ && rc != '\n'; ++i ) {
            str[i] = rc;
        }
        
        return atoi(str);
    }
    
    Array<int> getBytesFromFile() {
        assert(pFile);
        Array<int> intBytes;
        int rc;
        for( int i = 0; (rc = getc(pFile)) != EOF && i < _MaxSizeConst_; ++i ) {
            intBytes.push_back(rc);
        }
        return intBytes;
    }
    
    CNodeArray<int> initCNodeArrayWithCountingPropability(Array<int> &bytesArray) {
        if( bytesArray.size() == 0) {
            bytesArray = getBytesFromFile();
        }
        int* count = (int*)calloc(_MaxIntBytesSizeConst_, sizeof(int));
        CNodeArray<int> bytesCNodeArray(_MaxIntBytesSizeConst_, EmptyNodeIdentifier);
        Array<int> indexes;
        for( int i = 0; i < bytesArray.size(); ++i ) {
            if( count[bytesArray[i]] == 0 ) {
                indexes.push_back(bytesArray[i]);
            }
            ++count[bytesArray[i]];
        }
        for( int j = 0; j < indexes.size(); ++j ) {
            bytesCNodeArray[indexes[j]].propability = count[indexes[j]] / (float)(bytesArray.size());
            bytesCNodeArray[indexes[j]].value = indexes[j];
        }
        
        free(count);
        return bytesCNodeArray;
    }

    //<#TODO: CHECKING ON R/W#>
    void putC(char ch) {
        fputc(ch, pFile);
    }
    
    bool isEncrypted(const char* filePath) {
        size_t filePathLen = strlen(filePath);
        if( filePath[filePathLen - 1] == 't' && filePath[filePathLen - 2] == 'x' && filePath[filePathLen - 3] == 't') {
            return false;
        }
        return true;
    }
    
    
private:
    FILE* pFile;
    char* _filePath;
    bool isCorrectFilePath(const char* filePath) {
        return true;
    }
    //Array<CNode<int>> buffer;
};

#endif /* defined(__HaffmanCode__WorkingWithFIle__) */
