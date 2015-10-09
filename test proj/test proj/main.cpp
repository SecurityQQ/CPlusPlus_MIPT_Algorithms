//
//  main.cpp
//  test proj
//
//  Created by Александр Малышев on 24.05.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <iostream>
#include <list>
#include <stack>
#include <set>
#include <vector>
#include <Python/Python.h>
#include <map>

template <class T>
void printVecInfo(std::vector<T>& a) {
    std::cout<<"Size: "<<a.size() <<std::endl;
    std::cout<<"Capacity: "<<a.capacity() <<std::endl;
    for (auto i = a.begin(); i != a.end(); ++i) {
        std::cout<<*i <<" ";
    }
    std::cout<<std::endl;
}


/*
std::exception zeroDiv;
int div_(int a, int b) {
    if (b == 0) throw zeroDiv;
    return a / b;
}


struct CNode{
    int value;
    CNode *next;
    CNode *prev;
    char color;
};

class A {
    int _field;
public:
    A() {std::cout<<"CA "; }
    A(const A& a) {std::cout<<"CCA ";}
    A(int a): _field(a) {}
    virtual ~A() {std::cout<<"DA ";}
};

class B : public A {
public:
    B() {std::cout<<"CB ";}
    B(const B&) {std::cout<<"CCB ";}
    ~B() {std::cout<<"DB ";}
};



void func(A& a) {

}

class shoes {
    
public:
    virtual void show() { std::cout<<"shoes"<<std::endl;}

};

class redshoes : public shoes {
public:
    virtual void show() { std::cout<<"redshoes"<<std::endl; }
};

class box {
public:
    void show(shoes *p) {std::cout<<" box: "; p->show(); std::cout<<std::endl;}
    void show(redshoes *p) {std::cout<<" redbox: "; p->show(); std::cout<<std::endl;}
};

class NIKITKA_YURICH {
    int _first;
    int _second;
    
    void DoSomeAwesomeShit(const int& a) const {
        std::cout<<_first<<std::endl;
        std::cout<<_second<<std::endl;
    }
};

template <class T>
void Do(T a) {
    std::cout<<"TEMPLATE"<<std::endl;
}

template <>
void Do<int> (int a) {
    std::cout<<"INT SPEC"<<std::endl;
}

void Do(int c) {
    std::cout<<"JUST DO"<<std::endl;
}


template<typename T, template <typename, typename> typename Container>
class MyAwesomeString {
    Container<T, std::allocator<T>> buf;
};


class Aa
{
public:
    Aa()
    {
        std::cout<<"A"<<std::endl;
    }
    Aa(const Aa& src)
    {
        std::cout<<"CA"<<std::endl;
    }
    ~Aa()
    {
        std::cout<<"DA"<<std::endl;
    }
    
};

class functionator {
public:
    void f(int a) { std::cout<<"1"<<std::endl; }
    void f(int a, float b = 6) { std::cout<<"2"<<std::endl; }
    void f(double a, int b = 5) { std::cout<<"3"<<std::endl;}
    void f(float a, double b) { std::cout<<"4"<<std::endl;}
};

class Base1 { public: int Q; };
class Base2 { public: int W; };
class Derived1 : public Base1, public virtual Base2
{ public: int A; };
class Derived2 : public Base1, public virtual Base2
{ private: char B; };
class Derived3 : public virtual Derived1, public virtual Derived2
{ public: int C; };



struct MatrixRow {
    int& operator [] (int i) {
        return row[i];
    }
    std::vector<int> row;
};

class Matrix {
public:
    Matrix() {
        buf.resize(3);
        for (auto i = buf.begin(); i != buf.end(); ++i) {
            i->row.assign(3,0);
        }
    }
    ~Matrix() { }
    
    MatrixRow & operator () (int i) {
        return buf[i];
    }
    
private:
    std::vector<MatrixRow> buf;
};
*/



//class A
//{
//public:
//    A(int) { std::cout << "CA "; }
//    ~A() { std::cout << "DA "; }
//};
//
//class B
//{
//public:
//    B(int) { std::cout << "CB "; }
//    ~B() { std::cout << "DB "; }
//};
//
//class C
//{
//public:
//    C() : b(5), a(4) { std::cout << "CC "; }
//    ~C() { std::cout << "DC "; }
//private:
//    A a;
//    B b;
//};

/*
class Base {
public:
    virtual ~Base(void) {}
};
class Derived1 : public Base {
public:
    virtual ~Derived1(void) {}
};
class Derived2 : public Base {
public:
    virtual ~Derived2(void) {}
};
class Unrelated {
public:
    virtual ~Unrelated(void) {}
};


int main(int argc, char* argv[]) {
    
    Base *pb = new Derived1;
    Derived1 * pd1 = dynamic_cast<Derived1 *>(pb);
    Derived2 * pd2 = dynamic_cast<Derived2 *>(pb);
    Unrelated *pu1 = dynamic_cast<Unrelated *>(pb);
    Unrelated *pu2 = reinterpret_cast<Unrelated *>(pb);
    printf("%p %p %p %p %p\n", pb, pd1, pd2, pu1, pu2);
    return 0;
}
*/

/*
class A {
public:
    ~A() { std::cout<<"Your mum is ugly"<<std::endl;}
};

class B : public A {
public:
    void doSomeShit() {
        int x = 1; x++; x--; std::cout<<"Shit!\n"<<std::endl;
    }
    ~B() { std::cout<<"Allah"<<std::endl; }
};
*/
//int main(int argc, char* argv[])
//{
//    std::list<int> a = {1, 5, 7};
//    std::stack<int, std::allocator<int>> st {a.get_allocator()};
//    
//    std::cout<<st.top()<<std::endl;
//    
//    return 0;
//}

template <class T, template <class, class> class Container>
class myAwesomeString {
    
    
private:
    Container<T, std::allocator<T>> buf;
};

using namespace std;
int main() {
    std::vector<int> a = {3, 4, 5};
    printVecInfo(a);
    a.shrink_to_fit();
    printVecInfo(a);
    a.clear();
    printVecInfo(a);ч
    return 0;
}
//int main(int argc, const char * argv[]) {
//
//    std::list<int> l;
//    l.push_back(1);
//    l.push_back(2);
//    l.push_back(3);
//    
//    for (std::list<int>::iterator it = l.begin(), end = l.end(); it != end; ++it) {
//        if ((*it % 2) == 0) {
//            l.push_back(1);
//        }
//    }
//    
//    shoes *pa = new redshoes();
//    box *pb = new box();
//  pa->show();
//    pb->show(pa);
//    MyAwesomeString<int, std::vector> mbs;
    
    
//    int a = 5;
//    Do<int>(a);
//    Derived1 d;
    
//    C c1, c2(c1);

    
//    std::vector<int> v;
//    v.push_back(1);
//    v.push_back(2);
//    v.push_back(3);
//    v.push_back(4);
//    v.push_back(5);
//    v.push_back(6);
//    v.erase(v.begin(), v.begin() + v.size() / 2);
//    printVecInfo(v);
    

//    std::vector<Aa> v;
//    v.resize(1);
//    std::cout<<v.size()<<std::endl;
    
    
    
//    std::map<int, double> myMap;
//    
//    myMap.insert(std::make_pair(5, 5.0));
//    myMap.insert(std::make_pair(10, 13));
//    std::map<int, double>::iterator it = myMap.find(5);
////    it->first = 8;
//    myMap.insert(std::make_pair(10, 17));
//    std::cout<<myMap.size()<<std::endl;
    
    
//    std::vector<int> a;
//    a.push_back(1);
//    a.push_back(2);
//    a.push_back(3);
//    a.push_back(4);
//    a.push_back(5);

//    A a;
//    A& b = a;
    

//    const char *str = "hello";
//    char *str1 = const_cast<char*>(str);
//    str1[0] = 'H';


//    print4VecInfo(v);
    
    // CA CB CCA DA DB DA
    
    //
//    printVecInfo(a);
//    a.erase(a.begin() + 3);
//    a.clear();
//    std::cout<<y;
//    printVecInfo(a);
    
//    
//    std::set<int> mySet;
//    std::map<int, int> myMap;
//    mySet.insert(1);
//    mySet.insert(1);
//    myMap.insert(std::make_pair(1, 1));
//     myMap.insert(std::make_pair(1, 2));
//    
//    auto x = mySet.find(1);
//    while (x != mySet.end()) {
//        std::cout<<*x<<std::endl;
//        ++x;
//    }
//
//    
//    return 0;
//}
