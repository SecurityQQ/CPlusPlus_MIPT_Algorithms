#include <iostream>
#include <assert.h>
#include <stdio.h>
#include "Array.h"

template <typename T>
Array<T>::Array() {
    length = 0;
    maxLength = 1;
    buffer = (T*) malloc (sizeof (T));
}

template <typename T>
Array<T>::Array(size_t size) {
    length = (int) size;
    maxLength = (int) size;
    buffer = (T*) malloc (maxLength * sizeof (T));
}
template <typename T>
Array<T>::Array(const char * filePath) {
    length = 0;
    maxLength = 1;
    buffer = (T*) malloc (sizeof (T));
    FILE *file = freopen(filePath, "r", stdin);
    int foo = -1;
    while (!feof(file)) {
        fscanf(file, "%d", &foo);
        push_back(foo);
    }
    fclose(stdin);
}

template <typename T>
Array<T>::~Array() {
    free(buffer);
    length = 0;
    maxLength = 0;
}

template <typename T>
T Array<T>::getElement(int index) {
    assert((index < length) && (0 <= index));
    return buffer[index];
}

template <typename T>
void Array<T>::push_back(T insertingElement) {
    if (length == maxLength) resize();
    buffer[length++] = insertingElement;
}

template <typename T>
void Array<T>::push(int index, T insertingElement) {
    assert ((index < length) && (0 <= index));
    if (length == maxLength) resize();
    for (int i = length; i > index; --i) {
        buffer[i] = buffer[i-1];
    }
    ++length;
    buffer[index] = insertingElement;
}

template <typename T>
T& Array<T>:: operator[] (int index) {
    assert((index < length) && (0 <= index));
    return buffer[index];
}
    
template <typename T>
void Array<T>::pop(int index) {
    assert ((index < length) && (0 <= index));
    for (int i = index; i < length - 1; ++i) {
        buffer[i] = buffer[i+1];
    }
    --length;
}

template <typename T>
int Array<T>::size() {
    return length;
}

template <typename T>
void Array<T>::resize(){
    maxLength *= 2;
    T* newBuffer = (T *) realloc(buffer, sizeof (T) * (maxLength));
    assert(newBuffer != NULL);
        buffer = newBuffer;
}

template <typename T>
void Array<T>::saveToFile (const char * filePath) {
    freopen(filePath, "w", stdout);
    for (int i = 0; i < length; ++i) {
         printf("%d ", buffer[i]);
    }
    fclose(stdout);
}