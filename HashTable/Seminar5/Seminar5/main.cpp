#include <iostream>
#include "assert.h"

template <class T>
class Array {
public:
    Array();
    Array(size_t size);
    ~Array();
    T getElement (int index);
    void push_back (T insertingElement);
    void push (int index, T insertingElement);
    void pop (int index);
    T& operator[] (int index);
    int size ();
private:
    void resize();
    int length;
    int maxLength;
    T* buffer;
};

typedef int Item;

template <class T>
class heap {
public:
    heap();
    ~heap();
    void heapify(int index);
    void add(T elem);
    T pop (size_t index);
    void makeHeap(Array<T> &arr);
    T& operator[] (int index);
    bool comp(T &a, T &b);
private:
    int length;
    Array<T> data;
};

int main(int argc, const char * argv[]) {
    
    return 0;
}



//! ARRAY IMPLEMENTATION
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
Array<T>::~Array() {
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

//! END OF ARRAY IMPLEMENTATION

//! --------------------------------------------------------

//! HEAP IMPLEMENTATION

template <class T>
heap<T>::heap() {
    length = 0;
}

template <class T>
heap<T>::~heap() {
    data.~Array();
}

template <class T>
T& heap<T>:: operator[] (int index) {
    assert((index < length) && (0 <= index));
    return data[index];
}

template <class T>
bool comp(T &a,T &b) {
    return a < b;
}

template <class T>
void heap<T>::heapify(int index) {
    int root = index;
    while( 2 * root + 1 < length ) {
        int child = 2 * root + 1;
        if( (child + 1 < length) && comp(data[child], data[child + 1]) ) {
            child += 1;
        }
        if( comp(data[root], data[child]) ) {
            std::swap(data[child], data[index]);
            root = child;
        } else {
            return;
        }
    }
    
}
template <class T>
void heap<T>::add(T elem) {
    data.push_back(elem);
}

template <class T>
T heap<T>::pop (size_t index) {
    data.pop((int) index);
};

template <class T>
void heap<T>::makeHeap(Array<T> &arr){
    length = arr.size();
    for (int i = length / 2; i > 0; ++i) {
        heapify(i);
    }
    
}

//! END OF HEAP IMPLEMENTATION

