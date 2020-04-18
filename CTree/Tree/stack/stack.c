#include "stack.h"

void InitStack(Stack* S)
{
	InitList(S);
}
int DestroyStack(Stack* S)
{
	return DestroyList(S);
}
_Bool StackIsEmpty(Stack S)
{
	return ListIsEmpty(S);
}
int Push(const StackElementType elem, Stack* pS)
{
	return ListPushBack(elem, pS);
}
int Pop(Stack* pS)
{
	return ListPopBack(pS);
}
StackElementType Top(Stack S)
{
	return RetrieveFromListPos(HeadOfList(S));
}
unsigned int StackSize(Stack S)
{
	return ListSize(S);
}