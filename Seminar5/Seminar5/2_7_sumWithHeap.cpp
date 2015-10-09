#include <iostream>
#include "assert.h"

template <typename  T>
class Array {
public:
    Array();
    Array(size_t size);
    ~Array();
    T getElement (int index);
    void push_back (T insertingElement);
    void push (int index, T insertingElement);
    void pop (int index);
    void makeHeap();
    void heapify(int index);
    bool comp(T a,T b);
    T& operator[] (int index);
    int size ();
private:
    void resize();
    int length;
    int maxLength;
    T* buffer;
};


int main(int argc, const char * argv[]) {
    int n, foo;
    int ans = 0;
    Array<int> myHeap;
    scanf("%d", &n);
    for( int i = 0; i < n; ++i) {
        scanf("%d", &foo);
        myHeap.push_back(foo);
    }
    myHeap.makeHeap();
    while (myHeap.size() > 2) {
        int i;
        if( myHeap[1] < myHeap[2] ) {
            i = 1;
        } else {
            i = 2;
        }
        int temp = myHeap[0] + myHeap[i];
        ans += temp;
        std::swap(myHeap[i], myHeap[myHeap.size() - 1]);
        myHeap.pop(myHeap.size() -1);
        myHeap[0] = temp;
        
        if( i != myHeap.size() - 1 ) {
            myHeap.heapify(i);
        }
        myHeap.heapify(0);
        
    }
    ans += myHeap[0] + myHeap[1];
    printf("%d", ans);
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

//! HEAP IMPLEMENTATION
template <typename  T>
bool Array<T>::comp(T a,T b) {
    return a > b;
}

template <typename  T>
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
template <typename  T>
void Array<T>::makeHeap(){
    for (int i = length / 2; i >= 0; --i) {
        heapify(i);
    }
}

//! END OF HEAP IMPLEMENTATION

