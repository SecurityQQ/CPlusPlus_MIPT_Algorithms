//
//  main.cpp
//  TEST
//
//  Created by Александр Малышев on 16.03.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <iostream>
#include <assert.h>
#include <vector>


int main(int argc, const char * argv[]) {
    std::vector<int> a;
    
    
    a.assign(5, 1);
    a.assign(2, 2);
    
    
    for( int i = 0; i < a.size(); ++i ) {
        std::cout<<a[i] << " ";
    }
    
    
    return 0;
}
