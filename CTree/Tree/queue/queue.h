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
Queue DestroyQueue(Queue Q);
_Bool QueueIsEmpty(Queue Q);
Queue EnQueue(const QueueElementType elem, Queue Q);//���
QueueElementType FirstOfQueue(Queue Q);
Queue DeQueue(Queue Q);//����
unsigned int QueueSize(Queue Q);
Queue DestroyQueue(Queue Q);
#endif