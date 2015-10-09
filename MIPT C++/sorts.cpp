//
//  sorts.cpp
//  MIPT C++
//
//  Created by Александр Малышев on 01.10.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//
#include <iostream>
#include "sorts.h"
#include "Array.h"

template <typename T>
void myAwesomeSwap (T &firstElement, T &secondElement) {
    T temp = firstElement;
    firstElement = secondElement;
    secondElement = temp;
}

template <typename T>
void bubbleSort (Array<T> &array) {
    bool myAwesomeBubbleSortFlag = true;
    int sz = array.size();
    int i = 0;
    while ((myAwesomeBubbleSortFlag) && (i < sz)) {
        myAwesomeBubbleSortFlag = false;
        for (int j = 0; j <sz - i - 1; ++j) {
            if (array[j] > array[j+1]) {
                myAwesomeSwap(array[j], array[j+1]);
                myAwesomeBubbleSortFlag = true;
            }
        }
        ++i;
    }
}

template <typename T>
void insertionSort (Array<T> &array) {
    int sz = array.size();
    for (int rightIndex = 1; rightIndex < sz; ++rightIndex) {
        int leftIndex = 0;
        while ((array[rightIndex] >= array[leftIndex]) && (leftIndex < rightIndex))
            ++leftIndex;
        int temp = array[rightIndex];
        for (int k = rightIndex; leftIndex < k; --k) {
            array[k] = array[k - 1];
        }
        array[leftIndex] = temp;
    }
}

template <typename T>
void insertionSort2(Array<T> &array) {
    for (int i = 1; i < array.size(); ++i)
        for (int j = i; j && array[j] < array[j-1]; j--)
            myAwesomeSwap(array[j], array[j-1]);
}

template <typename T>
void selectionSort(Array<T> &array) {
    int sz = array.size();
    for (int j = 0; j < sz; ++j) {
        int min = j;
        for (int i = j; i < sz; i ++) {
            if (array[min] > array[i]) min = i;
        }
        myAwesomeSwap(array[j], array[min]);
    }
}

// TODO: I am tired, don`t want to fix
template <typename T>
void quicksort(Array<T> &array, int l, int r)
{
    int i=l;
    int j=r;
    int x=array[(i+j)>>1];
    while (array[i]<x) i++;
    while (array[j]>x) j--;
    if (i<=j)
        myAwesomeSwap(array[i],array[j]);
    
    i++;
    j--;
    if (i<r) quicksort(array, i,r);
    if (j>l) quicksort(array, l,j);
}

template<typename T>
void insertionSortWiki(Array<T> &A) {
    for (int i = 1; i < A.size(); i++)
        for (int j = i; j && A[j] < A[j-1]; j--)
            myAwesomeSwap(A[j], A[j-1]);
}

template <typename T>
void bubbleSortByNikitochkaPystovoitov (Array<T> &A) {
    int sz =  A.size();
    for (int i = 0 ; i < sz ; ++i ) {
        for (int j = 0; j < i - sz - 1; ++j) {
            if (A[j] > A[j+1]) myAwesomeSwap(A[j], A[j+1]);
    }
  }
}