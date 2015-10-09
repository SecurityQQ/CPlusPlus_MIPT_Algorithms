//! ======CNODE_INIT========
struct CNode {
    int Data;
    CNode *next;
    CNode *prev;
};
//! ====END_OF_CNODE_INIT===

//! ======CSTACK_INIT========
struct CStack {
    CNode *top;
};
void Init(CStack *stack){
    stack->top = 0;
}
void Push(CStack *stack, int data) {
    CNode *node = (CNode *) malloc(sizeof(CNode));
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
    
    CNode *prevTop = stack->top;
    stack->top = stack->top->next;
    
    free(prevTop);
    return data;
}
//! ====END_OF_CSTACK_INIT===
