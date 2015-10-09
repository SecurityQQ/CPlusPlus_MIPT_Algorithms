//
//  CTextEditor.cpp
//  TextEditor
//
//  Created by Александр Малышев on 02.03.15.
//  Copyright (c) 2015 SecurityQQ. All rights reserved.
//

#include "CTextEditor.h"
#include <iterator>
#include <iostream>

CTextEditor:: CTextEditor() {
    lines.push_back("");
}



void CTextEditor:: insertLineBreak() {

    std::stack<COperation>().swap(redoStack);
    
    std::string tailString(lines[cursorPos.line].begin() + cursorPos.pos, lines[cursorPos.line].end());
    lines[cursorPos.line].erase(lines[cursorPos.line].begin() + cursorPos.pos, lines[cursorPos.line].end());
    lines.insert(lines.begin() + cursorPos.line + 1, tailString);
    
    ++cursorPos.line;
    cursorPos.pos = 0;
    
    COperation op;
    op.symbol = '\n';
    op.cursor = cursorPos;
    op.isDelete = true;
    undoStack.push(op);
}

void CTextEditor:: moveLeft() {
    if( cursorPos.pos > 0 ) {
        --cursorPos.pos;
        return;
    }
    if( cursorPos.line > 0 ) {
        --cursorPos.line;
        cursorPos.pos = lines[cursorPos.line].size();
    }
}

void CTextEditor:: moveRight() {
    if( cursorPos.pos < lines[cursorPos.line].size()) {
        ++cursorPos.pos;
        return;
    }
    if( cursorPos.line < ( lines.size() - 1) ) {
        ++cursorPos.line;
        cursorPos.pos = 0;
    }
}

void CTextEditor:: moveUp() {
    if( cursorPos.line > 0 ) {
        --cursorPos.line;
        cursorPos.pos = std::min(cursorPos.pos, lines[cursorPos.line].size());
    }
}

void CTextEditor:: moveDown() {
    if( cursorPos.line < lines.size() - 1 ) {
        ++cursorPos.line;
        cursorPos.pos = std::min(cursorPos.pos, lines[cursorPos.line].size());
    }
}

void CTextEditor:: backspace() {
    std::stack<COperation>().swap(redoStack);
    if( cursorPos.pos == 0 && cursorPos.line == 0) {
        return;
    }
    
    if( cursorPos.pos == 0 ) {
        lines[cursorPos.line - 1].append(lines[cursorPos.line]);
        for( unsigned long i = cursorPos.line; i < lines.size(); ++i ) {
            std::swap(lines[i], lines[i + 1]);
        }
        lines.pop_back();
        --cursorPos.line;
        cursorPos.pos = lines[cursorPos.line].size();
        return;
    }
    
    char ch = lines[cursorPos.line][cursorPos.pos - 1];
    doBackspace();
    
    COperation op;
    op.cursor = cursorPos;
    op.isDelete = false;
    op.symbol = ch;
    undoStack.push(op);
}

void CTextEditor:: doBackspace() {
    --cursorPos.pos;
    lines[cursorPos.line].erase(lines[cursorPos.line].begin() + cursorPos.pos, lines[cursorPos.line].begin() + cursorPos.pos + 1);
    std::stack<COperation>().swap(redoStack);
}

void CTextEditor:: undo() {
    if( undoStack.empty() ) {
        return;
    }
    
    COperation op = undoStack.top();
    undoStack.pop();
    cursorPos = op.cursor;
    if( op.isDelete ) {
        doBackspace();
    } else {
        doAdd(op.symbol);
    }
    
    COperation redoOp;
    redoOp.cursor = op.cursor;
    redoOp.isDelete = !op.isDelete;
    redoOp.symbol = op.symbol;
    redoStack.push(redoOp);
}

void CTextEditor:: redo() {
    if( redoStack.empty() ) {
        return;
    }
    
    COperation op = redoStack.top();
    redoStack.pop();
    if( op.isDelete ) {
        cursorPos = op.cursor;
        doBackspace();
    } else {
        doAdd(op.symbol);
    }
    
    COperation undoOp;
    undoOp.cursor = op.cursor;
    undoOp.isDelete = !op.isDelete;
    undoOp.symbol = op.symbol;
    undoStack.push(undoOp);
}

void CTextEditor:: addSymbol(char ch) {
    std::stack<COperation>().swap(redoStack);
    doAdd(ch);
    COperation op;
    op.symbol = ch;
    op.cursor = cursorPos;
    op.isDelete = true;
    undoStack.push(op);
}

void CTextEditor:: doAdd(char ch) {
    lines[cursorPos.line].insert(lines[cursorPos.line].begin() + cursorPos.pos, ch);
    ++cursorPos.pos;

}

void CTextEditor:: printText() {
    for( int i = 0; i < lines.size(); ++i ) {
        printf("\'");
        std::cout<< lines[i] <<"\'"<<std::endl;
    }
    std::cout<<"----\n";
}