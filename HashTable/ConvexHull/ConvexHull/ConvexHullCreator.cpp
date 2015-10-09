//
//  ConvexHullCreator.cpp
//  ConvexHull
//
//  Created by Александр Малышев on 16.03.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include "ConvexHullCreator.h"
#include <stack>

#define inc(it) if( it != (frame.end() - 1) ) {\
++it;\
} else {\
it = frame.begin();\
}

CPoint comparisonPoint;

template <class T>
void cycleSwap(T& el1, T&el2, T& el3, T& el4, char dir) {
    if( dir == 'R') {
        T temp = el1;
        el1 = el2;
        el2 = el3;
        el3 = el4;
        el4 = temp;
        return;
    }
    if( dir == 'L' ) {
        T temp = el4;
        el4 = el3;
        el3 = el2;
        el2 = el1;
        el1 = temp;
    }
}

bool compareRanges( CRange range, CRange range2) {
    
    printf("Comparting: (%f; %f) and (%f; %f) RESULT: ", range.end.x, range.end.y, range2.end.x, range2.end.y);
    
    if( range.isVertical ) {
        if( range2.isVertical ) {
            printf("%d\n", range.end.y < range2.end.y);
            return range.end.y < range2.end.y;
        }
        if( range.end.y > range.start.y ) {
            printf("0\n");
            return 0;
        }
        printf("1\n");
        return 1;
    }
    if( range2.isVertical ) {
        if( range2.end.y > range2.start.y ) {
            printf("1\n");
            return 1;
        }
        printf("0\n");
        return 0;
    }
    printf("%d\n", range.coefK < range2.coefK);
    return range.coefK < range2.coefK;

}

bool comparePoints( CPoint &point, CPoint &point2) {
    if( point.x == comparisonPoint.x && point.y == comparisonPoint.y ) {
        return 1;
    }
    if( point2.x == comparisonPoint.x && point2.y == comparisonPoint.y ) {
        return 0;
    }

    
    return compareRanges(CRange(comparisonPoint, point), CRange(comparisonPoint, point2));
}


CConvexPolygon ConvexHullCreator:: getConvexHull(vectorOfPoints points) {
    return getConvexHull(CPolygon(points));
}

CConvexPolygon ConvexHullCreator:: getConvexHull(CPolygon polygon) {
    std::vector<CPoint> frame = polygon.getFrame();
    std::vector<CPoint> convexHull;
    comparisonPoint = frame[0];
    
    for( std::vector<CPoint>::iterator it = frame.begin(); it != frame.end(); ++it ) {
        if( comparisonPoint.x > it->x ) {
            comparisonPoint = *it;
        }
    }

    std::sort(frame.begin(), frame.end(), comparePoints);
    
    convexHull.push_back(frame[0]);
    convexHull.push_back(frame[1]);
    
    std::vector<CPoint>::iterator it = frame.begin() + 2;
    
    while( it != frame.end() ) {
        
        printf("%f %f\n", (convexHull.end()-1)->x, (convexHull.end()-1)->y);
        __Coord__ area = 0;
        do {
            __Coord__ a = (it->x - (convexHull.end() - 1)->x);
            __Coord__ b = (it->y - (convexHull.end() - 2)->y);
            __Coord__ c = (it->x - (convexHull.end() - 2)->x);
            __Coord__ d = (it->y - (convexHull.end() - 1)->y);
            area = a * b - c * d;
            if( area >= 0 ) {
                convexHull.pop_back();
            }
        } while( area >= 0);
        convexHull.push_back(*it);
        ++it;
    }
    
    
    
    
    
    
    
    
    
    
    
///debug
    std::cout<<"Convex HULL: \n";
    for( std::vector<CPoint>::iterator it = convexHull.begin(); it != convexHull.end(); ++it ) {
        std::cout<< it->x <<" "<< it->y << std::endl;
    }
    CConvexPolygon hull(convexHull);
    return hull;
}


CConvexPolygon ConvexHullCreator::getMinimumBoundingRectangle(CPolygon polygon) {
    std::vector<CPoint> frame = getConvexHull(polygon).getFrame();
    

    std::vector<CPoint>::iterator minAreaLeftPoint, minAreaRightPoint, minAreaTopPoint, minAreaBotPoint;
    double minArea = ULLONG_MAX;
    
    double angleR = 0; //MAX angle between firstEdge and edge which was created by rightpoint
    double angleL = 0; //MIN angle between firstEdge and edge which was created by leftpoint
    
    __Coord__ maxDiam = 0;
    
    
    
    
    std::vector<CPoint>::iterator botPoint = frame.begin();
    
    
    std::vector<CPoint>::iterator it = botPoint;
    std::vector<CPoint>::iterator cycleEnd = botPoint;
    std::vector<CPoint>::iterator leftPoint, rightPoint, topPoint;
    topPoint = it;
    leftPoint = it;
    inc(it);
    rightPoint = it;
    CRange firstEdge(*leftPoint, *rightPoint);
    std::vector<CPoint>::iterator prevIt = it;
    inc(it);
    inc(botPoint);
    do {
        
        __Coord__ tempDiam = fabsl(( firstEdge.coefX * it->x + firstEdge.coefY * it->y + firstEdge.coefC));
        double tempAngle = getAngle(firstEdge, CRange(*prevIt, *it));
        
        if( tempDiam >= maxDiam ) {
            maxDiam = tempDiam;
            topPoint = it;
            if( 0 <= tempAngle ) {
                rightPoint = it;
                angleR = tempAngle;
            }
        } else {
            if( 0 <= tempAngle ) {
                leftPoint = it;
                angleL = tempAngle;
            }
        }
        
    prevIt = it;
    inc(it);
        
    } while( it != cycleEnd );

    for( ull edgesChecked = 0; edgesChecked < frame.size(); ++edgesChecked ) {
        std::cout<<*botPoint <<" "<< *rightPoint<<" "<< *topPoint <<" "<<*leftPoint<<std::endl;
        
        double area = fabsl((firstEdge.coefY * (leftPoint->x - rightPoint->x) - firstEdge.coefX*(leftPoint->y - rightPoint->y)) * maxDiam);
        
        if( minArea >= area ) {
            minAreaLeftPoint = leftPoint;
            minAreaRightPoint = rightPoint;
            minAreaTopPoint = topPoint;
            minAreaBotPoint = botPoint;
        }
        std::vector<CPoint>::iterator nextIt = leftPoint;
        inc(nextIt);
        double leftAngle = fabsl(M_PI_2 - fabsl(acosl(getAngle( firstEdge, CRange(*leftPoint, *nextIt)))));
        nextIt = rightPoint;
        inc(nextIt);
        double rightAngle = fabsl(M_PI_2 - fabsl(acosl(getAngle( firstEdge, CRange(*rightPoint, *nextIt)))));
        nextIt = topPoint;
        inc(nextIt);
        double topAngle = M_PI - fabsl(acosl(getAngle( firstEdge, CRange(*topPoint, *nextIt))));
        
        nextIt = botPoint;
        inc(nextIt);
        double botAngle = fabsl(acosl(getAngle(firstEdge, CRange(*botPoint, *nextIt))));

        if( leftAngle <= rightAngle && leftAngle <= topAngle && leftAngle <= botAngle ) {
            nextIt = leftPoint;
            inc(nextIt);
            firstEdge = CRange(*leftPoint, *nextIt);
            cycleSwap(botPoint, rightPoint, topPoint, leftPoint, 'L');
            botPoint = nextIt;
            continue;
        }
        if( rightAngle <= leftAngle && rightAngle <= topAngle && rightAngle <= botAngle ) {
            nextIt = rightPoint;
            inc(nextIt);
            firstEdge = CRange(*rightPoint, *nextIt);
            cycleSwap(botPoint, rightPoint, topPoint, leftPoint, 'R');
            botPoint = nextIt;
            continue;
        }
        if( topAngle <= rightAngle && topAngle <= leftAngle && topAngle <= botAngle ) {
            nextIt = topPoint;
            inc(nextIt);
            firstEdge = CRange(*topPoint, *nextIt);
            std::swap(leftPoint, rightPoint);
            std::swap(botPoint, topPoint);
            botPoint = nextIt;
            continue;
        }
        nextIt = botPoint;
        inc(nextIt);
        firstEdge = CRange(*botPoint, *nextIt);
        botPoint = nextIt;
    }
    
    
    std::vector<CPoint> mbrFrame;
    if( minAreaBotPoint != frame.begin() ) {
        firstEdge = CRange(*(minAreaBotPoint - 1), *minAreaBotPoint);
    } else {
        firstEdge = CRange(*(frame.end() - 1), *minAreaBotPoint);
    }
    
    __Coord__ x, y;
    
    //ax + by + c = 0
    //-bx +ay +b * x0 - a * y0 = 0
    std::vector<CPoint> minPoints;
    
    minPoints.push_back(*minAreaRightPoint);
    minPoints.push_back(*minAreaTopPoint);
    minPoints.push_back(*minAreaLeftPoint);
    
    
    for( int i = 0; i < minPoints.size(); ++i ) {
        __Coord__ a = firstEdge.coefX;
        __Coord__ b = firstEdge.coefY;
        __Coord__ c = firstEdge.coefC;
        
        __Coord__ p = minPoints[i].x;
        __Coord__ q = minPoints[i].y;
        
        x = (b * b * p - a * b * q - a * c) / (a * a + b * b);
        y = (a * a * q - a * b * p - b * c) / (a * a + b * b);
        
        if( minPoints[i] == CPoint(x, y) ) {
            __Coord__ x0, y0;
            if( a != 0 ) {
                x0 = rand() % 20;
                y0 = -(b * x - a * y - b * x0) / a;
            } else {
                assert( b == 0 );
                x0 = (b * x - a * y) / b;
                y0 = rand() % 20;
            }
            firstEdge = CRange( CPoint(x, y), CPoint(x0, y0) );
            
        } else {
            firstEdge = CRange( CPoint(x, y), minPoints[i]);
        }
            mbrFrame.push_back(CPoint(x, y));
    }
    
    
    
    
    
//    std::cout<< rightPoint->x << ";" <<rightPoint->y <<" && "<<leftPoint->x <<";" << leftPoint->y << " && "<<topPoint->x << ";" << topPoint->y <<std::endl;
//    
//
    for( int i = 0; i < mbrFrame.size(); ++i ) {
        std::cout<<mbrFrame[i] << " ";
    }
    
    CConvexPolygon minBoundingRectangle(mbrFrame);
    return minBoundingRectangle;
}