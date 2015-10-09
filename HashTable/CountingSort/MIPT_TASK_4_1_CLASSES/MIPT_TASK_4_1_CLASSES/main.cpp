//
//  main.cpp
//  MIPT_TASK_4_1_CLASSES
//
//  Created by Александр Малышев on 11.02.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <iostream>
#include "CString.h"

int main(int argc, const char * argv[]) {
    char* asdf = "12";
    std::string asdf2 = "34";
    CString myAwesomeString(asdf);
    CString myAwesomeString2(asdf2);
    CString myAwesomeString3("1234");
    myAwesomeString += myAwesomeString2;
    if( myAwesomeString == myAwesomeString3 ) {
        std::cout<<myAwesomeString;
    }
    CString veryLongString;
    std::cout<<std::endl;
    for( int i = 0; i < 100; ++i ) {
        veryLongString += myAwesomeString3;
    }
    std::cout<<veryLongString;
    
    // Testing comparator:
    CString a("aaa");
    CString b("aaa");
    CString c("Aac");
    if( a < b ) {
        std::cout<<"\nYES\n";
    }
    if( a == b ) {
        std::cout<<"\nYES\n";
    }
    
    // Testing methods:
    CString stringForTest("Hello!");
    stringForTest.deleteWithIndexes(2, 3);
    std::cout<<stringForTest << std::endl;
    stringForTest.replaceAtIndex("12345asdf", 2);
    std::cout<<stringForTest << std::endl;
    stringForTest.insertSubstringAtIndex("|ASFD|", 2);
    std::cout<<stringForTest << std::endl;
    return 0;
}
