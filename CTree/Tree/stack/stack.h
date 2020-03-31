#ifndef _STACK_H_
#define _STACK_H_

#define LINK_STACK 1

#ifdef LINK_STACK
#include "../link_list/link_list.h"
//---------------------------------------
typedef void* StackElementType;

//---------------------------------------
typedef List Stack;
typedef ListPosition  StackPosition;
#endif // LINK_Stack

void InitStack(Stack* S);
Stack DestroyStack(Stack S);
_Bool StackIsEmpty(Stack S);
Stack Push(const StackElementType elem, Stack S);//入队
StackElementType Top(Stack S);
Stack Pop(Stack S);//出队
unsigned int StackSize(Stack S);
Stack DestroyStack(Stack S);
#endif //_STACK_H_