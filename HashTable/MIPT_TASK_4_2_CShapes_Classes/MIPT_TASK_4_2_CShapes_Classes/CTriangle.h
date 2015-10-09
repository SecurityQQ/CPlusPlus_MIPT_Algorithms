//
//  CTriangle.h
//  MIPT_TASK_4_2_CShapes_Classes
//
//  Created by Александр Малышев on 14.02.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#ifndef __MIPT_TASK_4_2_CShapes_Classes__CTriangle__
#define __MIPT_TASK_4_2_CShapes_Classes__CTriangle__

#include "CPolygon.h"

class CTriangle: public CPolygon {
public:
    CTriangle();
    CTriangle(CPoint &firstVertex, CPoint &secondVertex, CPoint &thirdVertex);
};
#endif /* defined(__MIPT_TASK_4_2_CShapes_Classes__CTriangle__) */
