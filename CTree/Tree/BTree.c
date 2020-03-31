#include "BTree.h"
#include <stdlib.h>
#include <memory.h>
#include "stack/stack.h"

//�����ǵݹ����
//#define NON_RECURSION 1

typedef BTreeNode* PtrToBTreeNode;
static int g_nNodes = 3;


int SetCountOfNode(int n)
{
    if (n > 2)
    {
        g_nNodes = 3;
    }
    return g_nNodes;
}
int	 GetCountOfNode()
{
    return g_nNodes;
}

static PtrToBTreeNode MakeBTreeNode(int number, BTreeElementType elem)
{
    PtrToBTreeNode ptr = (PtrToBTreeNode)malloc(sizeof(BTreeNode));
    ptr->Element = elem;
    ptr->Number = number;
    ptr->Children = calloc(g_nNodes, sizeof(PtrToBTreeNode));
    return ptr;
}
//��ʼ����
BTree BTree_Initialize()
{
    return MakeBTreeNode(-1, 0);
}
//��Ԫ�� X ���뵽��T
//��Ԫ�� X ���뵽��T
BTree BTree_InsertTo(BTreeElementType X, int father, int self,  BTree T)
{
    
}

//�������
//void BTree_PreOrderBase(BTree root, void(*func)(BTree))
void BTree_PreOrder(BTree root, void(*func)(BTree))
{
#ifdef NON_RECURSION
    if (!root)
    {
        return;
    }
    func(root);
    for (int i = 0; i < GetCountOfNode(); ++i)
    {
        BTree_PreOrder(root->Children[i], func);
    }
#else
    if (!root)
    {
        return;
    }
    Stack stack;
    InitStack(&stack);
    stack = Push(root, stack);
    PtrToBTreeNode ptr = NULL;
    while (!StackIsEmpty(stack))
    {
        ptr = Top(stack);
        stack = Pop(stack);

        func(root);
        for (int i = g_nNodes - 1; i > -1; --i)
        {
            stack = Push(root->Children[i], stack);
        }
    }
    stack = DestroyStack(stack);
#endif
}
//�������
void BTree_PostOrder(BTree root, void(*func)(BTree))
{
#ifdef NON_RECURSION
    if (!root)
    {
        return;
    }
    for (int i = 0; i < GetCountOfNode(); ++i)
    {
        BTree_PreOrder(root->Children[i], func);
    }
    func(root);
#else
    if (!root)
    {
        return;
    }
    Stack stack;
    InitStack(&stack);
    stack = Push(root, stack);
    PtrToBTreeNode ptr = NULL;
    while (!StackIsEmpty(stack))
    {
        ptr = Top(stack);
        stack = Pop(stack);

        func(root);
        for (int i = 0; i < g_nNodes; ++i)
        {
            stack = Push(root->Children[i], stack);
        }
    }
    stack = DestroyStack(stack);
#endif
}
//�������
#include "queue/queue.h"
void BTree_SeqOrder(BTree root, void(*func)(BTree))
{
    if (!root)
    {
        return;
    }
    Queue queue;
    InitQueue(&queue);
    
}