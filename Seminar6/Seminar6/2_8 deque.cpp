//
//  main.cpp
//  Seminar6
//
//  Created by Александр Малышев on 27.10.14.
//  Copyright (c) 2014 SecurityQQ. All rights reserved.
//

#include <iostream>
#include <assert.h>

//! ======CNODE_INIT========
struct CNode {
    int Data;
    CNode *next;
    CNode *prev;
};
//! ====END_OF_CNODE_INIT===

//! ======CDeque_INIT========
struct CDeque {
    CNode *front;
    CNode *back;
};
void Init(CDeque *deque) {
    deque->front = NULL;
    deque->back = NULL;
}

void pushFront(CDeque *deque, int data) {
    CNode *node = (CNode *) malloc(sizeof(CNode));
    node->Data = data;
    node->prev = node;
    node->next = node;
    if (deque->front == NULL) {
        deque->front = node;
        deque->back = node;
    }
    else {
        node->prev = deque->front;
        deque->front->next = node;
        deque->front = node;
    }
}

void pushBack(CDeque *deque, int data) {
    CNode *node = (CNode *) malloc(sizeof(CNode));
    node->Data = data;
    node->prev = node;
    node->next = node;
    if (deque->back == NULL) {
        deque->front = node;
        deque->back = node;
    }
    else {
        node->next = deque->back;
        deque->back->prev = node;
        deque->back = node;
    }
}

int popFront(CDeque *deque) {
    //assert(deque->front != NULL);
    if( deque->front == NULL ) {
        return -1;
    }
    
    int data = deque->front->Data;
    if( deque->front == deque->back ) {
        deque->front = NULL;
        deque->back = NULL;
    } else {
        CNode *prevFront = deque->front;
        deque->front = deque->front->prev;
        free(prevFront);
    }
    return data;
}
int popBack(CDeque *deque) {
    //assert(deque->back != NULL);
    if( deque->back == NULL ) {
        return -1;
    }
    
    int data = deque->back->Data;
    if( deque->back == deque->front ) {
        deque->front = NULL;
        deque->back = NULL;
    } else {
        CNode *prevBack = deque->back;
        deque->back = deque->back->next;
        free(prevBack);
    }
    return data;
}

void Deinit(CDeque *deque) {
    while (deque->front != NULL) {
        popFront(deque);
    }
}
//! ====END_OF_CSTACK_INIT===

int main(int argc, const char * argv[]) {
    int n, cmd, value;
    bool isDequeOK = true;
    CDeque deque;
    Init(&deque);
    scanf("%d", &n);
    
    for( int i = 0; i < n; ++i) {
        scanf("%d%d", &cmd, &value);
        if (isDequeOK) {
            switch (cmd) {
                case 1:
                    pushFront(&deque, value);
                    break;
                    
                case 2:
                    if (value != popFront(&deque)) isDequeOK = false;
                    break;
                    
                case 3:
                    pushBack(&deque, value);
                    break;
                    
                case 4:
                    if (value != popBack(&deque)) isDequeOK = false;
                    break;
            }
        }
    }
    if( isDequeOK ) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    
    
    return 0;
}
