//
//  CTriangle.cpp
//  MIPT_TASK_4_2_CShapes_Classes
//
//  Created by Александр Малышев on 14.02.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include "CTriangle.h"

CTriangle::CTriangle() {
    
}

CTriangle::CTriangle(CPoint &firstVertex, CPoint &secondVertex, CPoint &thirdVertex) {
    frame.push_back(firstVertex);
    frame.push_back(secondVertex);
    frame.push_back(thirdVertex);
}