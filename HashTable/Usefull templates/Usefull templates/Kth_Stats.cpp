#include <iostream>

bool compInt (int p, int p2) {
    return p < p2;
}

template <typename T>
T middle(T *arr, T var1, T var2, T var3, bool comp(T firstCompElement, T secondCompElement));

template <typename T>
int partitionByMiddle (T* arr, int l, int r, bool comp(T firstCompElement, T secondCompElement));

int findKStat(int* arr, int n, int k);

void show(int *arr, int n, int tmp) {
    for (int i = 0; i < n ; ++i) {
        if( i == tmp) printf("|");
        printf("%d ", arr[i]);
        if( i == tmp) printf("|");
    }
    printf("\n");
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int * arr = (int *) malloc (n * sizeof(int));
    for (int i = 0 ; i < n; ++i) {
        scanf("%d", &arr[i]);
    }
    
    printf("%d", findKStat(arr, n, k));
    
    return 0;
}

int findKStat(int* arr, int n, int k) {
    int startOfPartition = 0, endOfPartition = n;
    int p = partitionByMiddle(arr, startOfPartition, endOfPartition, compInt);
    while (true) {
        if (p == k) break;
        else {
            if (p > k) {
                endOfPartition = p;
                p = partitionByMiddle(arr, startOfPartition, endOfPartition, compInt);
            }
            else {
                startOfPartition = p + 1;
                p = partitionByMiddle(arr, startOfPartition, endOfPartition, compInt);
            }
        }
        
    }
    return arr[p];
}

template <typename T>
int partitionByMiddle( T* arr, int l, int r, bool comp(T firstCompElement, T secondCompElement) ) {
    srand(time(NULL));
    if( l == r ) {
        return l;
    }
    
    int piv = middle(arr, (rand() % (r - l) + l), (l + ((r - l) >> 1)) , (rand() % (r - l) + l), comp);
    std::swap(arr[piv], arr[r - 1]);
    piv = r - 1;
    int i = l;
    int j = l;
    
    while( j < piv) {
        if( comp(arr[j], arr[piv]) ) {
            std::swap(arr[j], arr[i++]);
        }
        ++j;
    }
    std::swap(arr[piv], arr[i]);
    return i;
}

template <typename T>
T middle(T *arr, T var1, T var2, T var3, bool comp(T firstCompElement, T secondCompElement)) {
    if ((comp(arr[var1], arr[var2]) && comp(arr[var2], arr[var3])) || ((comp(arr[var3], arr[var2]) && comp(arr[var2], arr[var1])))) return var2;
    if ((comp(arr[var2], arr[var1]) && comp(arr[var1], arr[var3])) || ((comp(arr[var3], arr[var1]) && comp(arr[var1], arr[var2])))) return var1;
    if ((comp(arr[var1], arr[var3]) && comp (arr[var3], arr[var2])) || ((comp(arr[var2], arr[var3]) && comp (arr[var3], arr[var1]))))  return var3;
    return var2;
}
