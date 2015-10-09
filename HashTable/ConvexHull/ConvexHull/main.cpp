//
//  main.cpp
//  ConvexHull
//
//  Created by Александр Малышев on 16.03.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <iostream>
#include "ConvexHullCreator.h"

int main(int argc, const char * argv[]) {

    std::vector<CPoint> points;
    CPoint foo;
    
    while( scanf("%lf%lf", &foo.x, &foo.y) == 2 ) {
        points.push_back(foo);
    }


//    for( int i = 0; i < 10; ++i ) {
//        points.push_back({static_cast<__Coord__>(rand() % 15), static_cast<__Coord__>(rand() % 15)});
//    }
//    
//    for( int i = 0; i < points.size(); ++i ) {
//        std::cout<<points[i].x << " "<< points[i].y <<std::endl;
//    }

    CPolygon polygon(points);
    
    ConvexHullCreator creator;
//    creator.getConvexHull(polygon);
    creator.getMinimumBoundingRectangle(polygon);
    
//    CRange a(CPoint(0, 0), CPoint(1, 0));
//    CRange b(CPoint(0, 0), CPoint(1, 0));
//    std::cout<<acos(getAngle(a, b));

    
    return 0;
}
