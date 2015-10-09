//void merge(T *arr, int left, int half, int right, bool comp(T a, T b, T d), int d) {
//    assert(left < right);
//    assert(left >= 0);
//    assert(half < right);
//    assert(left < half);
//    
//    int l_size = half - left;
//    int r_size = right - half;
//    
//    int l = 0;
//    int r = 0;
//    int sz = left;
//    
//    int* l_half = (int*) malloc (l_size * sizeof(int));
//    int* r_half = (int*) malloc (r_size * sizeof(int));
//
//    for( int i = left; i < half; ++i, ++l) {
//        l_half[l] = arr[i];
//    }
//    for (int i = half; i < right; ++i, ++r) {
//        r_half[r] = arr[i];
//    }
//    assert(l == l_size);
//    assert(r == r_size);
//    l = 0;
//    r = 0;
//    while (l < l_size && r < r_size) {
//        if (comp( l_half[l], r_half[r], d)) {
//            arr[sz++] = l_half[l++];
//        } else {
//            arr[sz++] = r_half[r++];
//        }
//    }
//    for( ; l < l_size; ++l, ++sz) {
//        arr[sz] = l_half[l];
//    }
//    for( ; r < r_size; ++r, ++sz) {
//        arr[sz] = r_half[r];
//    }
//}
//
//
//
//
//
//
//
//
//template<class T>
//void mergeSort (T* arr, int l, int r, bool comp(T a, T b, T d), int d) {
//    if (r - l <= 1) {
////        if (comp(arr[r], arr[l], d)) {
////            std::swap(arr[l], arr[r]);
////        }
//        return;
//    }
//    int half = (l + ((r - l) >> 1));
//    mergeSort (arr, l, half, comp, d);
//    mergeSort (arr, half, r, comp, d);
//    merge(arr, l, half, r, comp, d);
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
