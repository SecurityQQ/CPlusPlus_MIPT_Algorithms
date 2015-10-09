//
//  main.cpp
//  TextEditor
//
//  Created by Александр Малышев on 02.03.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include <iostream>
#include "CTextEditor.h"

bool getNext(char& ch) {
    
    std::cin.get(ch);
    if( std::cin.fail() ) {
        return false;
    }
    return true;
}

int main(int argc, const char * argv[]) {
    CTextEditor editor;
    char ch;
    while( getNext(ch) ) {
        switch( ch ) {
            case '\n':
                editor.insertLineBreak();
                break;
                
            case '<':
                editor.moveLeft();
                break;
                
            case '>':
                editor.moveRight();
                break;
                
            case '^':
                editor.moveUp();
                break;
                
            case '|':
                editor.moveDown();
                break;
                
            case '#':
                editor.backspace();
                break;
                
            case '@':
                editor.undo();
                break;
                
            case '$':
                editor.redo();
                break;
                
            default:
                editor.addSymbol(ch);
        }
    }
    editor.printText();
    return 0;
}
