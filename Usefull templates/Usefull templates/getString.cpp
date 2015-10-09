//
//  getString.cpp
//  Usefull templates
//
//  Created by Александр Малышев on 17.03.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <stdio.h>

char* getString(FILE * input) {
    char ch = '\0';
    char *str = (char *) malloc(sizeof(char));
    int length = 0;
    int maxLength = 1;
    
    while( (ch = getc(input) ) != '\n' ) {
        if( maxLength >= length - 1 ) {
            maxLength *= 2;
            char *newStr = (char*) malloc(maxLength * sizeof(char));
            if( newStr != NULL ) {
                memcpy(newStr, str, length * sizeof(char));
                free(str);
                str = newStr;
            } else {
                exit(1);
            }
        }
        str[length] = ch;
        ++length;
    }
    
    str[length] = '\0';
    return str;
}

int main(int argc, const char * argv[]) {
    std::cout<<getString(stdin);
    return 0;
}