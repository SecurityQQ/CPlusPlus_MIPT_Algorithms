//
//  Comparator.h
//  CTopResult
//
//  Created by Александр Малышев on 18.03.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#ifndef __CTopResult__Comparator__
#define __CTopResult__Comparator__

#include <stdio.h>
#include <functional>

template <class T>
class Comparator {
    
public:
    Comparator();
    Comparator(int compFunc(const T elem, const T elem2));
    ~Comparator();
    typedef std::function<int (const T elem, const T elem2)> CompareFunction;
    CompareFunction compare;
private:
};

template <class T>
Comparator<T>:: Comparator() {
    
}

template <class T>
Comparator<T>:: Comparator(int compFunc(const T elem, const T elem2)) {
    compare = compFunc;
}

template <class T>
Comparator<T>:: ~Comparator() {
    
}

#endif /* defined(__CTopResult__Comparator__) */
