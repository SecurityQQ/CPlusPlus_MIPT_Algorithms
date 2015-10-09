//
//  CCircle.cpp
//  MIPT_TASK_4_2_CShapes_Classes
//
//  Created by Александр Малышев on 14.02.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include "CCircle.h"

#pragma mark - CCircle implementation
#pragma mark --;

CCircle::CCircle() {
    CPoint nullPoint(0, 0);
    center = nullPoint;
    radius = 0;
}

CCircle::CCircle(CPoint _center, __Coord__ _radius) {
    center = _center;
    radius = _radius;
}
__Coord__ CCircle::getArea() {
    return radius * radius * M_PI;
}

bool CCircle::isOnBoundary(CPoint point) {
    return ((center.x - point.x) * (center.x - point.x) + (center.y - point.y) * (center.y - point.y) == radius * radius);
}

bool CCircle::isInShape(CPoint point) {
    return ((center.x - point.x) * (center.x - point.x) + (center.y - point.y) * (center.y - point.y) <= radius * radius);
}

vectorOfPoints CCircle::getIntersectionWithRange(CRange range) {
    vectorOfPoints intersections = getIntersectionWithLine(range);
    vectorOfPoints rangeIntersections;
    for( int i = 0; i < intersections.size(); ++i ) {
        if (intersections[i].isOnRange(range)) {
            rangeIntersections.push_back(intersections[i]);
        }
    }
    return rangeIntersections;
}

vectorOfPoints CCircle::getIntersectionWithLine(CRange range) {
    vectorOfPoints intersections;

    if( range.coefX == 0) {
        //by +c = 0 => y = -c/b
        //solving math equality:
        __Coord__ A = 1;
        __Coord__ B = - 2 * center.x;
        __Coord__ C = center.x * center.x
        + ( -range.coefC / range.coefY )
        * ( -range.coefC / range.coefY )
        - 2 * ( -range.coefC / range.coefY )
        * center.y + center.y * center.y - radius * radius;
        
        __Coord__ D = B * B - 4 * A * C;
        
        if( D > 0 ) {
            __Coord__ x1 = (-B - sqrt(D) ) / (2 * A);
            __Coord__ x2 = (-B + sqrt(D) ) / (2 * A);
            intersections.push_back(CPoint(x1, -range.coefC /range.coefY ));
            intersections.push_back(CPoint(x2, -range.coefC /range.coefY ));
        } else {
            if( D == 0 ) {
                __Coord__ x1 = -B / (2 * A);
                intersections.push_back(CPoint(x1, -range.coefC /range.coefY ));
            } else {
                    return intersections; //returns empty vector
                }
        }
    } else {
        // ax + by + c = 0 => x = ( -by - c ) / a
        // x^2 -2xx0 +x0^2 +y^2 -2yy0 +y0^2 -R^2 = 0
        // y^2 ((b/a)^2 + 1) + y ( 2bc/a^2 +2x0 *b/a -2y0) +c^2/a^2 +2x0c/a +x0^2 + y0^2 - R^2
       
        
        //solving math equality:
        
        __Coord__ A = (1 + (range.coefY / range.coefX)
                       * (range.coefY / range.coefX));
        
        __Coord__ B = (2 * range.coefY * range.coefC / (range.coefX * range.coefX)
                       + 2 * center.x * range.coefY / range.coefX - 2 * center.y);
        
        __Coord__ C = (range.coefC / range.coefX)
        * (range.coefC / range.coefX) + 2 * center.x * range.coefC / range.coefX + center.x
        * center.x + center.y * center.y - radius * radius;
        
        __Coord__ D = B * B - 4 * A * C;
        
        if( D > 0 ) {
            __Coord__ y1 = (-B - sqrt(D) ) / (2 * A);
            __Coord__ y2 = (-B + sqrt(D) ) / (2 * A);
            intersections.push_back(CPoint(- (range.coefY * y1 + range.coefC ) / range.coefX, y1));
            intersections.push_back(CPoint(- (range.coefY * y2 + range.coefC ) / range.coefX, y2));
        } else {
            if( D == 0 ) {
                __Coord__ y1 = -B / (2 * A);
                intersections.push_back(CPoint(- (range.coefY * y1 + range.coefC ) / range.coefX, y1));
            } else {
                return intersections; //returns empty vector
            }
        }
    }
    
    return intersections;
}