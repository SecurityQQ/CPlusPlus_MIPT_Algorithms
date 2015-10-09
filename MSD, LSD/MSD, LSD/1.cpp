//void merge(int * list, int l_start, int l_end,
//           int r_start, int r_end, bool comp(int a, int b, int d), int d) {
//    // temporary list sizes
//    int l_len = l_end - l_start;
//    int r_len = r_end - r_start;
//    
//    // temporary lists for comparison
//    int l_half[l_len];
//    int r_half[r_len];
//    
//    int i = l_start;
//    int l = 0;
//    int r = 0;
//    
//    // copy values into temporary lists
//    for (i=l_start; i < l_end; i++, l++) { l_half[l] = list[i]; }
//    for (i=r_start; i < r_end; i++, r++) { r_half[r] = list[i]; }
//    
//    // merge the values back into positions in main list
//    for (i=l_start, r=0, l=0; l < l_len && r < r_len; i++)
//    {
//        // if left value < r value, move left value
//        if (comp(l_half[l], r_half[r], d)) { list[i] = l_half[l]; l++; }
//        // else move right value
//        else { list[i] = r_half[r]; r++; }
//    }
//    
//    // handle leftover values
//    for ( ; l < l_len; i++, l++) { list[i] = l_half[l]; }
//    for ( ; r < r_len; i++, r++) { list[i] = r_half[r]; }
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
//void mergeSort(int * list, int left, int right, bool comp(int a, int b, int d), int d)
//{
//    // base case
//    if (right - left <= 1) { return; }
//    
//    // get slice indices
//    int l_start = left;
//    int l_end = (left+right)/2;
//    int r_start = l_end;
//    int r_end = right;
//    
//    // recursive call on left half
//    mergeSort(list, l_start, l_end, comp, d);
//    // recursive call on right half
//    mergeSort(list, r_start, r_end, comp, d);
//    // merge sorted right and left halves back together
//    merge(list, l_start, l_end, r_start, r_end, comp, d);
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
