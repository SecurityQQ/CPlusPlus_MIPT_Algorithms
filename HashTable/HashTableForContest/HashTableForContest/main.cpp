//
//  main.cpp
//  HashTableForContest
//
//  Created by Александр Малышев on 18.03.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <assert.h>
#include <iostream>
#include <typeinfo>

typedef unsigned long long ull;
#define CHashTableNodeNILL (-1)
#define defaultTableSize 8



template <class tKey>
class CHashTable {
public:
    
    CHashTable(tKey defKey);
    CHashTable(tKey defKey, ull tableSize);
    ~CHashTable();
    
    void setDefaultKey(tKey defaultKey);
    void add      (const tKey& key);
    void remove   (const tKey& key);
    bool contains (const tKey& key);
    
private:
    ull keysCount;
    ull hash (const tKey& key);
    ull stringsHash1 (const tKey& key);
    void rehash();
    
    struct CHashTableNode {
        tKey key;
        CHashTableNode *next;
        CHashTableNode() {
            next = NULL;
        }
    };
    
    CHashTableNode defaultNode;
    std::vector<CHashTableNode *> table;
    
    ull getPrime(const ull seed);
    
    
    ull hashSeed;
    
    
    void growHashTable();
    //not allowed constructors:
    CHashTable();
    CHashTable(CHashTable &);
    
    
};

#pragma mark - CHashTable implementation

template <class tKey>
CHashTable<tKey>:: CHashTable(tKey defKey) {
    keysCount = 0;
    hashSeed = getPrime(defaultTableSize);
    defaultNode.key = defKey;
    
    for( ull i = 0; i < defaultTableSize; ++i ) {
        CHashTableNode * initNode = new CHashTableNode;
        initNode[0] = defaultNode;
        table.push_back(initNode);
    }
}

template <class tKey>
CHashTable<tKey>:: CHashTable(tKey defKey, ull tableSize) {
    keysCount = 0;
    defaultNode.key = defKey;
    hashSeed = getPrime(tableSize);
    for( ull i = 0; i < tableSize; ++i ) {
        CHashTableNode * initNode = new CHashTableNode;
        initNode[0] = defaultNode;
        table.push_back(initNode);
    }
}



template <class tKey>
void CHashTable<tKey>:: growHashTable() {
    for( ull i = 0; i < table.size(); ++i ) {
        if( table[i]->key != defaultNode.key ) {
            CHashTableNode *emptyNode = new CHashTableNode;
            emptyNode[0] = defaultNode;
            delete table[i];
            table[i] = emptyNode;
        }
    }
    ull addingSize = table.size();
    for( ull i = 0; i < addingSize; ++i ) {
        CHashTableNode *emptyNode = new CHashTableNode;
        emptyNode[0] = defaultNode;
        table.push_back(emptyNode);
    }
    
    keysCount = 0;
    hashSeed = getPrime(table.size());
}

template <class tKey>
CHashTable<tKey>:: ~CHashTable() {
    for( ull i = 0; i < table.size(); ++i ) {
        delete table[i];
    }
}

template <class tKey>
ull CHashTable<tKey>::hash (const tKey& key) {
    
    if( typeid(tKey) == typeid(std::string) ) {
        return stringsHash1(key);
    }
    
    return 1;
}

template <class tKey>
ull CHashTable<tKey>::stringsHash1 (const tKey& key) {
    assert(typeid(tKey) == typeid(std::string));
    ull hash = 0;
    for( ull i = 0; i < key.size() - 1; ++i ) {
        hash = (hash * hashSeed + key[i + 1]) % table.size();
    }
    hash = (hash + key[key.size() - 1]) % table.size();
    return hash;
}


template <class tKey>
ull CHashTable<tKey> ::getPrime(const ull seed) {
    std::vector<ull> primes;
    ull lp [seed + 1];
    for( ull i = 2; i <= seed; ++i ) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes.push_back(i);
        }
        for (ull j = 0; j < (int) primes.size() && primes[j] <= lp[i] && i * primes[j] <= seed; ++j){
            lp[i * primes[j]] = primes[j];
        }
    }
    return primes[primes.size() - 1];
}

template <class T>
void CHashTable<T>:: add (const T& key ) {
    
    if( keysCount / table.size() >= 1) {
        rehash();
    }
    
    ++keysCount;
    ull index = hash(key);
    CHashTableNode *newNode = new CHashTableNode;
    newNode->key = key;
    
    if( table[index]->key == defaultNode.key ) {
        table[index] = newNode;
    } else {
        CHashTableNode *root = table[index];
        while( root->next != NULL ) {
            root = root->next;
        }
        root->next = newNode;
    }
//    printf("Hashed with size: %lld\n", index);
}

template <class tKey>
bool CHashTable<tKey>:: contains (const tKey& key) {
    
    ull index = hash(key);
    CHashTableNode *root = table[index];
    
    if( table[index]->key == defaultNode.key ) {
        return false;
    }
    
    while( root-> next != NULL) {
        if( root-> key == key ) {
            return true;
        }
        root = root->next;
    }
    
    if( root-> key == key ) {
        return true;
    }
    
    return false;
}

template <class tKey>
void CHashTable<tKey>:: remove (const tKey& key) {
    
    ull index = hash(key);
    CHashTableNode *root = table[index];
    CHashTableNode *prev = root;
    while( root-> next != NULL ) {
        if( root->key == key ) {
            if( root == table[index] ) {
                table[index] = root -> next;
                prev = table[index];
                delete root;
                root = table[index];
            } else {
                prev->next = root->next;
                delete root;
                root = prev->next;
            }
        } else {
            prev = root;
            root = root->next;
        }
    }
    
    if( root->key == key ) {
        prev->next = NULL;
        if( root != table[index] ) {
            delete root;
        } else {
            table[index][0] = defaultNode;
        }
    }

    --keysCount;
}

template <class tKey>
void CHashTable<tKey>:: rehash() {
    std::vector<tKey> allKeys;
    
    for( ull i = 0; i < table.size(); ++i ) {
        CHashTableNode *root = table[i];
        while( root -> next != NULL ) {
            allKeys.push_back(root->key);
            root = root->next;
        }
        if( root->key != defaultNode.key ) {
            allKeys.push_back(root->key);
        }
    }
    
    growHashTable();
    
    for( ull i = 0; i < allKeys.size(); ++i ) {
        add(allKeys[i]);
    }
    
}

int main(int argc, const char * argv[]) {

    CHashTable<std::string> hashTable("");
    char ch;
    std::string key;

///Tester:
//    srand(time(0));
//    for( int i = 0; i < 100000; ++i ) {
//        std::cout<<"i : "<< i << std::endl;
//        int randomN = rand() % 100000;
//        std::string temp(std::to_string(randomN));
//        std::cout<< temp <<std::endl;
//        hashTable.add(temp);
//    }
//  
//    
//    for( int i = 0; i < 10; ++i ) {
//        int randomN = rand() % 100000;
//        std::string key(std::to_string(randomN));
//        
//        if( random() % 2 ) {
//            if( hashTable.contains(key) ) {
//                std::cout<<"deleting key: " <<key << std::endl;
//                hashTable.remove(key);
//            }
//        }
//    }
//    

    
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
