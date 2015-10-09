#include <iostream>
#include <string.h>
#include "assert.h"

//! ======CNODE_INIT========
template <class T>
class CNode {
public:
    T Data;
    CNode *next;
    CNode *prev;
};
//! ====END_OF_CNODE_INIT===

//! ======CSTACK_INIT========
template <class T>
class CStack {
public:
    CStack();
    ~CStack();
    CNode<T> *top;
    void Push(T data);
    T Pop();
};

template <class T>
CStack<T>::CStack(){
    top = NULL;
}

template <class T>
CStack<T>::~CStack() {
    while( top != NULL ) {
        Pop();
    }
    top = NULL;
}

template <class T>
void CStack<T>::Push(T data) {
    CNode<T> *node = (CNode<T> *) malloc(sizeof(CNode<T>));
    node->Data = data;
    if (top == NULL) {
        top = node;
    }
    else {
        node->next = top;
        top = node;
    }
}

template <class T>
T CStack<T>::Pop() {
    assert(top != NULL);
    T data = top->Data;
    
    CNode<T> *prevTop = top;
    top = top->next;
    
    free(prevTop);
    return data;
}

//! ====END_OF_CSTACK_INIT===


//! ====POSTFIX TRANSLATION INIT===

struct Operator {
    char oper;
    int priority;
} Operator;

char* doPostfix(char* str);
void pushOper(char* str, char oper, int &num);
void pushVar(char* str, char* var, int &num, int &length);

//! ====END OF POSTFIX TRANSLATION INIT===

//! Wrapper for char* to T translator
template <class T>
T atoT(char* number);

//! Doing calculations with str in postfix record
template <class T>
double doCalc(char * str);

//! int to char* translator
char* itoa(int value);

//! Dynamic gets char*
char* getCharPtr();

//! Coping string [start; end)
char* strcpyInRange(char* str, int start, int end);

//! Merging string and char
void strcatChar(char* str, char c);

//! Getting first right closing bracket
int getClosingBracket(char* str, int start);

//! True when c = +, -, *, /
bool isOperator(char c);

//! strlen
int strLen(char* str);

int main(int argc, const char * argv[]) {
    
    char* str = getCharPtr();
    char* postFix = doPostfix(str);
    std::cout<<doCalc<double>(postFix) <<std::endl;
    return 0;
}


int strLen(char* str) {
    int i = 0;
    while(str[i++] != '\0');
    return i;
}
//!! dynamic gets(str)
char* getCharPtr() {
    char* foo = (char *) malloc(1000 * sizeof(char));
    gets(foo);
    char* str = (char *) malloc((strLen(foo) - 1) * sizeof(char));
    memmove(str, foo, (strLen(foo)) * sizeof(char));
    free(foo);
    return str;
}

//! getNumber ignoring spaces
char* getNumber(char* str, int &start) {
    int s = start;
    int e;
    if( isOperator(str[s]) ) {
        ++s;
    }
    assert(str[s] != '+' && str[s] != '*' && str[s] != '-' && str[s] != '/');
    while( str[s] == ' '  && str[s] != '\0' ) {
        ++s;
    }
    if( str[s] == ')' || str[s] == '(' )  {
        start = s;
        return (char*) "-1";
    }
    e = s;
    while( str[e] != ')' && str[e] != ' ' && str[e] != '+' && str[e] != '*' && str[e] != '-' && str[e] != '/' && str[e] != '(' && str[e] != '\0') {
        ++e;
        
    }
    start = e;
    return strcpyInRange(str, s, e);
}

//! do Calculations from postFix string
template <class T>
double doCalc(char * str) {
    CStack<T> s;
    int i = 0;
    while (str[i] != '\0') {
        if (!isspace(str[i])) {
            switch(str[i]) {
                case '+': {
                    T op1 = s.Pop();
                    T op2 = s.Pop();
                    T result = op1 + op2;
                    s.Push(result);
                } break;
                case '-': {
                    T op1 = s.Pop();
                    T op2 = s.Pop();
                    T result = op2 - op1;
                    s.Push(result);
                } break;
                case '*': {
                    T op1 = s.Pop();
                    T op2 = s.Pop();
                    T result = op1 * op2;
                    s.Push(result);
                } break;
                case '/': {
                    T op1 = s.Pop();
                    T op2 = s.Pop();
                    T result = op2 / op1;
                    s.Push(result);
                } break;
                default: {
                    char* number = getNumber(str, i);
                    T tmp = atoT<T>(number);
                    s.Push(tmp);
                }
            }
        }
        ++i;
    }
    
    return s.top->Data;
}

template <class T>
T atoT(char* number) {
    return atoi(number);
}
//!copying string from index = start to index = end
char* strcpyInRange(char* str, int start, int end) {
    char* cpystr = (char *) malloc( (end - start) * sizeof(char));
    assert(start <= end);
    for( int i = 0; start < end; ++i) {
        cpystr[i] = str[start++] ;
    }
    return cpystr;
}

void strcatChar(char* str, char c) {
    char* tmp = (char*) malloc(sizeof(char));
    tmp[0] = c;
    strcat(str, tmp);
}
bool isOperator(char c) {
    if( c == '*' ||
       c == '/' ||
       c == '+' ||
       c == '-' ) {
        return true;
    }
    return false;
}



//!POSTFIXTRANSLATION METHODS

void pushVar(char* str, char* var, int &num, int &length)
{
    for (int i = 0; i < length; ++i) {
        str[num] = var[i];
        ++num;
    }
    length = 0;
    str[num] = ' ';
    ++num;
}

void pushOper(char* str, char oper, int &num)
{
    str[num] = oper;
    ++num;
    str[num] = ' ';
    ++num;
}

char* doPostfix(char* str)
{
    const int STRLEN = (int) strLen(str);
    
    char* varArr = (char*) malloc(1000 * sizeof(char));
    char* num = (char*) malloc(20 * sizeof(char));
    struct Operator* operArr = (struct Operator*) malloc(sizeof(struct Operator) * 2 * STRLEN);
    
    int len = 0;
    int varLen = 0;
    int operLen = 0;
    
    int i = 0;
    
    while (str[i] != '\0')
    {
        if (str[i] >= '0' && str[i] <= '9') {
            num[varLen] = str[i];
            ++varLen;
        }
        else
        {
            if (varLen != 0) {
                pushVar(varArr, num, len, varLen);
            }
            int priority = 0;
            switch (str[i]) {
                case '+':
                case '-': {
                    priority = 2;
                    break;
                }
                case '*':
                case '/': {
                    priority = 3;
                    break;
                }
                case '(': {
                    priority = 1;
                    operArr[operLen].oper = str[i];
                    operArr[operLen].priority = priority;
                    operLen++;
                    break;
                }
            }
            if (priority >= 2) {
                while (operArr[operLen - 1].priority >= priority && operLen > 0) {
                    pushOper(varArr, operArr[operLen - 1].oper, len);
                    operLen--;
                }
                operArr[operLen].oper = str[i];
                operArr[operLen].priority = priority;
                operLen++;
            }
            if (str[i] == ')') {
                operLen--;
                while (operArr[operLen].oper != '(') {
                    pushOper(varArr, operArr[operLen].oper, len);
                    operLen--;
                }
            }
        }
        ++i;
    }
    if (varLen != 0) {
        pushVar(varArr, num, len, varLen);
    }
    while (operLen > 0) {
        pushOper(varArr, operArr[operLen - 1].oper, len);
        operLen--;
    }
    return varArr;
}
//! END OF POSTFIXTRANSLATION METHODS