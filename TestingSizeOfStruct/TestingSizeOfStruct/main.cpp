//
//  main.cpp
//  TestingSizeOfStruct
//
//  Created by Alexander Malyshev on 18.09.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#include <iostream>
#include <set>
#include <vector>

struct S {
    short x;
    char y;
    int z;
};

struct S2 {
    char y;
    short x;
    int z;
};

struct S3 {
    int z;
    char y;
    short x;
};

struct S4 {
    int x:30;
    int y:2;
    int z:1;
};

int main(int argc, const char * argv[]) {
    std::vector<int> ans(5);
    int sum = 0;
    const int NUMOFTESTS = 100000;
    for (int j = 0; j < NUMOFTESTS; ++j) {
        std::multiset<int> box1 = {0, 1, 1};
        std::multiset<int> box2 = {0, 0, 1, 1, 1};
        std::multiset<int> box3;
        
        srand(time(NULL));
        for (int i = 0; i < 2; ++i) {
            auto item = rand() % 2;
            while (box1.find(item) == box1.end()) {
                item = random() % 2;
            }
            
            
            box1.erase(box1.find(item));
            box3.insert(item);
            
            item = random() % 2;
            while (box2.find(item) == box2.end()) {
                item = rand() % 2;
            }
            
            box2.erase(box2.find(item));
            box3.insert(item);
            
        }
        
        
        int blacks = 0;
        for (auto it = box3.begin(); it != box3.end(); ++it) {
            blacks += *it;
        }
//        std::cout<<blacks <<std::endl;
        ans[blacks]++;
    }
    
    
    std::cout<<"Probabilities: \n";
    for (int i = 1; i < ans.size(); ++i) {
        std::cout<<i<< ": "<<(double)ans[i] / (double)NUMOFTESTS <<std::endl;
    }
    
    return 0;
}

//1: 0.124681
//2: 0.373667
//3: 0.375657
//4: 0.125995
    
//1: 0.180986
//2: 0.430985
//3: 0.318906
//4: 0.069123

//1: 0.13497
//2: 0.38303
//3: 0.36795
//4: 0.11405
