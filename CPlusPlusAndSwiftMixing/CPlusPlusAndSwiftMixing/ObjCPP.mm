//
//  ObjCPP.m
//  CPlusPlusAndSwiftMixing
//
//  Created by Alexander Malyshev on 16.10.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#import "ObjCPP.h"

#include <iostream>

@implementation ObjCPP

- (void) hello {
    std::cout<<"Hello!!!"<<std::endl;
}
@end
