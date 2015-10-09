#include <iostream>
#include <assert.h>

template <typename T>
void quickSort(T *arr, int l, int r, bool comp(T a, T b));
template <typename T>
void awesomeSwap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

struct edge {
    int cord;
    bool isLeft;
};
void Init(edge edge) {
    edge.cord = 0;
    edge.isLeft = true;
}
bool compEdges(edge firstEdge, edge secondEdge) {
    return firstEdge.cord < secondEdge.cord;
}

int main() {
    int n = 0;
    edge* ranges;
    int ans = 0;
    
    scanf("%d", &n);
    long sz = 2 * n;
    ranges = (edge *)malloc(sz * sizeof(edge));
    for( int i = 0; i < sz; i += 2) {
        Init(ranges[i]);
        Init(ranges[i + 1]);
        scanf("%d%d", &ranges[i].cord, &ranges[i + 1].cord);
        ranges[i].isLeft = true;
        ranges[i + 1].isLeft = false;
    }
    
    quickSort(ranges, 0, 2 * n - 1, compEdges);
    int cnt = 0;
    for( int i = 0 ; i < 2 * n; ++i ) {
        if( cnt == 1) {
            assert(i > 0);
            ans += abs(ranges[i].cord - ranges[i - 1].cord);
        }
        if( ranges[i].isLeft ) {
            ++cnt;
        } else {
            --cnt;
        }
    }
    
    printf("%d", ans);
    
    return 0;
}


template <typename T>
void quickSort(T *arr, int l, int r, bool comp(T a, T b)) {
    int i = l, j = r;
    T pivot = arr[(l >>1) + (r >>1)];
    while (i <= j) {
        while(comp(arr[i], pivot)) {
            i++;
        }
        while (comp(pivot, arr[j])) {
            j--;
        }
        if (i <= j) {
            awesomeSwap(arr[i], arr[j]);
            i++;
            j--;
        }
    };
    
    if (l < j)
        quickSort(arr, l, j, comp);
    if (i < r)
        quickSort(arr, i, r, comp);
    
}