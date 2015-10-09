template <typename T>
void awesomeSwap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}
template <typename T>
void quickSort(T *arr, int l, int r, bool comp(T a, T b)) {
    int i = l, j = r;
    T pivot = arr[l + ((r - l) >>1)];
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