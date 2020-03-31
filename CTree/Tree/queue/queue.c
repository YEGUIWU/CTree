#include "queue.h"
void InitQueue(Queue* Q)
{
	InitList(Q);
}
Queue DestroyQueue(Queue Q)
{
	return DestroyList(Q);
}
_Bool QueueIsEmpty(Queue Q)
{
	return ListIsEmpty(Q);
}
Queue EnQueue(const QueueElementType elem, Queue Q)
{
	return PushBack(elem, Q);
}
Queue DeQueue(Queue Q)
{
	return PopFront(Q);
}
QueueElementType FirstOfQueue(Queue Q)
{
	return RetrieveFromListPos(HeadOfList(Q));
}
unsigned int QueueSize(Queue Q)
{
	return ListSize(Q);
}