//
//  CPolygon.cpp
//  MIPT_TASK_4_2_CShapes_Classes
//
//  Created by Александр Малышев on 14.02.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include "CPolygon.h"
#include "CTriangle.h"
#include "CCircle.h"

CPolygon::CPolygon() {
    
}

CPolygon::CPolygon(vectorOfPoints points) {
    frame = points;
}

__Coord__ CPolygon::getArea() {
    __Coord__ area = 0;
    for( int i = 0; i < frame.size() - 1; ++i ) {
        area += (1 / 2 ) * (frame[i].x * frame[i + 1].y - frame[i + 1].x * frame[i].y);
    }
    return area > 0 ? area : -area;
}

bool CPolygon::isOnBoundary(CPoint point) {
    for( int i = 0; i < frame.size() - 1; ++i ) {
        CRange side(frame[i], frame[i + 1]);
        if( point.isOnRange(side) ) {
            return true;
        };
    }
    CRange side(frame[frame.size()], frame[0]);
    return point.isOnRange(side);
}

bool CPolygon::isInShape(CPoint point) {
    CPoint outsidePoint = getPointOutside();
    CRange rangeBetweenPointAndOutsidePoint(point, outsidePoint);
    vectorOfPoints a =  getIntersectionWithRange(rangeBetweenPointAndOutsidePoint);
    return getIntersectionWithRange(rangeBetweenPointAndOutsidePoint).size() % 2;
}

vectorOfPoints CPolygon::getIntersectionWithRange(CRange range) {
    vectorOfPoints intersection;
    for( int i = 0; i < frame.size() - 1; ++i ) {
        CRange side(frame[i], frame[i + 1]);
        CPoint* temp = side.getIntersectionWithRange(range);
        if( temp != NULL ) {
            bool isUnical = true;
            for( int i = 0; i < intersection.size(); ++i ) {
                if( intersection[i] == temp[0]) {
                    isUnical = false;
                }
            }
            if( isUnical ) {
                intersection.push_back(temp[0]);
            }
        }
    }
    
    return intersection;
}


CPoint CPolygon::getPointOutside() {
    __Coord__ maxDistance = 0; // radius of the ballon which contains all polygon's points
    std::vector<__Coord__> coefs;
    for( int i = 1; i < frame.size(); ++i ) {
        __Coord__ dist = sqrt(( frame[i].x - frame[0].x ) * ( frame[i].x - frame[0].x ) + ( frame[i].y - frame[0].y ) * ( frame[i].y - frame[0].y ));
        if( dist > maxDistance ) {
            maxDistance = dist;
        }
    }
    
    maxDistance += 1;
    CCircle bubble(CPoint(frame[0].x, frame[0].y), maxDistance);
    
    for( int i = 0; i < frame.size() - 1; ++i ) {
        CRange tempRange(frame[i], frame[i+1]);
        coefs.push_back(tempRange.coefK);
    }
    CRange tempRange(frame[0], frame[frame.size()]);
    coefs.push_back(tempRange.coefK);
    
    srand((unsigned int)time(NULL));
    
    bool isCoefUnical = true;
    double generatedLineCoef = random() % 100000000 / 1000000.0f;
    do {
        for( int i = 0 ; i < coefs.size(); ++i ) {
            if( generatedLineCoef == coefs[i] ) {
                isCoefUnical = false;
                generatedLineCoef = random() % 100000000 / 1000000.0f;
                break;
            }
        }
    } while( !isCoefUnical );
    CRange generatedRange(frame[0], generatedLineCoef);
    CPoint outsidePoint = bubble.getIntersectionWithLine(generatedRange)[0];
    return outsidePoint;
}



std::vector<CPoint> CPolygon::getFrame() const {
    return frame;
}