 //
//  splitString.cpp
//  MIPT C++
//
//  Created by Александр Малышев on 03.10.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//

#include "splitString.h"
#include <iostream>




int length (const char * str) {
    //int len = 0;
    //while (str[len] != '\0') ++len;
    return strlen(str);
}

char** split(const char *str, const char *delim) {
    int lenOfStr = length(str), lenOfDelim = length(delim);
    int elementsInSplitedString = 0;
    char **splitedString;
    char * nullStr = "\0";
    splitedString = (char **) malloc(sizeof(char *));
    int lastSavedPos = 0;
    int i = 0, size;
    while (i < lenOfStr) {
        int j = 0;
        int lastPos = i;
        while (str[lastPos] == delim[j]) {
            ++lastPos;
            ++j;
            if (j == lenOfDelim) {
                size = i - lastSavedPos;
                if (!i) ++size;
                ++elementsInSplitedString;
                splitedString = (char **) realloc(splitedString, (elementsInSplitedString) * sizeof(char *));
                splitedString[elementsInSplitedString - 1] = (char *) malloc((size) * sizeof(char));
                memcpy(splitedString[elementsInSplitedString - 1], str + lastSavedPos, size);
                splitedString[elementsInSplitedString - 1][length(splitedString[elementsInSplitedString - 1])] = '\0';
                i = lastPos;
                lastSavedPos = i;
                break;
            }
        }
    ++i;
    }
    size = lenOfStr - lastSavedPos;
    splitedString[elementsInSplitedString] = (char *) malloc(size * sizeof(char));
    memcpy(splitedString[elementsInSplitedString], str + lastSavedPos, size);
    return splitedString;
}
void delete_string_array(char **str) {
    for (int i = 0; i <length(*str); ++i)
        free(str[i]);
}
