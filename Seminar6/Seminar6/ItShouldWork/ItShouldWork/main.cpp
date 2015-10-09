#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <memory.h>

#define show     for(int i = 0; i < a.maxLength; ++i) {\
std::cout<<a.buffer[i] << " ";\
} std::cout<<std::endl;\
//! CDEQUE INIT =======================

template <class T>
class CDeque {
public:
    CDeque();
    ~CDeque();
    void push_back(T element);
    void push_front(T element);
    T pop_back();
    T pop_front();
    
    
    void resize();
    T* buffer;
    size_t size;
    size_t front;
    size_t back;
    size_t maxLength;
private:


};

//! IMPLEMENTATION OF CDEQUE ==========

template <class T>
CDeque<T>::CDeque() {
    size = 0;
    maxLength = 1;
    front = -1;
    back = -1;
    buffer = (T*) malloc (sizeof (T));
}

template <class T>
CDeque<T>::~CDeque() {
//    while(front != -1) {
//        pop_front();
//    }
    maxLength = 0;
    front = 0;
    back = 0;
    free(buffer);
}

template <class T>
void CDeque<T>::resize() {
    assert(front == back);
    //doing in situation [... back][front ... ]
    //coping all elements, except buffer[front]
    size_t backMalloc = (back) * sizeof(T);
    size_t frontMalloc = (maxLength - front) * sizeof(T);
    size_t oldLength = maxLength;
    
    maxLength *= 2;
    
    // coping halfs:
    T* tempBack = (T*)malloc(backMalloc);
    T* tempFront = (T*)malloc(frontMalloc);
    memcpy(tempBack, buffer, backMalloc);
    memcpy(tempFront, buffer + front + 1, frontMalloc);
    
    T* tempBuffer = (T*)calloc(oldLength, sizeof(T));
    memcpy(tempBuffer, buffer, oldLength * sizeof(T));

    buffer = (T *)calloc(maxLength, sizeof (T));
    memcpy(buffer, tempBack, backMalloc);
    
    front = (maxLength - (oldLength - front));
    memcpy(buffer + front + 1, tempFront, frontMalloc);
    for(int i = 0; i < maxLength; ++i ) {
        std::cout<<buffer[i] << " ";
    } std::cout<< std::endl;
    free(tempBack);
    free(tempFront);
    free(tempBuffer);
}

template <class T>
void CDeque<T>::push_front(T element) {
    if( front <= 0 ) {
        front = maxLength - 1;
    } else {
        --front;
    }
    if( back == -1) {
        back = front;
    } else {
        if( front == back ) {
            T tmp = buffer[back];
            resize();
            buffer[back] = tmp;
        }
    }
    buffer[front] = element;
    ++size;
}

template <class T>
void CDeque<T>::push_back(T element) {
    if( (back <= maxLength - 1) || (back == -1) ) {
        back = 0;
    } else {
        ++back;
    }
    if( front == -1) {
        front = back;
        } else {
        if( front == back ) {
            T tmp = buffer[front];
            resize();
            buffer[front] = tmp;
        }
    }
    buffer[back] = element;
    ++size;
}

template <class T>
T CDeque<T>::pop_front() {

    if( size == 0) {
        return -1;
    }
    
    T popElem = buffer[front];
    buffer[front] = 0;
    if( front == maxLength - 1) {
        front = 0;
    } else {
        ++front;
    }
    --size;
    if( size == 0) {
        front = -1;
        back = -1;
    }
    return popElem;
}
template <class T>
T CDeque<T>::pop_back() {
    if( size == 0) {
        return -1;
    }

    T popElem = buffer[back];
    buffer[back] = 0;
    if (back == 0) {
        back = maxLength - 1;
    } else {
        --back;
    }
    --size;
    if( size == 0) {
        front = -1;
        back = -1;
    }
    return popElem;
}

bool dequeCheck() {
    int n, cmd, value;
    CDeque<int> deque;
    scanf("%d", &n);
    
    for( int i = 0; i < n; ++i) {
        scanf("%d%d", &cmd, &value);
            switch (cmd) {
                case 1:
                    deque.push_front(value);
                    break;
                    
                case 2: {
                    if (value != deque.pop_front()) {
                        return false;
                    }
                }
                break;
                    
                case 3:
                    deque.push_back(value);
                    break;
                    
                case 4:
                    if (value != deque.pop_back()) {
                        return false;
                    }
                    break;
        }
    }
    return true;
}

int main() {
    CDeque<int> a;

        if (dequeCheck()) {
        printf("YES");
    } else {
        printf("NO");
    }
    return 0;
}



