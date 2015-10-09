//////
//////  Array.h
//////  MIPT C++
//////
//////  Created by Александр Малышев on 30.09.14.
//////  Copyright (c) 2014 SecurityQQ. All rights reserved.
//////


//#ifndef __MIPT_C____Array__
//#define __MIPT_C____Array__
//typedef long long ll ;
//template <typename T>
//class matrix {
//public:
//    matrix () ;
//    matrix (int cols, int rows);
//    ~matrix () ;
//    ll rows, cols;
//    //T operator[] (int indexCols, int indexRow) ;
//    matrix operator ^ (ll n) {
//        if ( n == 1 )   return self;
//        if ( n % 2  )   return ( self ^ (n - 1) ) * self ;
//        return ( X ^ (n/2) ) * ( self ^ (n/2) ) ;
//    }
//    matrix operator * (matrix<T> Y);
//private:
//    void resize();
//    int length;
//    int maxLength;
//    T* buffer;
//};
//
//template <typename T>
//matrix<T> operator * (matrix<T> Y) {
//    matrix<T> Z(Y.cols, rows);
//}
//
//template <typename T>
//matrix operator ^ (ll n) {
//    if ( n == 1 )   return self ;
//    if ( n % 2  )   return ( self ^ (n - 1) ) * self ;
//    return ( X ^ (n/2) ) * ( self ^ (n/2) ) ;
//}
//
//
//#endif //__MIPT_C____Array__