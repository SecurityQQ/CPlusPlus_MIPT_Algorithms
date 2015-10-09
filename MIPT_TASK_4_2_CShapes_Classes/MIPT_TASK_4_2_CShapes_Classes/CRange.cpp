//
//  CRange.cpp
//  MIPT_TASK_4_2_CShapes_Classes
//
//  Created by Александр Малышев on 14.02.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include "CRange.h"
#include <cmath>

#pragma mark - CPoint implementation
#pragma mark --

bool CPoint::isOnRange(CRange &range) {
    
    return (range.coefX * x + range.coefY * y + range.coefC == 0)
    && (std::min(range.start.x, range.end.x) <= x)
    && (x <= std::max(range.start.x, range.end.x))
    && (std::min(range.start.y, range.end.y) <= y)
    && (y <= std::max(range.start.y, range.end.y));
}

std::ostream& operator<< (std::ostream& stream, CPoint point) {
    stream<<point.x<<";"<<point.y;
    return stream;
}

#pragma mark - CRange implementation
#pragma mark --

CRange::CRange(CPoint p, CPoint p2) {
    start = p;
    end = p2;
    getCoefs(p, p2);
}
CRange::CRange(CPoint p, __Coord__ _coefK) {
    //kx + b = y;
    CPoint p2(p.x + 1, _coefK * (p.x + 1) );
    start = p;
    end = p2;
    getCoefs(p, p2);
}
void CRange::getCoefs(CPoint& p, CPoint& p2) {
    assert(p != p2);
    isVertical = false;
    //ax + by + c = 0 coefX = a, coefY = b, coefC = c;
    if( p.x == p2.x ) {
        coefX = 1;
        coefY = (p.x - p2.x) / (p2.y - p.y);
        coefC = -coefX * p.x - coefY * p.y;
    } else {
        coefX = (p.y - p2.y) / (p2.x - p.x);
        coefY = 1;
        coefC = -coefX * p.x - coefY * p.y;
    }
    if( coefY != 0) {
        coefK = - coefX / coefY;
        coefB = - coefC / coefY;
    } else {
        isVertical = true;
    }
}

bool CRange::isPointOnLine(CPoint &point) {
    return coefX * point.x + coefY * point.y + coefC == 0;
}


//<# better to do enum#>
CPoint* CRange::getIntersectionWithRange(CRange &range) {
//    ax + by + c = 0
//    a2 x + b2 y + c2 = 0
    __Coord__ x;
    __Coord__ y;
    
    if( coefX == 0 ) {
        //y = -c/b
        if( range.coefX == 0 ) {
            return NULL; //they are equal
        } else {
            x = -range.coefC + coefC * range.coefY / coefY;
            y = -coefC / coefY;
        }
    } else {
         __Coord__ det = (coefY * range.coefX - coefX * range.coefY);
         if( det == 0 ) {
             if (coefC == 0) {
                 return NULL; //their intersection is an empty set
             } else {
                 if( range.coefX / coefX == range.coefC / coefC) {
                     return NULL; //they are equal
                 }
             }
         } else {
                x = -(range.coefC * coefY - coefC * range.coefY) / (coefY * range.coefX - coefX * range.coefY);
                y = (range.coefC * coefX - coefC * range.coefX) / (coefY * range.coefX - coefX * range.coefY);
         }
    }
    CPoint point(x, y);
    if( point.isOnRange(*this) && point.isOnRange(range) ) {
        return new CPoint(x, y);
    } else {
        return NULL;
    }
}

double getAngle(CRange range1, CRange range2) {
    double scalProduct = (range1.end.x - range1.start.x) * (range2.end.x - range2.start.x) +
    (range1.end.y - range1.start.y) * (range2.end.y - range2.start.y);
    
    double lengths =( sqrt((range1.end.x - range1.start.x) * (range1.end.x - range1.start.x) + (range1.end.y - range1.start.y) * (range1.end.y - range1.start.y) ) *
               sqrt((range2.end.x - range2.start.x) * (range2.end.x - range2.start.x) + (range2.end.y - range2.start.y) * (range2.end.y - range2.start.y)));
    double cos = scalProduct / lengths;
    if( cos > 1 ) {
        return 1;
    }
    if( cos < -1 ) {
        return -1;
    }
    
    return cos;

}
