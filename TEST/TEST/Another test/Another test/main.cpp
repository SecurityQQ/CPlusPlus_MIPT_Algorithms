//
//  main.cpp
//  Another test
//
//  Created by Александр Малышев on 05.07.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

template <class ForwardIterator, class T>
ForwardIterator lb (ForwardIterator first, ForwardIterator last, const T& val)
{
    ForwardIterator it;
//    iterator_traits<ForwardIterator>::difference_type count, step;
    auto count = distance(first,last);
    while (count>0)
    {
        it = first; auto step=count/2; advance (it,step);
        if (*it<val) {                 // or: if (comp(*it,val)), for version (2)
            first=++it;
            count-=step+1;
        }
        else count=step;
    }
    return first;
}

class T {
public:
    virtual void cock() { std::cout<<"T::cock"<<std::endl;}
    virtual void suck() { std::cout<<"T::suck"<<std::endl;}
    virtual void dick() { std::cout<<"T::dick"<<std::endl;}
};

class A : public T{
public:
    virtual void cock() { std::cout<<"A::cock"<<std::endl;}
    virtual void pinus() { std::cout<<"A::pinus"<<std::endl;}
};

class AS {
public:
    static void staticmethod();
};

void doNothing() {}


class C {
public:
    void f() { };
};

struct cock {
    virtual ~cock() {}
};

struct dick : virtual cock {
    
};

int main(int argc, const char * argv[]) {
//    std::vector<int> a {5, 7, 2, 3, 4, 5, 6, 7};
//    A a;
//    std::cout<<sizeof(A)<<std::endl;
//    std::cout<<sizeof(AS)<<std::endl;

    A asdf;
    T x = asdf;
    void (*ptr)() = &doNothing;
    AS singleton;
    C notSingleton;
    void (*ptr3)() = &(singleton.staticmethod);
    x.cock();

    double buf = 5;
    uint64_t& b = reinterpret_cast<uint64_t&>(buf);
    std::cout<<b<<std::endl;
    printf("buf: %p, b: %p\n", buf, b);
    
    int&& rval = 5;
    int intger = 4;
    int&  qqq=  &intger;
    
    std::cout<<typeof(&rval) == typeof(&&asdf)<<std::endl;
    
    
//    int x = 6;
//    std::cout<<*lb(a.begin(), a.end(), x)<<std::endl;
    return 0;
}
