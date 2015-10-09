//
//  CTopResult.h
//  CTopResult
//
//  Created by Александр Малышев on 03.03.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#ifndef __CTopResult__CTopResult__
#define __CTopResult__CTopResult_

#include <stdio.h>
#include "Comparator.h"
#include <vector>
#include <algorithm>
#include <iterator>

typedef unsigned long long ull;

template <class tKey, class tValue>
class CTopResult;

template <class tKey, class tValue>
class CTopResult {

private:
    
    struct item {
        tValue value;
        std::vector<tKey> keys;
    };
    
    Comparator<tValue> compareManager;
    
    ull topMaxSize;
    ull topRealSize;
    
    item *buffer;
    
    CTopResult();


public:
    CTopResult(ull topResultSize, Comparator<tValue> comparator);

    ~CTopResult();
    void add(tKey key, tValue value);
    void show();
    std::vector<tKey> getFirstInTop();
    std::vector<tKey> getLastInTop();
    
    class iterator {
        friend class CTopResult;
    private:
        item *top;
    public:
        iterator(item *top) {
            this->top = top;
        }
        item& operator*() {
            return (*top);
        }
        iterator operator ++() {
            iterator itr = *this;
            ++top;
            return itr;
        }
        iterator operator --() {
            iterator itr = *this;
            --top;
            return itr;
        }
        bool operator == (const iterator &itr) {
            return top->value == itr.top->value;
        }
        bool operator != (const iterator &itr) {
            return top->value != itr.top->value;
        }
    };
    
    iterator begin() {
        return iterator(buffer);
    }
    iterator end() const {
        return iterator(buffer + topRealSize);
    }
};



template <class tKey, class tValue>
CTopResult<tKey, tValue>:: CTopResult(ull topResultSize, Comparator<tValue> comparator) {
    topMaxSize = topResultSize;
    topRealSize = 0;
    compareManager = comparator;
    buffer = new item[topMaxSize];
}
template <class tKey, class tValue>
CTopResult<tKey, tValue>::~CTopResult() {
    delete [] buffer;
}

template <class tKey, class tValue>
void CTopResult<tKey, tValue>:: add(tKey key, tValue value) {
    ull i = 0;
    
    while( compareManager.compare(value, buffer[i].value) > 0 && i < topRealSize) {
        ++i;
    }
    
    if( i >= topMaxSize ) { 
        return;
    }
    
    if( i < topRealSize ) {
        if( compareManager.compare( value, buffer[i].value ) == 0 ) {
            buffer[i].keys.push_back(key);
            return;
        }
    }
    
    if( topRealSize < topMaxSize ) {
        for( ull j = topRealSize; j > i; --j ) {
            std::swap(buffer[j], buffer[j - 1]);
        }
        ++topRealSize;
    } else {
        for( ull j = topMaxSize - 1; j > i; --j ) {
            std::swap(buffer[j], buffer[j - 1]);
        }
    }
    buffer[i].value = value;
    buffer[i].keys.erase(buffer[i].keys.begin(), buffer[i].keys.end());
    buffer[i].keys.push_back(key);
}

template <class tKey, class tValue>
void CTopResult<tKey, tValue>:: show() {
    for( ull i = 0; i < topRealSize; ++i ) {
        std::cout<<"#" <<i + 1 << " |result: "<< buffer[i].value <<" ";
        for( ull j =0; j < buffer[i].keys.size() - 1; ++j ) {
            std::cout<< buffer[i].keys[j] <<", ";
        }
        std::cout<<buffer[i].keys[buffer[i].keys.size() - 1] <<std::endl;
    }
}
#endif /* defined(__CTopResult__CTopResult__) */
