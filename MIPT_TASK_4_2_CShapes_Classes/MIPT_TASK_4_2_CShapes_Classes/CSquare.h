//
//  CSquare.h
//  MIPT_TASK_4_2_CShapes_Classes
//
//  Created by Александр Малышев on 14.02.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#ifndef __MIPT_TASK_4_2_CShapes_Classes__CSquare__
#define __MIPT_TASK_4_2_CShapes_Classes__CSquare__

#include "CPolygon.h"

class CSquare : public CPolygon {
public:
    CSquare();
    CSquare(CPoint startPoint, __Coord__ side);
private:
    __Coord__ side;
};

#endif /* defined(__MIPT_TASK_4_2_CShapes_Classes__CSquare__) */
