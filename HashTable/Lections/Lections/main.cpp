//
//  main.cpp
//  Lections
//
//  Created by Александр Малышев on 16.10.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//

#include <iostream>
typedef int Item;
size_t binsearch (const Item * a, size_t l, size_t r, Item key);
void qSort(Item * a, int l, int r);
size_t partition (Item * arr, size_T l, size_t r, bool comp(Item &firstCompElement, Item &secondCompElement));
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}


size_t binsearch (const Item * a, size_t l, size_t r, Item key) {
    if (l == r ) return -1;
    if (l == r - 1) return (a[l] == key) ? ( l : -1 );
    size_t mid = ((l>> 1) + (r>> 1));
    if (a[mid] > key)
        return binsearch(a, l, mid, key);
    else
        return binsearch(a, mid, r, key);
}
void qSort(Item * a, int l, int r) {
    if (r <= l) return;
    size_t q = partition (a, l , r);
    qSort(a, l , q);
    qSort(a, q, r);
}

size_t partition (Item * arr, size_T l, size_t r, bool comp(Item &firstCompElement, Item &secondCompElement)) {
    int i = l - 1;
    int j = r - 1;
    Item v = a[r-1];
    while (true) {
        do {
        ++i;
            
        } while (a[i] < v);
}