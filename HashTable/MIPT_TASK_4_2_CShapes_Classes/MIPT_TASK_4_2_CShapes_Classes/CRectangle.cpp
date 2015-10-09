//
//  CRectangle.cpp
//  MIPT_TASK_4_2_CShapes_Classes
//
//  Created by Александр Малышев on 14.02.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include "CRectangle.h"


CRectangle::CRectangle() {
    
}

CRectangle::CRectangle(CPoint p1, CPoint p2) {
    frame.push_back(CPoint(p1.x, p1.y));
    frame.push_back(CPoint(p1.x, p2.y));
    frame.push_back(CPoint(p2.x, p2.y));
    frame.push_back(CPoint(p2.x, p1.y));
}