//
//  CConvexPolygon.h
//  MIPT_TASK_4_2_CShapes_Classes
//
//  Created by Александр Малышев on 14.02.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#ifndef __MIPT_TASK_4_2_CShapes_Classes__CConvexPolygon__
#define __MIPT_TASK_4_2_CShapes_Classes__CConvexPolygon__

#include "CPolygon.h"
class CConvexPolygon: public CPolygon {
public:
    CConvexPolygon();
    CConvexPolygon(vectorOfPoints points);
};

#endif /* defined(__MIPT_TASK_4_2_CShapes_Classes__CConvexPolygon__) */
