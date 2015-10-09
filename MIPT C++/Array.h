//
//  Array.h
//  MIPT C++
//
//  Created by Александр Малышев on 30.09.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//
#ifndef __MIPT_C____Array__
#define __MIPT_C____Array__
#define append push_back
template <typename T>
class Array {
public:
    Array();
    Array(size_t size);
    Array(const char *filePath);
    ~Array();
    T getElement (int index);
    void push_back (T insertingElement);
    void push (int index, T insertingElement);
    void pop (int index);
    void saveToFile (const char * filePath);
    T& operator[] (int index);
    int size ();
private:
    void resize();
    int length;
    int maxLength;
    T* buffer;
};

#endif //__MIPT_C____Array__