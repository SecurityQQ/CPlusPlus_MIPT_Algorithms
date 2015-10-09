//
//  sorts.h
//  MIPT C++
//
//  Created by Александр Малышев on 01.10.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//

#ifndef __MIPT_C____sorts__
#define __MIPT_C____sorts__

#include <stdio.h>

template <typename T>
bool operator < (T &lhs, T &rhs);
template <typename T>
bool operator > (T &lhs, T &rhs);

template <typename T>
void myAwesomeSwap (T &firstElement, T &secondElement);
template <typename T>
void bubbleSort(T *array);
template <typename T>
void insertionSort(T *array);
template <typename T>
void selectionSort(T *array);
template <typename T>
void insertionSort2(T *array);
template<typename T>
void insertionSortWiki(T *A);
template <typename T>
void quicksort(T *array, int l, int r);
template <typename T>
void bubbleSortByNikitochkaPystovoitov(T *A);

#endif /* defined(__MIPT_C____sorts__) */
