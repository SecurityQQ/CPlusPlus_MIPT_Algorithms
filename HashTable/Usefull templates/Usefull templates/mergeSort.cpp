template<typename T>
void mergeSort (T* arr, int l, int r, bool comp(T a, T b)) {
    if (r - l <= 1) {
        if (comp(arr[r], arr[l])) {
            awesomeSwap(arr[l], arr[r]);
        }
        return;
    }
    mergeSort (arr, l, (l + r) / 2, comp);
    mergeSort (arr, (l + r) / 2, r, comp);
    merge(arr, l, (l + r) / 2, r, comp);
}

template <typename T>
void merge(T *arr, int left, int half, int right, bool comp(T a, T b)) {
    assert(left < right);
    assert(left >= 0);
    assert(half < right);
    assert(left < half);
    int l_size = half - left;
    int r_size = right - half   ;
    int l = 0;
    int r = 0;
    int sz = left;
    int l_half[l_size];
    int r_half[r_size];
    for( int i = left; i < half; ++i, ++l) {
        l_half[l] = arr[i];
    }
    for (int i = half; i < right; ++i, ++r) {
        r_half[r] = arr[i];
    }
    l = 0;
    r = 0;
    while (l < l_size && r < r_size) {
        if( l_half[l] < r_half[r] ) {
            arr[sz++] = l_half[l++];
        } else {
            arr[sz++] = r_half[r++];
        }
    }
    for( ; l < l_size; ++l, ++sz) {
        arr[sz] = l_half[l];
    }
    for( ; r < r_size; ++r, ++sz) {
        arr[sz] = r_half[r];
    }
}
