//
//  main.cpp
//  Prefix-Z-Function
//
//  Created by Alexander Malyshev on 05.11.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#include <iostream>
#include <vector>

typedef long StringSizeType;

class PrefixFunction: public std::vector<StringSizeType> {
public:
    
    PrefixFunction(const std::vector<StringSizeType>& vector): std::vector<StringSizeType>(vector) {
        
    }
    
    PrefixFunction(const std::string& string): std::vector<StringSizeType>(string.size()) {
        for (StringSizeType i = 1; i < size(); ++i) {
            StringSizeType j = this->at(i-1);
            while ((j > 0) && string[i] != string[j]) {
                j = this->at(j-1);
            }
            if (string[i] == string[j]) {
                ++j;
            }
            this->at(i) = j;
        }
    }
    
    void print() {
        for (StringSizeType i = 0; i < size(); ++i) {
            std::cout<<this->at(i) <<" ";
        }
        std::cout<<std::endl;
    }
    
    const std::string minLexString() {
        std::string stringFromPrefixFunction(size(), 'a');
        for (StringSizeType i = 1; i < size(); ++i) {
            if (this->at(i) == 0) {
                stringFromPrefixFunction[i] = stringFromPrefixFunction[this->at(i - 1)] + 1;
            } else {
                stringFromPrefixFunction[i] = stringFromPrefixFunction[this->at(i) - 1];
            }
        }
        return stringFromPrefixFunction;
    }
};

class ZFunction: public std::vector<StringSizeType> {
public:
    
    ZFunction(const std::vector<StringSizeType>& vector): std::vector<StringSizeType>(vector) {}
    
    ZFunction(const std::string& string): std::vector<StringSizeType>(string.size()) {
        leftBound = 0;
        rightBound = 0;
        this->at(0) = string.size();
        for (StringSizeType i = 1; i < size(); ++i) {
            if (i <= rightBound) {
                this->at(i) = std::min(rightBound - i + 1, this->at(i-leftBound));
            }
            while (i + this->at(i) < string.size() && string[this->at(i)] == string[i + this->at(i)]) {
                ++this->at(i);
            }
            if (i + this->at(i) - 1 > rightBound) {
                leftBound = i;
                rightBound = i + this->at(i) - 1;
            }
        }
    }
    
    void print() {
        for (StringSizeType i = 0; i < size(); ++i) {
            std::cout<<this->at(i) <<" ";
        }
        std::cout<<std::endl;
    }
    
    const std::string minLexString() {
        std::string stringFromPrefixFunction(size(), 'a');
        StringSizeType lastSavedSymbolIndex = 0;
        for (StringSizeType i = 1; i < size(); ++i) {
            
            if (this->at(i) == 0) {
                stringFromPrefixFunction[i] = stringFromPrefixFunction[lastSavedSymbolIndex] + 1;
                lastSavedSymbolIndex = this->at(i);
                continue;
            }
            
            for (StringSizeType j = 0; j < this->at(i); ++j) {
                stringFromPrefixFunction[i + j] = stringFromPrefixFunction[j];
            }
            lastSavedSymbolIndex = this->at(i);
            i += this->at(i) - 1;
            
        }
        
        return stringFromPrefixFunction;
    }
    
    StringSizeType getLeftBound() const {
        return leftBound;
    }
    
    StringSizeType getRightBound() const {
        return rightBound;
    }
    
private:
    StringSizeType leftBound;
    StringSizeType rightBound;
};


PrefixFunction getPrefixFunctionFromZFunction(ZFunction &zFunction) {
    std::vector<StringSizeType> prefixFunction(zFunction.size(), 0);
    for (int i = 1; i < zFunction.size(); ++i) {
        for (int j = zFunction[i] - 1; j >= 0 && prefixFunction[i + j] == 0; --j) {
            prefixFunction[i + j] = j + 1;
        }
    }
    return PrefixFunction(prefixFunction);
}


int main(int argc, const char * argv[]) {
    StringSizeType foo;
    std::vector<StringSizeType> vec;
    char c;
    
    std::cin>>foo;
    vec.push_back(foo);
    std::cin.get(c);
    if (c == '\n' || c == '\0') {
        std::cout<<ZFunction(vec).minLexString();
        return 0;
    }
    do {
        if (!(std::cin >> foo)) {
            break;
        }
        vec.push_back(foo);
    } while (std::cin.get(c) && c != '\0' && c != '\n');

    vec[0] = 0;
    auto zf = ZFunction(vec);
    auto pf = getPrefixFunctionFromZFunction(zf);
    auto minLexStr = pf.minLexString();
    std::cout<<minLexStr<<std::endl;
    return 0;
}
