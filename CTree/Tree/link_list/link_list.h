#ifndef _LINK_LIST_
#define _LINK_LIST_
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

//ʹ�õ�����
#define SINGLE_LINK_LIST 1
//ʹ��˫����
//#define DOUBLE_LINK_LIST 1


typedef void* ListElementType;


#ifdef SINGLE_LINK_LIST
typedef struct ListNode
{
	ListElementType ELement;
	struct ListNode* Next;
} ListNode;
typedef ListNode* List;
#elif DOUBLE_LINK_LIST
typedef struct ListNode
{
	ListElementType ELement;
	struct ListNode* Next;
	struct ListNode* Pre;
} ListNode;
typedef struct List
{
	ListNode* Head;
	ListNode* Tail;
	long		  Length;
}List;
#endif // SINGLE_LINKE_LIST

typedef ListNode* ListPosition;
//��ʼ������
void InitList(List* L);

//�ж������Ƿ�Ϊ��
_Bool ListIsEmpty(List L);

//�ж�ĳ��λ���Ƿ�λ������Ľ�β
_Bool PosInListIsLast(ListPosition P);

//����ĳ��Ԫ�ص�λ��
ListPosition FindInList(ListElementType X, List L);

//���ҷ��������Ľ��
ListPosition FindIf(_Bool(*p)(), List L);

//��������ɾ��ĳ��Ԫ��
void DeleteFromList(ListElementType X, List L);

//����ĳ��Ԫ�ص���һ��λ��
ListPosition FindPrePosFromList(ListElementType X, List L);

//β����Ԫ��
List PushBack(ListElementType X, List L);

//ͷ����Ԫ��
List PushFront(ListElementType X, List L);

//ɾ��β��
List PopBack(List L);

//ɾ��ͷ��
List PopFront(List L);

//��ĳ��λ�÷���ĳ��Ԫ��
void InsertToList(ListElementType X, ListPosition P);

//�������
List DestroyList(List L);

//��ȡ����ͷ���λ��
ListPosition HeadOfList(List L);

//��ȡ����β���λ��
ListPosition TailOfList(List L);

//��ȡ����ĵ�һ��Ԫ��
ListElementType FirstOfList(List L);

//��ȡ��������һ��Ԫ��
ListElementType FinalOfList(List L);

//������һ��λ��
#ifdef SINGLE_LINK_LIST
ListPosition AdvanceOfListPos(ListPosition P, List L);
#elif DOUBLE_LINK_LIST
ListPosition AdvanceOfListPos(ListPosition P);
#endif

//�ӽڵ�λ��ȡ��Ԫ�ص�ֵ
ListElementType RetrieveFromListPos(ListPosition P);

//��ӡ����
void DisplayList(List L, void(*pDisplayFunc)(ListPosition));

//��������
void SortList(List lst, int(*pCmp)(ListElementType, ListElementType));

//��ȡ����Ĵ�С
unsigned int ListSize(List L);

//������󣬴�ӡ������Ϣ
void ListError(const char* errMsg);

//���ش��󣬴�ӡ������Ϣ�����˳�����
void ListFailError(const char* errMsg);
#endif // !_LINK_LIST_