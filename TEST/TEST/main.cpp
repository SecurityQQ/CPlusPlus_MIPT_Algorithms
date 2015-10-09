//
//  main.cpp
//  TEST
//
//  Created by Александр Малышев on 16.03.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <iostream>
#include <assert.h>
#include <vector>
#include <array>
#include <queue>

using namespace std;

class Base{
public:
    Base(){ cout << "B "; }
    virtual ~Base(){ cout << "~B "; }
};
class Derive: virtual public Base{
public:
    Derive(){ cout << "D "; }
    ~Derive(){ cout << "~D "; }
};

int main(int argc, const char * argv[]) {
    Base *p = new Derive;
    delete p;
    return 0;
}
