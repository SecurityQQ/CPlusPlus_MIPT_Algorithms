//
//  ConvexHullCreator.h
//  ConvexHull
//
//  Created by Александр Малышев on 16.03.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#ifndef __ConvexHull__ConvexHullCreator__
#define __ConvexHull__ConvexHullCreator__

#include <stdio.h>
#include <iostream>
#include "CPolygon.h"
#include "CConvexPolygon.h"

typedef unsigned long long ull;

class ConvexHullCreator {
    
public:
    
    CConvexPolygon getConvexHull(vectorOfPoints points);
    CConvexPolygon getConvexHull(CPolygon polygon);
    CConvexPolygon getMinimumBoundingRectangle(CPolygon polygon);
};


#endif /* defined(__ConvexHull__ConvexHullCreator__) */
