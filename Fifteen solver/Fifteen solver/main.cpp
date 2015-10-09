//
//  main.cpp
//  Fifteen solver
//
//  Created by Александр Малышев on 17.05.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <iostream>
//#include "FifteenGame.h"
#include "FifteenGameSolver_v2.h"
int main(int argc, char * argv[]) {
    srand(time(NULL));
    FifteenGame newGame = FifteenGame(5).newGame();
    newGame.printBoard();

    
    auto x = newGame.solve();
//    if ( x == FOUND) {
//        std::cout<<"\nfinished\n";
//    }
    
    std::cout<<"\nfinished\n";
    for (auto i = x.begin(); i != x.end(); ++i) {
        std::cout<<char(*i);
    }
    return 0;
}