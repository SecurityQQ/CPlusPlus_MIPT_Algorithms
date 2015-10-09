//
//  FifteenGameSolver_v2.h
//  Fifteen solver
//
//  Created by Александр Малышев on 24.05.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#ifndef Fifteen_solver_FifteenGameSolver_v2_h
#define Fifteen_solver_FifteenGameSolver_v2_h

#include <vector>
#include <cmath>


#define MOVE_FAIL (-1)
#define MOVE_OK 0
#define FOUND (-1024)
#define NOT_FOUND (-512)
#define INF UINT32_MAX

typedef unsigned int uint;

enum Motion {
    keyUp    = 'U',
    keyLeft  = 'L',
    keyDown  = 'D',
    keyRight = 'R'
};

Motion reverseMotion(const Motion motion) {
    switch (motion) {
        case 'U':
            return keyDown;
            break;
        case 'L':
            return keyRight;
            break;
        case 'D':
            return keyUp;
            break;
        case 'R':
            return keyLeft;
            break;
    }
}

class FifteenGame {
public:
    
    FifteenGame();
    FifteenGame(short boardSize);
    ~FifteenGame();
    
    FifteenGame defaultBoard();
    FifteenGame newGame();
    
    void printBoard();
    
    int move(const Motion motion);
    void moveWithArrayOfMotions(const std::vector<Motion> motions);
    
    friend bool operator== (const FifteenGame &g1, const FifteenGame &g2);
    friend bool operator!= (const FifteenGame &g1, const FifteenGame &g2);
    
    std::vector<Motion> solve();
private:
    const short DefaultBoardSize = 4;
    std::pair<short, short> nullPosition;
    unsigned int getEuristic();
    std::vector<std::vector<uint>> board;
    uint depthFirstSearch(FifteenGame curState, uint curCost, uint curCostBound, std::vector<Motion> path);
    std::vector<Motion> getSuccessorsDir();
};


FifteenGame:: FifteenGame() {
    board.assign(DefaultBoardSize, std::vector<uint>(DefaultBoardSize, 0));
}

FifteenGame:: FifteenGame(short boardSize) {
    board.assign(boardSize, std::vector<uint>(boardSize, 0));
}

FifteenGame:: ~FifteenGame() {
    
}

FifteenGame FifteenGame:: defaultBoard() {
    FifteenGame defaultGame(board.size());
    for (short i = 1; i < board.size() * board.size(); ++i) {
        defaultGame.board[(i - 1) / board.size()][(i - 1) % board.size()] = i;
    }
    defaultGame.nullPosition = std::make_pair(board.size() - 1, board.size() - 1);
    return defaultGame;
}

void FifteenGame:: printBoard() {
    short maxDigit = (short)log10(board.size() * board.size()) + 1;
    for (auto i = board.begin(); i != board.end(); ++i) {
        for (auto j = i->begin(); j != i->end(); ++j) {
            if (*j == 0) {
                std::cout<<"_";
            } else {
                std::cout<<*j;
            }
            for (int i = 0; i < (maxDigit - (short)log10(*j)); ++i) {
                std::cout<<" ";
            }
        }
        std::cout<<std::endl;
    }
}

int FifteenGame:: move(const Motion motion) {
    switch (motion) {
        case 'U':
            if (nullPosition.first == 0) {
                return MOVE_FAIL;
            }
            std::swap(board[nullPosition.first][nullPosition.second], board[nullPosition.first - 1][nullPosition.second]);
            nullPosition.first--;
            break;
        case 'L':
            if (nullPosition.second == 0) {
                return MOVE_FAIL;
            }
            std::swap(board[nullPosition.first][nullPosition.second], board[nullPosition.first][nullPosition.second - 1]);
            nullPosition.second--;
            break;
        case 'D':
            if (nullPosition.first == (board.size() - 1)) {
                return MOVE_FAIL;
            }
            std::swap(board[nullPosition.first][nullPosition.second], board[nullPosition.first + 1][nullPosition.second]);
            nullPosition.first++;
            break;
        case 'R':
            if (nullPosition.second == (board.size() - 1)) {
                return MOVE_FAIL;
            }
            std::swap(board[nullPosition.first][nullPosition.second], board[nullPosition.first][nullPosition.second + 1]);
            nullPosition.second++;
            break;
            
        default:
            //TODO: exeption
            break;
    }
    return MOVE_OK;
}

void FifteenGame:: moveWithArrayOfMotions(const std::vector<Motion> motions) {
    for (auto i = motions.begin(); i != motions.end(); ++i) {
        move(*i);
    }
}

FifteenGame FifteenGame:: newGame() {
    
    FifteenGame newGame = defaultBoard();
//    srand(time(NULL));
    for (int i = 0; i < 7 * board.size() * board.size(); ++i) {
        switch (rand() % 4) {
            case 0:
                newGame.move(keyUp);
                break;
            case 1:
                newGame.move(keyLeft);
                break;
            case 2:
                newGame.move(keyDown);
                break;
            case 3:
                newGame.move(keyRight);
                break;
        }
    }
    return newGame;
}

unsigned int FifteenGame:: getEuristic() {
    unsigned int euristic = 0;
    for (short i = 0; i < board.size(); ++i) {
        for (short j = 0; j < board.size(); ++j) {
            if (board[i][j] == 0) {
                euristic += abs(i - (short)board.size() + 1) + abs(j - (short)board.size() + 1);
            } else {
                int iMan = abs(((short)i - (short)(board[i][j] - 1) / (short)board.size()));
                int jMan = abs(j - (short)(board[i][j] - 1) % (short)board.size());
                euristic += (iMan + jMan);
            }
        }
    }
    
    return euristic;
}



bool operator== (const FifteenGame &g1, const FifteenGame &g2) {
    if (g1.board.size() != g2.board.size()) { return false; }
    if (g1.nullPosition != g2.nullPosition) { return false; }
    for (short i = 0; i < g1.board.size(); ++i) {
        for (short j = 0; j < g1.board.size(); ++j) {
            if (g1.board[i][j] != g2.board[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool operator!= (const FifteenGame &g1, const FifteenGame &g2) {
    return !operator==(g1, g2);
}

std::vector<Motion> FifteenGame:: getSuccessorsDir() {
    std::vector<Motion> successors;
    FifteenGame aSuccessor = *this;
    aSuccessor.move(keyLeft);
    if (aSuccessor != *this) {
        successors.push_back(keyLeft);
        aSuccessor.move(keyRight);
    }
    aSuccessor.move(keyRight);
    if (aSuccessor != *this) {
        successors.push_back(keyRight);
        aSuccessor.move(keyLeft);
    }
    aSuccessor.move(keyUp);
    if (aSuccessor != *this) {
        successors.push_back(keyUp);
        aSuccessor.move(keyDown);
    }
    aSuccessor.move(keyDown);
    if (aSuccessor != *this) {
        successors.push_back(keyDown);
        aSuccessor.move(keyUp);
    }
    return successors;
}

int a = 0;


std::vector<Motion> ans;

std::vector<Motion> FifteenGame:: solve() {
    
    uint nextCostBound = getEuristic();
    uint solution;
    std::vector<Motion> path;
    while (solution != FOUND) {
        path.erase(path.begin(), path.end());
        uint currentCostBound = nextCostBound;
        solution = depthFirstSearch(*this, 0, currentCostBound, path);
        nextCostBound += 2;
    }
    
    return ans;
}

uint b = 0;
uint FifteenGame:: depthFirstSearch(FifteenGame curState, uint curCost, uint curCostBound, std::vector<Motion> path) {
    uint h = curState.getEuristic();
    ++b;
//    std::cout<<"-new search(" <<b <<")-\n";
//    std::cout<<"Current cost: " <<curCost <<" Current bound: "<<curCostBound<<"Euristic: "<<h<<std::endl;
//    curState.printBoard();
    
    
    if (h == 0) {
        ans = path;
        return FOUND;
    }
    
    std::vector<Motion> nextDir = curState.getSuccessorsDir();
    
    
    for (auto i = nextDir.begin(); i != nextDir.end(); ++i) {
        
        if ((path.size() >= 1) && path[path.size() - 1] == reverseMotion(*i)) {
            continue;
        }
        FifteenGame next = curState;
        next.move(*i);
        path.push_back(*i);
        uint nextWay = next.getEuristic() + curCost + 1;
        
        if (nextWay <= curCostBound) {
                uint t = depthFirstSearch(next, curCost + 1, curCostBound, path);
                if (t == FOUND) {
                    return FOUND;
                }
            }
        path.pop_back();
        }
    return NOT_FOUND;
}




#endif
