//
//  HashTable.h
//  HashTable
//
//  Created by Александр Малышев on 09.03.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#ifndef __HashTable__HashTable__
#define __HashTable__HashTable__

#include <stdio.h>
#include <vector>
#include <assert.h>
#include <iostream>

typedef unsigned long long ull;
#define CHashTableNodeNILL (-1)
#define defaultTableSize 8



template <class tKey>
class CHashTable {
public:
    
    CHashTable();
    CHashTable(ull tableSize);
    ~CHashTable();
    
    void add      (const tKey& key);
    void remove   (const tKey& key);
    bool contains (const tKey& key);
    
private:
    ull keysCount = 0;
    ull hash (const tKey& key);
    ull stringsHash1 (const tKey& key);
    ull stringsHash2 (const tKey& key);
    void rehash();
    
    struct CHashTableNode {
        tKey key;
        CHashTableNode *next = NULL;
    };
    
    std::vector<CHashTableNode *> table;
    
    ull getPrime(const ull seed);
    
    
    ull hashSeed = getPrime(defaultTableSize);
    
    
    void growHashTable();
};

#pragma mark - CHashTable implementation

template <class tKey>
CHashTable<tKey>:: CHashTable() {
    table.assign( defaultTableSize, NULL);
}

template <class tKey>
CHashTable<tKey>:: CHashTable(ull tableSize) {
    table.assign( tableSize, NULL);
}



template <class tKey>
void CHashTable<tKey>:: growHashTable() {
    ull newSize = table.size() * 2;
    table.assign(newSize, NULL);
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
        return stringsHash2(key);
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
ull CHashTable<tKey>::stringsHash2 (const tKey& key) {
    char *str = new char[key.size()];
    memcpy(str, key.data(), key.size() * sizeof(char));
    ull hash = 0;
    
    for (; *str; str++)
    {
        hash += (unsigned char)(*str);
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    
    return hash % table.size();
}

template <class tKey>
ull CHashTable<tKey> ::getPrime(const ull seed) {
    return 1;
    //        std::vector<ull> primes;
    //        ull lp [seed + 1];
    //        for( ull i = 2; i <= seed; ++i ) {
    //            if (lp[i] == 0) {
    //                lp[i] = i;
    //                primes.push_back(i);
    //            }
    //            for (ull j = 0; j < (int) primes.size() && primes[j] <= lp[i] && i * primes[j] <= seed; ++j){
    //                lp[i * primes[j]] = primes[j];
    //            }
    //        }
    //    return primes[primes.size() - 1];
}

template <class T>
void CHashTable<T>:: add (const T& key ) {
    
    if( keysCount / table.size() >= 1) {
        rehash();
    }
    
    ++keysCount;
    ull index = hash(key);
    CHashTableNode *tableNode = new CHashTableNode;
    tableNode[0].key = key;
    
    if( table[index] == NULL ) {
        table[index] = tableNode;
    } else {
        CHashTableNode *root = table[index];
        while( root->next != NULL ) {
            root = root->next;
        }
        root->next = tableNode;
    }
    //    std::cout<<key.data();
    //    printf("Hashed with size: %lld\n", index);
}

template <class tKey>
bool CHashTable<tKey>:: contains (const tKey& key) {
    
    ull index = hash(key);
    CHashTableNode *root = table[index];
    
    if( table[index] == NULL ) {
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
    if( root == NULL ) {
        return;
    }
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
            table[index] = NULL;
        }
    }
    
    --keysCount;
}

template <class tKey>
void CHashTable<tKey>:: rehash() {
    std::vector<tKey> allKeys;
    
    for( ull i = 0; i < table.size(); ++i ) {
        if( table[i] != NULL ) {
            CHashTableNode *root = table[i];
            while( root -> next != NULL ) {
                allKeys.push_back(root->key);
                root = root->next;
            }
            if( root != NULL ) {
                allKeys.push_back(root->key);
            }
        }
    }
    
    growHashTable();
    
    for( ull i = 0; i < allKeys.size(); ++i ) {
        add(allKeys[i]);
    }
    
}

#endif /* defined(__HashTable__HashTable__) */
