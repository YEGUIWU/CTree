#ifndef _QUEUE_H_
#define _QUEUE_H_

#define LINK_QUEUE 1

#ifdef LINK_QUEUE
#include "../link_list/link_list.h"
//---------------------------------------
//typedef int QueueElementType;
typedef void* QueueElementType;

//---------------------------------------
typedef List Queue;
typedef ListPosition  QueuePosition;
#endif // LINK_QUEUE

void InitQueue(Queue* Q);
_Bool QueueIsEmpty(Queue Q);
QueueElementType FirstOfQueue(Queue Q);
int EnQueue(const QueueElementType elem, Queue *pQ);//入队
int DeQueue(Queue* pQ);//出队
unsigned int QueueSize(Queue Q);
int DestroyQueue(Queue* Q);
#endif