//
//  CCircle.h
//  MIPT_TASK_4_2_CShapes_Classes
//
//  Created by Александр Малышев on 14.02.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#ifndef __MIPT_TASK_4_2_CShapes_Classes__CCircle__
#define __MIPT_TASK_4_2_CShapes_Classes__CCircle__

#include "CShapes.h"
#include <cmath>

class CCircle : public CShape {
public:
    
    CCircle();
    CCircle(CPoint _center, __Coord__ _radius);
    
    virtual __Coord__ getArea();
    virtual bool isOnBoundary(CPoint point); //returns true if the point is on boundary
    virtual bool isInShape(CPoint point);
    virtual vectorOfPoints getIntersectionWithRange(CRange range);
    virtual vectorOfPoints getIntersectionWithLine(CRange range);

private:
    CPoint center; //center of the circle
    __Coord__ radius; //radius of the circle
};


#endif /* defined(__MIPT_TASK_4_2_CShapes_Classes__CCircle__) */
