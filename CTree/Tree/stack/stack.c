#include "stack.h"

void InitStack(Stack* S)
{
	InitList(S);
}
Stack DestroyStack(Stack S)
{
	return DestroyList(S);
}
_Bool StackIsEmpty(Stack S)
{
	return ListIsEmpty(S);
}
Stack Push(const StackElementType elem, Stack S)
{
	return PushFront(elem, S);
}
Stack Pop(Stack S)
{
	return PopFront(S);
}
StackElementType Top(Stack S)
{
	return RetrieveFromListPos(HeadOfList(S));
}
unsigned int StackSize(Stack S)
{
	return ListSize(S);
}