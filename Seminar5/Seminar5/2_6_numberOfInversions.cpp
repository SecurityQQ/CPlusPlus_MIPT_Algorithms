#include <iostream>
#include <assert.h>

template <typename T>
class Array {
public:
    Array();
    Array(size_t size);
    Array(const char *filePath);
    ~Array();
    T getElement (int index);
    void push_back (T insertingElement);
    void push (int index, T insertingElement);
    void pop (int index);
    void saveToFile (const char * filePath);
    T& operator[] (int index);
    int size ();
private:
    void resize();
    int length;
    int maxLength;
    T* buffer;
};

template <class T>
void awesomeSwap(T& a, T& b);

template <class T>
void mergeSort(Array<T> arr, int l, int r, bool comp(T a, T b));

template <class T>
void merge(Array<T> arr, int left, int half, int right, bool comp(T a, T b));

template <class T>
void awesomeSwap(T& a, T& b);

bool compInt(int a, int b) {
    return a < b;
}

long long ans = 0;

int main() {
    char foo[15];
    Array<int> arr;
    
    while( gets(foo) ) {
        if( foo[0] == '\0' ) {
            break;
        }
        arr.push_back(atoi(foo));
    }
    mergeSort(arr, 0, arr.size() - 1, compInt);
    printf("%lld", ans);
    return 0;
}

template <class T>
void awesomeSwap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

template<class T>
void mergeSort (Array<T> arr, int l, int r, bool comp(T a, T b)) {
    if (r - l <= 1) {
        if (comp(arr[r], arr[l])) {
            awesomeSwap(arr[l], arr[r]);
            ans += 1;
        }
        return;
    }
    mergeSort (arr, l, (l + r) / 2, comp);
    mergeSort (arr, (l + r) / 2, r, comp);
    merge(arr, l, (l + r) / 2, r, comp);
}

template <class T>
void merge(Array<T> arr, int left, int half, int right, bool comp(T a, T b)) {
    assert(left < right);
    assert(left >= 0);
    assert(half < right);
    assert(left < half);
    int l_size = half - left;
    int r_size = right - half;
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
            if (l_half[l] != r_half[r]) {
                ans += ((half - left) - l);
            }
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

template <typename T>
Array<T>::Array() {
    length = 0;
    maxLength = 1;
    buffer = (T*) malloc (sizeof (T));
}

template <typename T>
Array<T>::Array(size_t size) {
    length = (int) size;
    maxLength = (int) size;
    buffer = (T*) malloc (maxLength * sizeof (T));
}
template <typename T>
Array<T>::Array(const char * filePath) {
    length = 0;
    maxLength = 1;
    buffer = (T*) malloc (sizeof (T));
    FILE *file = freopen(filePath, "r", stdin);
    int foo = -1;
    while (!feof(file)) {
        fscanf(file, "%d", &foo);
        push_back(foo);
    }
    fclose(stdin);
}

template <typename T>
Array<T>::~Array() {
    //free(buffer);
    length = 0;
    maxLength = 0;
}

template <typename T>
T Array<T>::getElement(int index) {
    assert((index < length) && (0 <= index));
    return buffer[index];
}

template <typename T>
void Array<T>::push_back(T insertingElement) {
    if (length == maxLength) resize();
    buffer[length++] = insertingElement;
}

template <typename T>
void Array<T>::push(int index, T insertingElement) {
    assert ((index < length) && (0 <= index));
    if (length == maxLength) resize();
    for (int i = length; i > index; --i) {
        buffer[i] = buffer[i-1];
    }
    buffer[index] = insertingElement;
}

template <typename T>
T& Array<T>:: operator[] (int index) {
    assert((index < length) && (0 <= index));
    return buffer[index];
}

template <typename T>
void Array<T>::pop(int index) {
    assert ((index < length) && (0 <= index));
    for (int i = index; i < length - 1; ++i) {
        buffer[i] = buffer[i+1];
    }
    --length;
}

template <typename T>
int Array<T>::size() {
    return length;
}

template <typename T>
void Array<T>::resize(){
    maxLength *= 2;
    T* newBuffer = (T *) realloc(buffer, sizeof (T) * (maxLength));
    assert(newBuffer != NULL);
    buffer = newBuffer;
}

template <typename T>
void Array<T>::saveToFile (const char * filePath) {
    freopen(filePath, "w", stdout);
    for (int i = 0; i < length; ++i) {
        printf("%d ", buffer[i]);
    }
    fclose(stdout);
}
