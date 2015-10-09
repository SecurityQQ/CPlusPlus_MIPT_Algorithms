//
//  main.cpp
//  Non working example
//
//  Created by Александр Малышев on 04.07.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <iostream>

class A
{
    int a;
public:
    void foo(){ a = 0; };
};
class B1 : public A{ int b1;};
class B2 : public A{ int b2;};
class C : public B1, public B2{int c;};

int main(int argc, const char * argv[]) {
    C c;
    c.B1::foo();
    return 0;
}
