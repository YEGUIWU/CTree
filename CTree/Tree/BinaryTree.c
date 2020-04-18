#include "BinaryTree.h"

static const TreeElementType NullElem = 0;

static TreePosition NullNode = NULL;

typedef TreeNode* PtrToTreeNode;
//-------------------------------
//报错处理
void TreeError(const char* errMsg);
//失败处理
void TreeFailError(const char* errMsg);
//构造结点
PtrToTreeNode MakeTreeNode(TreeElementType X);
//销毁树结点
PtrToTreeNode DestoryTreeNode(PtrToTreeNode P);


#ifdef COMMON_TREE

int BinaryTree_MakeTree(BinaryTree* Tree, BinaryTreeArray pArray, int n)
{
	PtrToTreeNode* ptrs = (PtrToTreeNode*)calloc(n, sizeof(PtrToTreeNode));

	for (int i = 0; i < n; ++i)
	{
		ptrs[i] = MakeTreeNode(pArray[i].data);
	}
	*Tree = ptrs[0];
	PtrToTreeNode pTmp;
	for (int i = 1; i < n; ++i)
	{
		pTmp = ptrs[pArray[i].parent];//找爸爸位置
		if (!pTmp->Left)//爸爸还没有孩子，就做爸爸的孩子
		{
			pTmp->Left = ptrs[i];
		}
		else//爸爸有孩子了，就给爸爸的孩子当孩子
		{
			PtrToTreeNode pt;
			for (pt = pTmp->Left; pt->Right; pt = pt->Right)
			{
				//do nothing
			}
			pt->Right = ptrs[i];
			
		}
	}
	free(ptrs);
	return 0;
}
BinaryTree InitializeTree()
{
	return NullNode;
}
#elif SEARCH_TREE_COME_TRUE
#pragma region 搜索树
//--------------------------------------------------
//初始化
BinaryTree InitializeTree()
{
	return NullNode;
}
//--------------------------------------------------
//查找最小
TreePosition FindMinOnTree(BinaryTree T)
{
	if (T == NULL)
		return NULL;
	else if (T->Left == NULL)
		return T;
	else
		return FindMinOnTree(T->Left);
}
//--------------------------------------------------
//查找最大
TreePosition FindMaxOnTree(BinaryTree T)
{
	if (T != NULL)
	{
		while (T->Right != NULL)
		{
			T = T->Right;
		}
	}
	return T;
}

//--------------------------------------------------
//插入元素
BinaryTree InsertToTree(TreeElementType X, BinaryTree T)
{
	if (T == NULL)
	{
		T = MakeTreeNode(NullElem);
		if (T == NULL)
			TreeFailError("Out of space!!!");
		else
		{
			T->Element = X;
			T->Left = T->Right = NULL;
		}
	}
	else if (CompareTreeElement(&X, &T->Element) < 0)
		T->Left = InsertToTree(X, T->Left);
	else if (CompareTreeElement(&X, &T->Element) > 0)
		T->Right = InsertToTree(X, T->Right);
	return T;
}
//--------------------------------------------------
//删除元素
BinaryTree DeleteFromTree(TreeElementType X, BinaryTree T)
{
	TreePosition TmpCell;
	if (T == NULL)
		TreeError("Element not found");
	else if (CompareTreeElement(&X, &T->Element) < 0)
		T->Left = DeleteFromTree(X, T->Left);
	else if (CompareTreeElement(&X, &T->Element) > 0)
		T->Right = DeleteFromTree(X, T->Right);
	else if (T->Left && T->Right)
	{
		TmpCell = FindMinOnTree(T->Right);
		T->Element = TmpCell->Element;
		T->Right = DeleteFromTree(T->Element, T->Right);
	}
	else
	{
		TmpCell = T;
		if (T->Left == NULL)
			T = T->Right;
		else if (T->Right == NULL)
			T = T->Left;
		free(TmpCell);
	}
	return T;
}
#pragma endregion
#elif AVL_TREE
#pragma region 平衡树
#ifdef  AVL_TREE_COME_TRUE
//获取高
static int Height(TreePosition P)
{
	if (P == NULL)
		return -1;
	else
		return P->Height;
}

//左旋转
static TreePosition SingleRotateWithLeft(TreePosition K2)
{
	TreePosition K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;

	K2->Height = max(Height(K2->Left), Height(K2->Right)) + 1;
	K1->Height = max(Height(K1->Left), K2->Height) + 1;
	return K1;
}
//右旋转
static TreePosition SingleRotateWithRight(TreePosition K1)
{
	TreePosition K2 = K1->Right;
	K1->Right = K2->Left;
	K2->Left = K1;

	K1->Height = max(Height(K1->Left), Height(K1->Right)) + 1;
	K2->Height = max(Height(K2->Left), K1->Height) + 1;
	return K2;
}

//双旋转
static TreePosition DoubleRoteateWithLeft(TreePosition K3)
{
	K3->Left = SingleRotateWithRight(K3->Left);

	return SingleRotateWithLeft(K3);
}
//双旋转
static TreePosition DoubleRoteateWithRight(TreePosition K3)
{
	K3->Right = SingleRotateWithRight(K3->Right);

	return SingleRotateWithLeft(K3);
}
//初始化
BinaryTree InitializeTree()
{
	return NullNode;
}
//查找最小
TreePosition FindMinOnTree(BinaryTree T)
{
	if (T == NULL)
		return NULL;
	else if (T->Left == NULL)
		return T;
	else
		return FindMinOnTree(T->Left);
}
//查找最大
TreePosition FindMaxOnTree(BinaryTree T)
{
	if (T != NULL)
	{
		while (T->Right != NULL)
		{
			T = T->Right;
		}
	}
	return T;
}
//插入元素
BinaryTree InsertToTree(TreeElementType X, BinaryTree T)
{
	if (T == NULL)
	{
		T = MakeTreeNode(NullElem);
		if (T == NULL)
			TreeFailError("Out of space");
		else
		{
			T->Element = X;
			T->Height = 0;
			T->Left = T->Right = NULL;
		}
	}
	else if (CompareTreeElement(&X, &T->Element) < 0)
	{
		T->Left = InsertToTree(X, T->Left);
		if (Height(T->Left) - Height(T->Right) == 2)
		{
			if (X < T->Left->Element)
				T = SingleRotateWithLeft(T);
			else
				T = DoubleRoteateWithLeft(T);
		}
	}
	else if (CompareTreeElement(&X, &T->Element) > 0)
	{
		T->Right = InsertToTree(X, T->Right);
		if (Height(T->Right) - Height(T->Left) == 2)
		{
			if (X > T->Right->Element)
				T = SingleRotateWithRight(T);
			else
				T = DoubleRoteateWithRight(T);
		}
	}
	if (T) //else 的就是已经在树中存在的了，不需要添加
		T->Height = max(Height(T->Left), Height(T->Right)) + 1;
	return T;
}
//删除元素
BinaryTree DeleteFromTree(TreeElementType X, BinaryTree T)
{
	TreePosition TmpCell;
	if (T == NULL)
		TreeError("Element not found");
	else if (CompareTreeElement(&X, &T->Element) < 0)
		T->Left = DeleteFromTree(X, T->Left);
	else if (CompareTreeElement(&X, &T->Element) > 0)
		T->Right = DeleteFromTree(X, T->Right);
	else if (T->Left && T->Right)
	{
		TmpCell = FindMinOnTree(T->Right);
		T->Element = TmpCell->Element;
		T->Right = DeleteFromTree(T->Element, T->Right);
	}
	else
	{
		TmpCell = T;
		if (T->Left == NULL)
			T = T->Right;
		else if (T->Right == NULL)
			T = T->Left;
		free(TmpCell);
	}
	return T;
}
#endif
#pragma endregion
#elif SPLAY_TREE

#pragma region 伸展树

//左旋转
static TreePosition SingleRotateWithLeft(TreePosition K2)
{
	TreePosition K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;
	return K1;
}
//右旋转
static TreePosition SingleRotateWithRight(TreePosition K1)
{
	TreePosition K2 = K1->Right;
	K1->Right = K2->Left;
	K2->Left = K1;
	return K2;
}

//双旋转
static TreePosition DoubleRoteateWithLeft(TreePosition K3)
{
	K3->Left = SingleRotateWithRight(K3->Left);

	return SingleRotateWithLeft(K3);
}
//双旋转
static TreePosition DoubleRoteateWithRight(TreePosition K3)
{
	K3->Right = SingleRotateWithRight(K3->Right);

	return SingleRotateWithLeft(K3);
}

//---------------------------------------------------------
//初始化
BinaryTree InitializeTree()
{
	if (NullNode == NULL)
	{
		NullNode = MakeTreeNode(NullElem);
		NullNode->Left = NullNode->Right = NullNode;
	}
	return NullNode;
}
//---------------------------------------------------------
//伸展
BinaryTree SplayTheTree(TreeElementType Item, TreePosition P)
{
	TreeNode Header;
	TreePosition LeftTreeMax, RightTreeMin;

	Header.Left = Header.Right = NullNode;
	LeftTreeMax = RightTreeMin = &Header;
	NullNode->Element = Item;

	while (Item != P->Element)
	{
		if (CompareTreeElement(&Item, &P->Element) < 0)
		{
			if (CompareTreeElement(&Item, &P->Left->Element) < 0)
				P = SingleRotateWithLeft(P);
			if (P->Left == NullNode)
				break;
			//Link Right
			RightTreeMin->Left = P;
			RightTreeMin = P;
			P = P->Left;
		}
		else
		{
			if (CompareTreeElement(&Item, &P->Right->Element) < 0)
				P = SingleRotateWithRight(P);
			if (P->Right == NullNode)
				break;
			//Link Left
			LeftTreeMax->Right = P;
			LeftTreeMax = P;
			P = P->Right;
		}
	}
	//Reassemble
	LeftTreeMax->Right = P->Left;
	RightTreeMin->Left = P->Right;
	P->Left = Header.Right;
	P->Right = Header.Left;

	return P;
}
//---------------------------------------------------------
//将元素 X 插入到树T
BinaryTree InsertToTree(TreeElementType Item, BinaryTree T)
{
	static TreePosition NewNode = NULL;
	if (!NewNode)
	{
		NewNode = MakeTreeNode(NullElem);
	}
	NewNode->Element = Item;
	if (T == NullNode)
	{
		NewNode->Left = NewNode->Right = NullNode;
		T = NewNode;
	}
	else
	{
		T = SplayTheTree(Item, T);
		if (CompareTreeElement(&Item, &T->Element) < 0)
		{
			NewNode->Left = T->Left;
			NewNode->Right = T;
			T->Left = NullNode;
			T = NewNode;
		}
		else if (CompareTreeElement(&T->Element, &Item) < 0)
		{
			NewNode->Right = T->Right;
			NewNode->Left = T;
			T->Right = NullNode;
			T = NewNode;
		}
		else
		{
			return T;	//Already in the tree
		}
	}
	NewNode = NULL;		//So next insert will call malloc
	return T;
}
//---------------------------------------------------------
//删除元素
BinaryTree DeleteFromTree(TreeElementType Item, BinaryTree T)
{
	TreePosition NewTree;
	if (T != NullNode)
	{
		T = SplayTheTree(Item, T);
		if (CompareTreeElement(&Item, &T->Element) == 0)
		{
			//Found it
			if (T->Left == NullNode)
				NewTree = T->Right;
			else
			{
				NewTree = T->Left;
				NewTree = SplayTheTree(Item, NewTree);
				NewTree->Right = T->Right;
			}
			DestoryTreeNode(T);
			T = NewTree;
		}
	}
	return T;
}
//--------------------------------------
//查找最小，返回位置
TreePosition FindMinOnTree(BinaryTree T)
{
	if (T == NULL)
		return NULL;
	else if (T->Left == NULL)
		return T;
	else
		return FindMinOnTree(T->Left);
}
//-------------------------------------
//查找最大，返回位置
TreePosition FindMaxOnTree(BinaryTree T)
{
	if (T != NULL)
	{
		while (T->Right != NULL)
		{
			T = T->Right;
		}
	}
	return T;
}
#pragma endregion
#elif REDBLACK_TREE
//初始化
BinaryTree InitializeTree()
{
	if (!NullNode)//== NULL
	{
		NullNode = MakeTreeNode(sizeof(TreeNode));
		if (!NullNode)//==NULL
			TreeFailError("Out of space!!!\n");
		NullNode->Left = NullNode->Right = NullNode;
		NullNode->Color = Black;
		NullNode->Element = NullElem;
	}
	return NullNode;
}
//左旋转
static TreePosition SingleRotateWithLeft(TreePosition K2)
{
	TreePosition K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;
	return K1;
}
//右旋转
static TreePosition SingleRotateWithRight(TreePosition K1)
{
	TreePosition K2 = K1->Right;
	K1->Right = K2->Left;
	K2->Left = K1;
	return K2;
}
//旋转
static TreePosition Rotate(TreeElementType Item, TreePosition Parent)
{
	if (Item < Parent->Element)
	{
		return Parent->Left = Item < Parent->Left->Element ?
			SingleRotateWithLeft(Parent->Left) :
			SingleRotateWithRight(Parent->Left);
	}
	else
	{
		return Parent->Right = Item < Parent->Right->Element ?
			SingleRotateWithLeft(Parent->Right) :
			SingleRotateWithRight(Parent->Right);
	}
}
//------------------------------------------------------------
static void DoPrint(BinaryTree T)
{
	if (T != NullNode)
	{
		DoPrint(T->Left);
		DisplayTreeElement(&T->Element);
		DoPrint(T->Right);
	}
}
void PrintTree(BinaryTree T)
{
	DoPrint(T->Right);
}
//--------------------------------------------------------------
static TreePosition X, P, GP, GGP;
static void HandleReorient(TreeElementType Item, BinaryTree T)
{
	X->Color = Red;//Do the color flip
	X->Left->Color = Black;
	X->Right->Color = Black;
	if (P->Color == Red)//Have to rotate
	{
		GP->Color = Red;
		if (CompareTreeElement(&Item, &GP->Element) != CompareTreeElement(&Item, &P->Element))
		{
			P = Rotate(Item, GP);
		}
		X = Rotate(Item, GGP);
		X->Color = Black;
	}
	T->Right->Color = Black;//Make root black
}
BinaryTree InsertToTree(TreeElementType Item, BinaryTree T)
{
	X = P = GP = T;
	NullNode->Element = Item;
	//Descend down the tree
	while (CompareTreeElement(&X->Element, &Item))//X->Element != Item
	{
		GGP = GP;
		GP = P;
		P = X;
		if (CompareTreeElement(&Item, &X->Element) < 0)
			X = X->Left;
		else
			X = X->Right;
		if (X->Left->Color == Red && X->Right->Color == Red)
			HandleReorient(Item, T);
	}
	if (X != NullNode)
		return NullNode;

	X = MakeTreeNode(Item);
	if (!X)//X == NULL
		TreeFailError("Out of space!!!");
	X->Left = X->Right = NullNode;

	if (Item < P->Element)
		P->Left = X;
	else
		P->Right = X;

	HandleReorient(Item, T);
	return T;
}
#endif // SEARCH_TREE

#pragma region 通用
//--------------------------------------------------
//构造树结点
PtrToTreeNode MakeTreeNode(TreeElementType X)
{
	PtrToTreeNode p = (PtrToTreeNode)calloc(1, sizeof(TreeNode));
	if (p)
		p->Element = X;
	else
		TreeFailError("Alloc Error");
	return p;
}
//销毁树结点
PtrToTreeNode DestroyTreeNode(PtrToTreeNode P)
{
	free(P);
	return NULL;
}
//比较元素大小
int CompareTreeElement(TreeElementType* lElem, TreeElementType* rElem)
{
	if (*lElem > * rElem)
	{
		return 1;
	}
	else if (*lElem < *rElem)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
//--------------------------------------------------
//根据某个位置获取元素
TreeElementType RetrieveFromTreePos(TreePosition P)
{
	return P->Element;
}
//--------------------------------------------------
//显示元素
void DisplayTreeElement(TreeElementType* X)
{
	printf("%d ", *X);
}
//--------------------------------------------------
//输出节点元素
void DisplayTreePos(TreePosition P)
{
	TreeElementType elem = RetrieveFromTreePos(P);
	DisplayTreeElement(&elem);
}
//--------------------------------------------------
//查找树
TreePosition FindElementFromTree(TreeElementType X, BinaryTree T)
{
	if (T == NULL)
		return NULL;
	else if (CompareTreeElement(&X, &T->Element) < 0)
		return FindElementFromTree(X, T->Left);
	else if (CompareTreeElement(&X, &T->Element) > 0)
		return FindElementFromTree(X, T->Right);
	else
		return T;
}
//--------------------------------------------------
//清空树
BinaryTree DestroyTree(BinaryTree T)
{
	if (T != NULL)
	{
		DestroyTree(T->Left);
		DestroyTree(T->Right);
		free(T);
	}
	return NULL;
}
//--------------------------------------------------
#pragma region 遍历

#ifdef NON_RECURSION
#include "stack/stack.h"
#endif // NON_RECURSION
//先序遍历
void PreOrder(BinaryTree root, void(*func)(BinaryTree))
{
	//递归版本
#ifndef NON_RECURSION 
	if (root)
	{
		func(root);
		PreOrder(root->Left, func);
		PreOrder(root->Right, func);
	}
#else
	//非递归版本
	if (TreeIsEmpty(root))
	{
		TreeError("树为空!\n");
		return;
	}
	BinaryTree tmpBinaryTree = root;
	Stack S;
	InitStack(&S);
	while (!TreeIsEmpty(tmpBinaryTree) || !StackIsEmpty(S))
	{
		if (!TreeIsEmpty(tmpBinaryTree))
		{
			func(tmpBinaryTree);
			Push(tmpBinaryTree, &S);
			tmpBinaryTree = tmpBinaryTree->Left;
		}
		else
		{
			tmpBinaryTree = (BinaryTree)Top(S);
			Pop(&S);
			tmpBinaryTree = tmpBinaryTree->Right;
		}
	}
#endif // !NON_RECURSION
}

//中序遍历
void InOrder(BinaryTree root, void(*func)(BinaryTree))
{
	//递归版本
#ifndef NON_RECURSION 
	if (root)
	{
		InOrder(root->Left, func);
		func(root);
		InOrder(root->Right, func);
	}
#else
	//非递归版本
	if (TreeIsEmpty(root))
	{
		TreeError("树为空!\n");
		return;
	}
	BinaryTree tmpBinaryTree = root;
	Stack S;
	InitStack(&S);
	while (!TreeIsEmpty(tmpBinaryTree) || !StackIsEmpty(S))
	{
		if (!TreeIsEmpty(tmpBinaryTree))
		{
			Push(tmpBinaryTree, &S);
			tmpBinaryTree = tmpBinaryTree->Left;
		}
		else
		{
			tmpBinaryTree = (BinaryTree)Top(S);
			func(tmpBinaryTree);
			Pop(&S);
			tmpBinaryTree = tmpBinaryTree->Right;
		}
	}
#endif // !NON_RECURSION
}

//后序遍历
void PostOrder(BinaryTree root, void(*func)(BinaryTree))
{
	//递归版本
#ifndef NON_RECURSION 
	if (root)
	{
		PostOrder(root->Left, func);
		PostOrder(root->Right, func);
		func(root);
	}
#else
	//非递归版本
	if (TreeIsEmpty(root))
	{
		TreeError("树为空!\n");
		return;
	}
	BinaryTree tmpBinaryTree = root;
	Stack S;
	InitStack(&S);
	while (!TreeIsEmpty(tmpBinaryTree) || !StackIsEmpty(S))
	{
		if (!TreeIsEmpty(tmpBinaryTree))
		{
			tmpBinaryTree->VisitCount = 1;
			Push(tmpBinaryTree, &S);
			tmpBinaryTree = tmpBinaryTree->Left;
		}
		else
		{
			tmpBinaryTree = (BinaryTree)Top(S);
			Pop(&S);
			if (tmpBinaryTree->VisitCount == 2)
			{
				func(tmpBinaryTree);
				tmpBinaryTree = NULL;
			}
			else
			{
				++tmpBinaryTree->VisitCount;
			    Push(tmpBinaryTree, &S);
				tmpBinaryTree = tmpBinaryTree->Right;
			}
		}
	}
#endif // !NON_RECURSION
}

//层序遍历
#ifdef SEQUENCE_ORDER
#include "queue/queue.h"
void SeqOrder(BinaryTree root, void(*func)(BinaryTree))
{
	if (TreeIsEmpty(root))
	{
		TreeError("树为空!\n");
		return;
	}

	Queue Q;
	InitQueue(&Q);
	EnQueue(root, &Q);					 //根结点先入队
	BinaryTree tmpBinaryTree = root;

	while (!QueueIsEmpty(Q))				 //队列不空
	{
		tmpBinaryTree = FirstOfQueue(Q);			 //获取队头元素
		DeQueue(&Q);						 //对头离队
		func(tmpBinaryTree);						 //访问当前树结点

		if (!TreeIsEmpty(tmpBinaryTree->Left))	 //左子树是否为空
		{
			EnQueue(tmpBinaryTree->Left, &Q);   //不为空入队
		}
		if (!TreeIsEmpty(tmpBinaryTree->Right))	 //右子树是否为空
		{
			EnQueue(tmpBinaryTree->Right, &Q);  //不为空入队
		}
	}
	DestroyQueue(&Q);
}
#endif // USE_SEQUENCE_ORDER
#pragma endregion

//---------------------------------------------------------
//判断树是否为空
_Bool TreeIsEmpty(BinaryTree tree)
{
	return tree == NullNode || tree == NULL;
}
//--------------------------------------------------------
//判断位置是否为叶子
_Bool IsLeaf(TreePosition P)
{
	//if ((P->Left != NullNode && P->Left != NULL) && (P->Right != NullNode && P->Right != NULL))
	if ((P->Left != NullNode) && (P->Right != NullNode))
		return true;
	else
		return false;
}
//--------------------------------------------------------
//计算叶子结点个数
static void CountLeafBasic(BinaryTree root, int* count)
{
	if (root)
	{
		if (!root->Left && !root->Right)
			++* count;
		CountLeafBasic(root->Left, count);
		CountLeafBasic(root->Right, count);
	}
}
int CountLeaf(BinaryTree root)
{
	int count = 0;
	CountLeafBasic(root, &count);
	return count;
}
//--------------------------------------------------------
//计算一棵树的深度
static int CountDepthBasic(BinaryTree root, int count)
{
	if (TreeIsEmpty(root))
		return count;
	else
	{
		++count;
		int left = CountDepthBasic(root->Left, count);
		int right = CountDepthBasic(root->Right, count);
		return left > right ? left : right;
	}
}
int CountDepth(BinaryTree root)
{
	return CountDepthBasic(root, 0);
}
//--------------------------------------------------------
//拷贝一棵树
BinaryTree CopyTree(BinaryTree src_tree)
{
	if (src_tree)
	{
		PtrToTreeNode pLeft = NULL, pRight = NULL;

		if (src_tree->Left)
			pLeft = CopyTree(src_tree->Left);
		if (src_tree->Right)
			pRight = CopyTree(src_tree->Right);

		PtrToTreeNode pNewNode = MakeTreeNode(NullElem);
		if (pNewNode)
		{
			pNewNode->Element = src_tree->Element;
			pNewNode->Left = pLeft;
			pNewNode->Right = pRight;
		}
		else
		{
			TreeFailError("Alloc Error");
		}
		return pNewNode;
	}
	else
		return NULL;
}

//--------------------------------------------------------
//报错
void TreeError(const char* pMsg)
{
	perror(pMsg);
}
//--------------------------------------------------------
//失败处理
void TreeFailError(const char* errMsg)
{
	perror(errMsg);
	exit(-1);
}
#pragma endregion