//
//  main.cpp
//  MIPT_TASK_4_2_CShapes_Classes
//
//  Created by Александр Малышев on 13.02.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <iostream>
#include "CCircle.h"
#include "CPolygon.h"

int main(int argc, const char * argv[]) {
//    CCircle circle(CPoint(1, 1), 1);
//    CRange range(CPoint(0, 1), CPoint(2, 1));
//    vectorOfPoints vec = circle.getIntersectionWithLine(range);
//    bool isInShape = circle.isInShape(CPoint(5, 1));
//    
//    
//    CRange crossingRange1(CPoint(-2, 3), CPoint(1, 0));
//    CRange crossingRange2(CPoint(-2, 0), CPoint(0, 2));
//    CPoint* intersec = crossingRange1.getIntersectionWithRange(crossingRange2);
//    
    vectorOfPoints pol;
    pol.push_back(CPoint(1, 1));
    pol.push_back(CPoint(3, 3));
    pol.push_back(CPoint(6, 1));
    pol.push_back(CPoint(3, -1));
    pol.push_back(CPoint(3, 1));
    
    CPolygon myPolygon(pol);
//    CRange rrr(CPoint(2, 2), CPoint(5, -1));
//    vectorOfPoints vec2 = myPolygon.getIntersectionWithRange(rrr);
    bool isInPolygon = myPolygon.isInShape(CPoint(4, 1));

    return 0;
}
