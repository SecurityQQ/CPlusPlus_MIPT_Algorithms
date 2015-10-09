//
//  main.cpp
//  r-value l-value
//
//  Created by Александр Малышев on 04.07.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <iostream>

using namespace std;

string answer() {
    return "13";
}

template <class T>
class A {
public:
    void friend func(A<T> a);
    
private:
    int x = 0;
};

template <class T>
void func(A<T> a) {
    a.x = 5;
    std::cout<<"Hello"<<std::endl;
}

int main(int argc, const char * argv[]) {
//    string const& asdf = answer();
//    string& qwer = answer();
    
    A<int> a;
    func(a);
    
    return 0;
}
