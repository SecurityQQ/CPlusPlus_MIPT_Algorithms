//
//  CString.h
//  MIPT_TASK_4_1_CLASSES
//
//  Created by Александр Малышев on 11.02.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#ifndef __MIPT_TASK_4_1_CLASSES__CString__
#define __MIPT_TASK_4_1_CLASSES__CString__


#pragma mark - includes
#pragma mark ---

#include <stdio.h>
#include <iostream>

#pragma mark - typedefs
#pragma mark ---
typedef unsigned long __indexType__;

#pragma mark CString interface
#pragma mark ---
class CString {
    
public:
    //Constructors:
    CString();
    CString(const char *string); //init with char*
    CString(const std::string string); //init with std::string
    CString(const CString& string); //copy constructor
    
    //Destructors:
    ~CString();
    
    //methods:
    
    void replaceAtIndex (const char* string, __indexType__ index); //replacing substring starting with index
    void insertSubstringAtIndex (const char* string, __indexType__ index); //inserting substring starting with index
    void deleteWithIndexes (__indexType__ firstIndex, __indexType__ secondIndex); //deleting substring in interval

    char& operator[] (__indexType__ index);            //index request
    
    //another operators:
    CString& operator= (const CString& string);
    bool operator== (CString& string);
    bool operator< (CString& string); //lexicography strong comparator
    bool operator> (CString& string); //lexicography strong comparator
    bool operator>= (CString& string); //lexicography weak comparator
    bool operator<= (CString& string); //lexicography weak comparator
    CString& operator+= (CString& string); //return *this with appending of string
    CString operator + (CString& string); //return CString created by merging two of them
    //working with string:
    __indexType__ size(); //returns current length of the CString
    
private:
    
    char *buffer; //data of the CString
    __indexType__ length; //current length
    __indexType__ maxSize; //maximum size of CString
    void resize(); //resizing CString

};

//global operators:
std::ostream &operator << (std::ostream &stream, CString &string);
std::istream &operator >> (std::istream &stream, CString &string);

#endif /* defined(__MIPT_TASK_4_1_CLASSES__CString__) */
