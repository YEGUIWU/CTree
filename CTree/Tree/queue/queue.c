#include "queue.h"
void InitQueue(Queue* Q)
{
	InitList(Q);
}
int DestroyQueue(Queue* Q)
{
	return DestroyList(Q);
}
_Bool QueueIsEmpty(Queue Q)
{
	return ListIsEmpty(Q);
}
int EnQueue(const QueueElementType elem, Queue* pQ)
{
	return ListPushBack(elem, pQ);
}
int DeQueue(Queue* pQ)
{
	return ListPopFront(pQ);
}
QueueElementType FirstOfQueue(Queue Q)
{
	return RetrieveFromListPos(HeadOfList(Q));
}
unsigned int QueueSize(Queue Q)
{
	return ListSize(Q);
}