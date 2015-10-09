//
//  CTextEditor.h
//  TextEditor
//
//  Created by Александр Малышев on 02.03.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#ifndef __TextEditor__CTextEditor__
#define __TextEditor__CTextEditor__

#include <stdio.h>
#include <vector>
#include <string>
#include <stack>

class CTextEditor {
    
public:
    
    CTextEditor();
    void insertLineBreak();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void backspace();
    void doBackspace();
    void undo();
    void redo();
    void addSymbol(char ch);
    void doAdd(char ch);
    
    void printText();
private:
    
    struct CCursorPos {
        size_t line;
        size_t pos;
        CCursorPos() : line(0), pos(0) {};
    };
    
    struct COperation {
        char symbol;
        bool isDelete;
        CCursorPos cursor;
        COperation() : symbol('\n'), isDelete(false) {};
    };
    
    std::vector<std::string> lines;
    CCursorPos cursorPos;
    std::stack<COperation> undoStack;
    std::stack<COperation> redoStack;
};

#endif /* defined(__TextEditor__CTextEditor__) */
