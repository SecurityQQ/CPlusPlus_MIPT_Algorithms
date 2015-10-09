//
//  main.cpp
//  Auto generating code
//
//  Created by Александр Малышев on 04.07.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <iostream>
#include <deque>

class A {
public:
//    A();
//    const int func() { return 1;};
//    ~A();
};

class B {
public:
};


class C {
public:
    C() {
        try {
            throw B();
        } catch (B) {
            std::cout<<"Catched B"<<std::endl;
        }
    }
    void func() throw(A, B);
};

void C::func() {
    int a = 5;
    int b = 0;
    
    if (b == 0) {
        if (a == 5) {
            throw A();
        } else {
            throw B();
        }
    } else {
        a = 5 / b;
        std::cout<<a<<std::endl;
    }
}

template <class T, class T2>
void func2(T a, T2 b) {
    //
}

template <class T2>
void func2(int a, T2 b) {
    std::cout<<a<<std::endl;
}

int main(int argc, const char * argv[]) {
//    C c;
//    try {
//        c.func();
//    } catch (A) {
//        std::cout<<"Zero dividing"<<std::endl;
//    }
//
    std::deque<int> asdf;
    func2(5, 5.0);
    return 0;
}
