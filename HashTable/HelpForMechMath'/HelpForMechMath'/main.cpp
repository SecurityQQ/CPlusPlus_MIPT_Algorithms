//
//  main.cpp
//  HelpForMechMath'
//
//  Created by Александр Малышев on 22.12.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//

#include <iostream>

using namespace std;

struct pt {
    double x, y;
};

void compactPolygon( FILE* inputStream);

int main() {
    FILE *inputStream = fopen("ЗДЕСЬ ДОЛЖЕН БЫТЬ НЕПРЕВЗОЙДЕННЫЙ ПУТЬ К ФАЙЛУ", "r");
    if( inputStream == 0) {
        cout<< "File reading error (No such file)" <<endl;
        return -1;
    } else {
        compactPolygon(inputStream);
        fclose(inputStream);
    }
    return 0;
}




void compactPolygon( FILE* inputStream) {
    pt leftBottomPeak;
    pt rightTopPeak;
    pt foo;
    
    fscanf(inputStream, "%lf%lf", &foo.x, &foo.y);
    leftBottomPeak = foo;
    rightTopPeak = foo;
    
    while( fscanf(inputStream, "%lf%lf", &foo.x, &foo.y) == 2 ) {
        if( foo.x < leftBottomPeak.x ) {
            leftBottomPeak.x = foo.x;
        }
        if( foo.y < leftBottomPeak.y ) {
            leftBottomPeak.y = foo.y;
        }
        if( foo.x > rightTopPeak.x ) {
            rightTopPeak.x = foo.x;
        }
        if( foo.y > rightTopPeak.y ) {
            rightTopPeak.y = foo.y;
        }
    }
     cout<< "First Diag: " <<leftBottomPeak.x << " " <<leftBottomPeak.y << endl << "Second Diag: " <<rightTopPeak.x << " " <<rightTopPeak.y << endl;
}
