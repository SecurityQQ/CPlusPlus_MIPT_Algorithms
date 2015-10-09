//
//  CShapes.h
//  MIPT_TASK_4_2_CShapes_Classes
//
//  Created by Александр Малышев on 13.02.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#ifndef __MIPT_TASK_4_2_CShapes_Classes__CShapes__
#define __MIPT_TASK_4_2_CShapes_Classes__CShapes__

//includes:
#include <iostream>
#include "CRange.h"
#include <vector>

//typedefs:
typedef std::vector<CPoint> vectorOfPoints;

#pragma mark - CShape interface
#pragma mark --

class CShape {
public:
    virtual __Coord__ getArea() = 0;
    virtual bool isOnBoundary(CPoint point) = 0; //returns true if the point is on boundary
    virtual bool isInShape(CPoint point) = 0;
    virtual vectorOfPoints getIntersectionWithRange(CRange range) = 0;
};








#endif /* defined(__MIPT_TASK_4_2_CShapes_Classes__CShapes__) */
