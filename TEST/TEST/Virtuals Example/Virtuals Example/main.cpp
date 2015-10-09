//
//  main.cpp
//  Virtuals Example
//
//  Created by Александр Малышев on 04.07.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//
#include <iostream>
using namespace std;

class BaseClass{
public:
    BaseClass(){
        print_it();
    }
    virtual void print_it() {
        cout << "BaseClass print_it" << endl;
    }
};

class DerivedClass : public BaseClass {
public:
    DerivedClass() {
        print_it();
    }
    virtual void print_it(){
        cout << "Derived Class print_it" << endl;
    }
};

int main() {
    
    DerivedClass dc;
}