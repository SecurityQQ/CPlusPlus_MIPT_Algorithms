//
//  CuteBot.hpp
//  ReversiBot
//
//  Created by Alexander Malyshev on 16.12.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

#ifndef CuteBot_hpp
#define CuteBot_hpp

#include "Constants.hpp"
#include <iostream>
#include <set>
#include <vector>

class Field {
public:
    Field();
    FieldCellOption at(int i, int j) { return _field[i][j]; }
    FieldCellOption at(FieldCoordinate coord) { return _field[coord.x][coord.y]; }
    void print();
    Score makeTurnAt(FieldCoordinate coord, FieldCellOption color);
private:
    std::vector<std::vector<FieldCellOption>> _field;
};


class CuteBot {
public:
    CuteBot() {}
    void play(std::istream& input, std::ostream& output);
    std::set<FieldCoordinate> possibleMoves(FieldCellOption color, Field &field);
    void sendMove(std::ostream& output, int x, int y);
    ~CuteBot() { }
private:

};

bool isInField(FieldCoordinate coord) {
    return 0 <= coord.x && coord.x <= 7 && 0 <= coord.y && coord.y <= 7;
}

void Field:: print() {
    std::cout<<std::endl;
    for (int i = 0; i < FIELD_SIZE; ++i) {
        for (int j = 0; j < FIELD_SIZE; ++j) {
            switch (_field[i][j]) {
                case black:
                    std::cout<<"B ";
                    break;
                case white:
                    std::cout<<"W ";
                    break;
                default:
                    std::cout<<"0 ";
                    break;
            }
        }
        std::cout<<std::endl;
    }
}

Score Field:: makeTurnAt(FieldCoordinate coord, FieldCellOption color) {
    assert(isInField(coord));
    assert(color == black || color == white);
    assert(at(coord) == empty);
    _field[coord.x][coord.y] = color;
    Score score = 0;
    std::vector<FieldCoordinate> directions = {{0, 1}, {0, -1}, {1, 0}, {1, 1}, {1, -1}, {-1, 0}, {-1, 1}, {-1, -1}};
    for (auto d: directions) {
        auto turn = coord + d;
        while (isInField(turn)) {
            if (at(turn) != oppositeColor(color)) {
                break;
            }
            while (isInField(turn) && at(turn) == oppositeColor(color)) {
                turn = turn + d;
            }
            if (isInField(turn) && at(turn) == color) {
                for (auto it = coord + d; it != turn; it = it + d) {
                    _field[it.x][it.y] = color;
                    ++score;
                }
            }
        }
    }
    return score;
}

void CuteBot:: play(std::istream& input, std::ostream& output) {
    FieldCellOption botColor;
    Field field;
    std::string foo;
    input>> foo;
    if (foo != "init") {
        return;
    }
    input>> foo;
    botColor = ((foo == "black") ? black : white);
    while (foo != "win" || foo != "lose") {
//        field.print();
        input>>foo;
        if (foo == "turn") {
            auto moves = possibleMoves(botColor, field);
            auto move = *moves.begin();
            sendMove(output, move.x, move.y);
            field.makeTurnAt(move, botColor);
        } else {
            if (foo == "move") {
                char x;
                int  y;
                input >> x >> y;
                field.makeTurnAt(FieldCoordinate(x - 'a', y - 1), oppositeColor(botColor));
            }
        }
    }
}

Field:: Field() {
    _field = std::vector<std::vector<FieldCellOption>>(FIELD_SIZE, std::vector<FieldCellOption>(FIELD_SIZE, empty));
    _field[3][3] = white;
    _field[4][4] = white;
    _field[3][4] = black;
    _field[4][3] = black;
}

void CuteBot:: sendMove(std::ostream& output, int x, int y) {
    assert(0 <= x && x <= 7 && 0 <= y && y <= 7);
    output<<"move "<< char('a' + x) <<" " << y + 1<<std::endl;
}

std::set<FieldCoordinate> CuteBot:: possibleMoves(FieldCellOption color, Field &field) {
    assert(color == black || color == white);
    std::set<FieldCoordinate> possibleTurns;
    std::vector<FieldCoordinate> directions = {{0, 1}, {0, -1}, {1, 0}, {1, 1}, {1, -1}, {-1, 0}, {-1, 1}, {-1, -1}};
    for (int i = 0; i < FIELD_SIZE; ++i) {
        for (int j = 0; j < FIELD_SIZE; ++j) {
            if (field.at(i, j) == color) {
                for (auto d : directions) {
                    auto turn = FieldCoordinate(i + d.x, j + d.y);
                    if (field.at(turn.x, turn.y) != oppositeColor(color)) {
                        continue;
                    }
                    while (0 <= turn.x && turn.x <= 7 && 0 <= turn.y && turn.y <= 7) {
                        if (field.at(turn.x, turn.y) == oppositeColor(color) ) {
                            turn.x += d.x;
                            turn.y += d.y;
                        } else {
                            if (0 <= turn.x && turn.x <= 7 && 0 <= turn.y && turn.y <= 7) {
                                if (field.at(turn.x, turn.y) == empty) {
                                    possibleTurns.insert(turn);
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    return possibleTurns;
}


#endif /* CuteBot_hpp */
