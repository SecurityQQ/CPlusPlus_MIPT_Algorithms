//
//  Heap.h
//  HaffmanCode
//
//  Created by Александр Малышев on 10.12.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//

#ifndef __HaffmanCode__HeapArray__
#define __HaffmanCode__HeapArray__

#include <iostream>
#include "assert.h"

template <class  T>
class Array {
public:
    Array();
    Array(int size);
    Array(int size, T anObject);
    ~Array();
    T getElement (int index);
    void push_back (T insertingElement);
    void push (int index, T insertingElement);
    T pop (int index);
    void makeHeap();
    void heapify(int index);
    bool comp(T a,T b);
    T& operator[] (int index);
    T last();
    int size ();
protected:
    void resize();
    int length;
    int maxLength;
    T* buffer;
};


//! ARRAY IMPLEMENTATION
template <class T>
Array<T>::Array() {
    length = 0;
    maxLength = 1;
    buffer = (T*) malloc (sizeof (T));
}

template <class T>
Array<T>::Array(int size) {
    length = (int) 0;
    maxLength = (int) size;
    buffer = (T*) calloc (maxLength, sizeof (T));
}

template <class T>
Array<T>::Array(int size, T anObject) {
    Array();
    for( int i = 0; i < size; ++i ) {
        push_back(anObject);
    }
}

template <class T>
Array<T>::~Array() {
    length = 0;
    maxLength = 0;
//    if( buffer != NULL) {
//        free(buffer);
//    }
}

template <class T>
T Array<T>::getElement(int index) {
    assert((index < length) && (0 <= index));
    return buffer[index];
}

template <class T>
void Array<T>::push_back(T insertingElement) {
    if (length == maxLength) resize();
    buffer[length++] = insertingElement;
}

template <class T>
void Array<T>::push(int index, T insertingElement) {
    assert ((index < length) && (0 <= index));
    if (length == maxLength) resize();
    ++length;
    memmove(buffer + index, buffer + index + 1, (length - index - 1) * sizeof(T));
    buffer[index] = insertingElement;
}

template <class T>
T& Array<T>:: operator[] (int index) {
    assert((index < length) && (0 <= index));
    return buffer[index];
}

template <class T>
T Array<T>::pop(int index) {
    assert ((index < length) && (0 <= index));
    T popedElem = buffer[index];
    memmove(buffer + index, buffer + index + 1, (length - index - 1) * sizeof(T));
    --length;
    return popedElem;
}

template <class T>
T Array<T>::last() {
    return buffer[length - 1];
}

template <class T>
int Array<T>::size() {
    return length;
}

template <class T>
void Array<T>::resize(){
    maxLength *= 2;
    assert(buffer = (T *) realloc(buffer, sizeof (T) * (maxLength)));
    //assert(newBuffer != NULL);
    //buffer = newBuffer;
}

//! HEAP IMPLEMENTATION
template <class  T>
bool Array<T>::comp(T a,T b) {
    return a.propability > b.propability;
}

template <class  T>
void Array<T>::heapify(int index) {
    int root = index;
    while( 2 * root + 1 < length ) {
        int child = 2 * root + 1;
        if( (child + 1 < length) && comp(buffer[child], buffer[child + 1]) ) {
            child += 1;
        }
        if( comp(buffer[root], buffer[child]) ) {
            std::swap(buffer[child], buffer[root]);
            root = child;
        } else {
            return;
        }
    }
    
}

template <class  T>
void Array<T>::makeHeap(){
    for (int i = length / 2; i >= 0; --i) {
        heapify(i);
    }
}
#endif /* defined(__HaffmanCode__HeapArray__) */
