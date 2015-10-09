//
//  main.cpp
//  OpenAdressForContest
//
//  Created by Александр Малышев on 22.03.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <assert.h>
#include <iostream>
#include <memory.h>

typedef unsigned long long ull;
#define NullString ""
#define DelString "DEL"
#define defaultTableSize (8)



class OpenAdressedHashTable {
public:
    
    OpenAdressedHashTable();
    OpenAdressedHashTable(ull tableSize);
    ~OpenAdressedHashTable();
    
    void add      (const std::string& key);
    void remove   (const std::string& key);
    bool contains (const std::string& key);
    
    
    
private:
    
    ull hash(const std::string &key);
    ull tryToHash(const std::string &key, ull i);
    void rehash();
    
    
    std::vector<std::string> table;
    
    void growHashTable();
    
    //not allowed constructors:
    
};

OpenAdressedHashTable:: OpenAdressedHashTable() {
    for( ull i = 0; i < defaultTableSize; ++i ) {
        table.push_back(NullString);
    }
}
OpenAdressedHashTable:: OpenAdressedHashTable( ull tableSize) {
    for( ull i = 0;i < tableSize; ++i ) {
        table.push_back(NullString);
    }
}

OpenAdressedHashTable:: ~OpenAdressedHashTable() {
    table.erase(table.begin(), table.end());
}

ull OpenAdressedHashTable::tryToHash(const std::string &key, ull i){
    
    return (ull)(hash(key) + 0.5 * i + 0.5 * i * i) % table.size();
}

ull OpenAdressedHashTable::hash(const std::string &key){
    char *str = new char[key.size()];
    memcpy(str, key.data(), key.length() + 1);
    ull hash = 0;
    for (ull i = 0; i < key.length(); ++i) {
        hash += (unsigned char)(str[i]);
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    delete [] str;
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    
    return hash % table.size();
}


void OpenAdressedHashTable:: rehash() {
    std::vector<std::string> keys;
    for( ull i = 0; i < table.size(); ++i ) {
        if( table[i] != DelString && table[i] != NullString ) {
            keys.push_back(table[i]);
        }
    }
    
    growHashTable();
    
    for( ull i = 0; i < keys.size(); ++i ) {
        add(keys[i]);
    }
    
}

void OpenAdressedHashTable:: growHashTable() {
    for( ull i = 0; i < table.size(); ++i ) {
        table[i] = NullString;
    }
    ull appendingSize = table.size() / 2;
    for( ull i = 0; i < appendingSize; ++i ) {
        table.push_back(NullString);
    }
    
}


void OpenAdressedHashTable:: add(const std::string &key) {
    
    for( ull i = 0; i < table.size() ; ++i ) {
        ull index = tryToHash(key, i);
        
        if( table[index] == NullString || table[index] == DelString) {
            table[index] = key;
            return;
        }
    }
    
    rehash();
    add(key);
}

bool OpenAdressedHashTable:: contains(const std::string &key) {
    
    for( ull i = 0; i < table.size(); ++i ) {
        ull index = tryToHash(key, i);
        if( table[index] == key ) {
            return true;
        }
        if( table[index] == NullString ) {
            return false;
        }
    }
    return false;
}

void OpenAdressedHashTable:: remove(const std::string &key) {
    for( ull i = 0; i < table.size(); ++i ) {
        ull index = tryToHash(key, i);
        if( table[index] == DelString ) {
            return;
        }
        if( table[index] == key ) {
            table[index] = DelString;
        }
    }
}


int main(int argc, const char * argv[]) {
    OpenAdressedHashTable hashTable;
    char ch;
    std::string key;
    while( !std::cin.fail() ) {
        ch = EOF;
        std::cin>> ch >> key;
        switch (ch) {
            case '+':
                if( hashTable.contains(key) ) {
                    std::cout<<"FAIL" <<std::endl;
                } else {
                    hashTable.add(key);
                    std::cout<<"OK" <<std::endl;
                }
                break;
            case '?':
                if( hashTable.contains(key) ) {
                    std::cout<<"OK" <<std::endl;
                } else {
                    std::cout<<"FAIL" <<std::endl;
                }
                break;
            case '-':
                if( hashTable.contains(key) ) {
                    hashTable.remove(key);
                    std::cout<<"OK" <<std::endl;
                } else {
                    std::cout<<"FAIL" <<std::endl;
                }
                break;
            default:
                exit(0);
                try {
                    throw "Incorrect operation";
                } catch (char * errorMsg) {
                    std::cerr<< errorMsg <<std::endl;
                    exit(1);
                }
                break;
        }
    }
    return 0;
}
