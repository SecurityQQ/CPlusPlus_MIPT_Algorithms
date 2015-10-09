//
//  CConvexPolygon.cpp
//  MIPT_TASK_4_2_CShapes_Classes
//
//  Created by Александр Малышев on 14.02.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include "CConvexPolygon.h"


CConvexPolygon::CConvexPolygon() {
    
}

CConvexPolygon::CConvexPolygon(vectorOfPoints points) {
    frame = points;
}