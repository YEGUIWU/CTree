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
_Bool StackIsEmpty(Stack S);
int Push(const StackElementType elem, Stack* pS);//入队
int Pop(Stack *pS);//出队
StackElementType Top(Stack S);
unsigned int StackSize(Stack S);
int DestroyStack(Stack* S);
#endif //_STACK_H_