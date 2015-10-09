//
//  Stack.h
//  HaffmanCode
//
//  Created by Александр Малышев on 10.12.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//

#ifndef HaffmanCode_Stack_h
#define HaffmanCode_Stack_h
#include "CNode.h"
//! ======node_INIT========
struct node {
    unsigned char Data;
    node *next;
    node *prev;
};
//! ====END_OF_node_INIT===

//! ======CSTACK_INIT========
struct CStack {
    node *top;
};
void Init(CStack *stack){
    stack->top = 0;
}
void Push(CStack *stack, unsigned char data) {
    node *node = (node *) malloc(sizeof(node));
    node->Data = data;
    if (stack->top == 0) {
        stack->top = node;
    }
    else {
        node->next = stack->top;
        stack->top = node;
    }
}
int Pop(CStack * stack) {
    assert(stack->top != 0);
    int data = stack->top->Data;
    
    node *prevTop = stack->top;
    stack->top = stack->top->next;
    
    free(prevTop);
    return data;
}
//! ====END_OF_CSTACK_INIT===

#endif
