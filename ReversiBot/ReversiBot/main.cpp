//
//  main.cpp
//  ReversiBot
//
//  Created by Alexander Malyshev on 16.12.15.
//  Copyright © 2015 Alexander Malyshev. All rights reserved.
//

//#include "IBot.hpp"
//#include "FieldCoordinate.hpp"
//#include "Constants.hpp"
#include "CuteBot.hpp"

int main(int argc, const char * argv[]) {
    Field field;
    CuteBot bot;
    bot.play(std::cin, std::cout);
    return 0;
}
