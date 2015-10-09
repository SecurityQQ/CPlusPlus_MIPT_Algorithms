//
//  CSquare.cpp
//  MIPT_TASK_4_2_CShapes_Classes
//
//  Created by Александр Малышев on 14.02.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include "CSquare.h"

CSquare::CSquare() {
    
}

CSquare::CSquare(CPoint startPoint, __Coord__ initSide) {
    side = initSide;
    frame.push_back(startPoint);
    frame.push_back(CPoint(startPoint.x, startPoint.y + side));
    frame.push_back(CPoint(startPoint.x + side, startPoint.y + side));
    frame.push_back(CPoint(startPoint.x + side, startPoint.y));
}