//
//  splitString.h
//  MIPT C++
//
//  Created by Александр Малышев on 03.10.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//

#ifndef __MIPT_C____splitString__
#define __MIPT_C____splitString__

#include <stdio.h>
int length (const char *str);
char** split(const char *str, const char *delim);
void delete_string_array(char **str);
#endif /* defined(__MIPT_C____splitString__) */
