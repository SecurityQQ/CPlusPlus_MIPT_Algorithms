//
//  CPolygon.h
//  MIPT_TASK_4_2_CShapes_Classes
//
//  Created by Александр Малышев on 14.02.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#ifndef __MIPT_TASK_4_2_CShapes_Classes__CPolygon__
#define __MIPT_TASK_4_2_CShapes_Classes__CPolygon__

#include "CShapes.h"
#include <cmath>

class CPolygon: public CShape {
public:
    CPolygon();
    CPolygon(vectorOfPoints points);
    virtual __Coord__ getArea();
    virtual bool isOnBoundary(CPoint point); //returns true if the point is on boundary
    virtual bool isInShape(CPoint point);
    virtual vectorOfPoints getIntersectionWithRange(CRange range);
    
    std::vector<CPoint> getFrame() const;
    
protected:
    std::vector<CPoint> frame;
    CPoint getPointOutside();
};

#endif /* defined(__MIPT_TASK_4_2_CShapes_Classes__CPolygon__) */
