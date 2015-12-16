//
//  Constants.hpp
//  ReversiBot
//
//  Created by Alexander Malyshev on 16.12.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef Constants_h
#define Constants_h
#include <assert.h>
#define FIELD_SIZE 8


struct FieldCoordinate {
public:
    FieldCoordinate(int x, int y): x(x), y(y) {};
    int x;
    int y;
    bool operator < (const FieldCoordinate &rhs) const;
    bool operator == (const FieldCoordinate &rhs) const { return x == rhs.x && y == rhs.y; }
    bool operator != (const FieldCoordinate &rhs) const { return !operator==(rhs); }
    friend FieldCoordinate operator + (const FieldCoordinate &lhs, const FieldCoordinate &rhs);
};

bool FieldCoordinate:: operator < (const FieldCoordinate &rhs) const {
    return x < rhs.x ? true : y < rhs.y ? true : false;
}

FieldCoordinate operator + (const FieldCoordinate &lhs, const FieldCoordinate &rhs) {
    return FieldCoordinate(lhs.x + rhs.x, lhs.y + rhs.y);
}

typedef int Score;

enum FieldCellOption {
    white = 0,
    black = 1,
    empty = -1,
};

FieldCellOption oppositeColor(FieldCellOption color) {
    assert(color == white || color == black);
    return color == white ? black : white;
}

#endif /* Constants_h */
