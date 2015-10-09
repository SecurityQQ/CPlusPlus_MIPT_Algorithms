//
//  main.cpp
//  HashTable
//
//  Created by Александр Малышев on 09.03.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <iostream>
#include "HashTable.h"
#include <unordered_set>
#include "OpenAdressedHashTable.h"
#include "CocoHashTable.h"

int main(int argc, const char * argv[]) {
    OpenAdressedHashTable hashTable;
//    CocoHashTable hashTable;
    char ch;
    std::string key;

    
//    for( int i = 0; i < 1000; ++i ) {
//        int randomN = rand() % 1000;
//        std::string temp(std::to_string(randomN));
//        hashTable.add(temp);
//    }
//    
//    for( int i = 0; i < 1000; ++i ) {
//        int randomN = rand() % 1000;
//        std::string temp(std::to_string(randomN));
//        hashTable.remove(temp);
//    }
    
//    printf("Magic!\n");
    
//    Tester:
//
    
        srand(time(0));
    clock_t start = clock();
        for( int i = 0; i < 1000; ++i ) {
            int randomN = rand() % 1000;
            std::string temp(std::to_string(randomN));
            hashTable.add(temp);
        }
    
    
        for( int i = 0; i < 1000; ++i ) {
            int randomN = rand() % 1000;
            std::string key(std::to_string(randomN));
    
            if( random() % 2 ) {
                if( hashTable.contains(key) ) {
                    hashTable.remove(key);
                }
            }
        }
    
    clock_t end = clock();
    std::cout<< end - start <<std::endl;
    
    
    std::unordered_set<std::string> stlHashTable;
    
    start = clock();
    for( int i = 0; i < 1000; ++i ) {
        int randomN = rand() % 1000;
        std::string temp(std::to_string(randomN));
        stlHashTable.insert(temp);
    }

    
    for( int i = 0; i < 1000; ++i ) {
        int randomN = rand() % 1000;
        std::string key(std::to_string(randomN));
        if( random() % 2 ) {
            stlHashTable.erase(key);
        }
    }
    
    end = clock();
    std::cout<< end - start <<std::endl;

//
//    
//    

    
    
//    
//    while( ch != EOF ) {
//        std::cin>> ch >> key;
//        switch (ch) {
//            case '+':
//                if( hashTable.contains(key) ) {
//                    std::cout<<"FAIL" <<std::endl;
//                } else {
//                    hashTable.add(key);
//                    std::cout<<"OK" <<std::endl;
//                }
//                break;
//            case '?':
//                if( hashTable.contains(key) ) {
//                    std::cout<<"OK" <<std::endl;
//                } else {
//                    std::cout<<"FAIL" <<std::endl;
//                }
//                break;
//            case '-':
//                if( hashTable.contains(key) ) {
//                    hashTable.remove(key);
//                    std::cout<<"OK" <<std::endl;
//                } else {
//                    std::cout<<"FAIL" <<std::endl;
//                }
//                break;
//            default:
//                try {
//                    throw "Incorrect operation";
//                } catch (char * errorMsg) {
//                    std::cerr<< errorMsg <<std::endl;
//                    exit(1);
//                }
//                break;
//        }
//    }

    return 0;
}
