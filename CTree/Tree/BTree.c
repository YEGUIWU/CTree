#include "BTree.h"
#include <stdlib.h>
#include <memory.h>
#include "stack/stack.h"

//开启非递归遍历
//#define NON_RECURSION 1

typedef struct BTreeNode BTreeNode;
typedef BTreeNode* PtrToBTreeNode;
static int g_nNodes = 3;



int BTree_SetCountOfNode(int n)
{
    if (n > 2)
    {
        g_nNodes = n;
    }
    return g_nNodes;
}
int	 BTree_GetCountOfNode()
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
//初始化树
static BTree BTree_Initialize()
{
    return (BTree) { MakeBTreeNode(-1, 0), NULL };
}
//
void ShowNodes(BTree tree)
{
    for (int ib = 0, ie = tree.nPosition, count; ib < ie; ++ib)
    {
        for (count = 0; count < g_nNodes; ++count)
        {
            if (!tree.positions[ib]->Children[count])
            {
                break;
            }
        }
        printf("%d %c %d\n", ib, tree.positions[ib]->Element, count);
    }
}
//
void ShowDegrees(BTree tree)
{
    int* p = (int*)calloc(sizeof(int), g_nNodes + 1);
    if (p)
    {
        for (int ib = 0, ie = tree.nPosition, count; ib < ie; ++ib)
        {
            for (count = 0; count < g_nNodes; ++count)
            {
                if (!tree.positions[ib]->Children[count])
                {
                    break;
                }
            }
            ++p[count];
        }
        for (int i = 0; i <= g_nNodes; ++i)
        {
            printf("degree[%d] = %d\n", i, p[i]);
        }

        free(p);
    }
}
//
int BTree_Destroy(BTree* pTree)
{
    if (!pTree)
    {
        return -1;
    }
    for (int ib = 0, ie = pTree->nPosition; ib < ie; ++ib)
    {
        if (pTree->positions[ib]->Children)
        {
            //free(pTree->positions[ib]->Children);
            //pTree->positions[ib]->Children = NULL;
        }
        free(pTree->positions[ib]);
    }
    //free(pTree->root);
    free(pTree->positions);
    pTree->root = NULL;
    pTree->positions = NULL;
    pTree->nPosition = 0;
    return 0;
}
//
int BTree_MakeTree(BTree* pTree, BTreeArray tree_array, int n)
{
    if (!pTree || !tree_array)
    {
        return -1;
    }
    *pTree = BTree_Initialize();
    pTree->nPosition = n;
    pTree->root->Element = tree_array->data;
    pTree->root->Number = 0;
    pTree->positions = (PtrToBTreeNode*)malloc(sizeof(PtrToBTreeNode*) * n);
    PtrToBTreeNode* trees = pTree->positions;
    trees[0] = pTree->root;
    for (int i = 1; i < n; ++i)
    {
        trees[i] = MakeBTreeNode(i, tree_array[i].data);
    }
    PtrToBTreeNode pTmp;
    for (int i = 1; i < n; ++i)
    {
        pTmp = trees[tree_array[i].parent];
        
        for (int j = 0; j < g_nNodes; ++j)
        {
            if (!pTmp->Children[j])
            {
                //printf("%d -> %d\n", i, tree_array[i].parent);
                pTmp->Children[j] = trees[i];
                break;
            }
        }
    }
    //free(trees);
    return 0;
}

static void PreOrderBase(BTreePosition root, void(*func)(BTreePosition))
{
#ifndef NON_RECURSION
    if (!root)
    {
        return;
    }
    func(root);
    for (int i = 0; i < BTree_GetCountOfNode(); ++i)
    {
        PreOrderBase(root->Children[i], func);
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

void BTree_PreOrder(BTree root, void(*func)(BTreePosition))
{
    PreOrderBase(root.root, func);
}

static void PostOrderBase(BTreePosition root, void(*func)(BTreePosition))
{
#ifndef NON_RECURSION
    if (!root)
    {
        return;
    }
    for (int i = 0; i < BTree_GetCountOfNode(); ++i)
    {
        PreOrderBase(root->Children[i], func);
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
//后序遍历
void BTree_PostOrder(BTree root, void(*func)(BTreePosition))
{
    PostOrderBase(root.root, func);
}
//层序遍历
#include "queue/queue.h"
typedef struct queue_elem
{
    void* pos;
    int step;
}queue_elem;
queue_elem* MakeQueueElem(void*pos, int step)
{
    queue_elem* p = malloc(sizeof(queue_elem));
    p->pos = pos;
    p->step = step;
    return p;
}
void SeqOrderBase(BTreePosition root, void(*func)(BTreePosition))
{
    if (!root)
    {
        return;
    }
    Queue Q;
    InitQueue(&Q);
    EnQueue(root, &Q);					 //根结点先入队
    PtrToBTreeNode tmp = NULL;

    while (!QueueIsEmpty(Q))				 //队列不空
    {
        tmp = FirstOfQueue(Q);			 //获取队头元素
        DeQueue(&Q);						 //对头离队
        func(tmp);						 //访问当前树结点

        for (int i = 0; i < g_nNodes; ++i)
        {
            if (tmp->Children[i])
            {
                EnQueue(tmp->Children[i], &Q);
            }
        }
    }

}
void BTree_SeqOrder(BTree root, void(*func)(BTreePosition))
{
    SeqOrderBase(root.root, func);    
}

//计算树的最大深度
static int MaxDepthBase(BTreePosition tree)
{
    if (!tree)
    {
        return 0;
    }
    int res = 1;
    for (int i = 0; i < g_nNodes && tree->Children[i]; ++i)
    {
        res = max(res, 1 + MaxDepthBase(tree->Children[i]));
    }

    return res;
}
int BTree_MaxDepth(BTree tree)
{
    return MaxDepthBase(tree.root);
}