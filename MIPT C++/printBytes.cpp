//
//  printBytes.cpp
//  MIPT C++
//
//  Created by Александр Малышев on 05.10.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//

#include "printBytes.h"
void print_bytes(const void* mem, int size) {
    const unsigned char* pChars = (unsigned char*) mem;
    for (int i = size - 1; i >= 0 ; --i) {
        for (int j = 7; j >= 0; j--)
            printf("%d",(pChars[i]&(1<<j))>>j);
            printf(" ");
    }
}