//
//  CRange.h
//  MIPT_TASK_4_2_CShapes_Classes
//
//  Created by Александр Малышев on 14.02.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#ifndef __MIPT_TASK_4_2_CShapes_Classes__CRange__
#define __MIPT_TASK_4_2_CShapes_Classes__CRange__

#include <stdio.h>
#include <iostream>
#include <assert.h>

typedef double __Coord__;

class CRange;

class CPoint {
public:
    CPoint() {
        x = 0;
        y = 0;
    }
    
    CPoint(__Coord__ _x, __Coord__ _y) {
        x = _x;
        y = _y;
    }
    
    __Coord__ x;
    __Coord__ y;
    
    bool isOnRange(CRange &range);

    CPoint operator= (CPoint point) {
        x = point.x;
        y = point.y;
        
        return *this;
    }
    
    bool operator== (CPoint point) {
        return (x == point.x) && (y == point.y);
    }
    
    bool operator!= (CPoint point) {
        
        return ((x != point.x) || (y != point.y));
    }
    friend std::ostream& operator<< (std::ostream& stream, CPoint point);
};

class CRange {
public:
    CRange(CPoint p, CPoint p2);
    CRange(CPoint p, __Coord__ _coefK);
    //for ax + by + c = 0
    __Coord__ coefX;
    __Coord__ coefY;
    __Coord__ coefC;
    
    //For y = kx + b
    __Coord__ coefK;
    __Coord__ coefB;
    
    CPoint start;
    CPoint end;
    
    bool isPointOnLine(CPoint &point);
    bool isVertical;
    CPoint* getIntersectionWithRange(CRange &line);
    
    
    friend double getAngle(CRange range1, CRange range2);
private:
    void getCoefs(CPoint& p, CPoint& p2);  //ax + by + c = 0 coefX = a, coefY = b, coefC = c;
};


#endif /* defined(__MIPT_TASK_4_2_CShapes_Classes__CRange__) */
