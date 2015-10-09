//
//  main.cpp
//  One More Virtuals Example
//
//  Created by Александр Малышев on 04.07.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <iostream>


class A {
    int a;
public:
    int puba;
    void foo() { std::cout<<"FOO A"<<std::endl;}
protected:
    int prota;
private:
    int priva;
};

class B : virtual public A {
    int b;
public:

//    void foo() { std::cout<<"FOO B"<<std::endl;}
};
class B2 : virtual public A {
    int b2;
public:
//    void foo() { std::cout<<"FOO B2"<<std::endl;}
};

class C : public B, public B2 {
    int c;
public:
//    void foo() { std::cout<<"FOO C"<<std::endl;}
};

int main(int argc, const char * argv[]) {
    C c;
    c.foo();

    return 0;
}
