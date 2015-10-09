//
//  CRectangle.h
//  MIPT_TASK_4_2_CShapes_Classes
//
//  Created by Александр Малышев on 14.02.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#ifndef __MIPT_TASK_4_2_CShapes_Classes__CRectangle__
#define __MIPT_TASK_4_2_CShapes_Classes__CRectangle__

#include "CPolygon.h"

class CRectangle: public CPolygon {
public:
    CRectangle();
    CRectangle(CPoint p1, CPoint p2);
};

#endif /* defined(__MIPT_TASK_4_2_CShapes_Classes__CRectangle__) */
