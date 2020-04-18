#include "BinaryTree.h"

static const TreeElementType NullElem = 0;

static TreePosition NullNode = NULL;

typedef TreeNode* PtrToTreeNode;
//-------------------------------
//������
void TreeError(const char* errMsg);
//ʧ�ܴ���
void TreeFailError(const char* errMsg);
//������
PtrToTreeNode MakeTreeNode(TreeElementType X);
//���������
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
		pTmp = ptrs[pArray[i].parent];//�Ұְ�λ��
		if (!pTmp->Left)//�ְֻ�û�к��ӣ������ְֵĺ���
		{
			pTmp->Left = ptrs[i];
		}
		else//�ְ��к����ˣ��͸��ְֵĺ��ӵ�����
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
#pragma region ������
//--------------------------------------------------
//��ʼ��
BinaryTree InitializeTree()
{
	return NullNode;
}
//--------------------------------------------------
//������С
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
//�������
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
//����Ԫ��
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
//ɾ��Ԫ��
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
#pragma region ƽ����
#ifdef  AVL_TREE_COME_TRUE
//��ȡ��
static int Height(TreePosition P)
{
	if (P == NULL)
		return -1;
	else
		return P->Height;
}

//����ת
static TreePosition SingleRotateWithLeft(TreePosition K2)
{
	TreePosition K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;

	K2->Height = max(Height(K2->Left), Height(K2->Right)) + 1;
	K1->Height = max(Height(K1->Left), K2->Height) + 1;
	return K1;
}
//����ת
static TreePosition SingleRotateWithRight(TreePosition K1)
{
	TreePosition K2 = K1->Right;
	K1->Right = K2->Left;
	K2->Left = K1;

	K1->Height = max(Height(K1->Left), Height(K1->Right)) + 1;
	K2->Height = max(Height(K2->Left), K1->Height) + 1;
	return K2;
}

//˫��ת
static TreePosition DoubleRoteateWithLeft(TreePosition K3)
{
	K3->Left = SingleRotateWithRight(K3->Left);

	return SingleRotateWithLeft(K3);
}
//˫��ת
static TreePosition DoubleRoteateWithRight(TreePosition K3)
{
	K3->Right = SingleRotateWithRight(K3->Right);

	return SingleRotateWithLeft(K3);
}
//��ʼ��
BinaryTree InitializeTree()
{
	return NullNode;
}
//������С
TreePosition FindMinOnTree(BinaryTree T)
{
	if (T == NULL)
		return NULL;
	else if (T->Left == NULL)
		return T;
	else
		return FindMinOnTree(T->Left);
}
//�������
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
//����Ԫ��
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
	if (T) //else �ľ����Ѿ������д��ڵ��ˣ�����Ҫ���
		T->Height = max(Height(T->Left), Height(T->Right)) + 1;
	return T;
}
//ɾ��Ԫ��
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

#pragma region ��չ��

//����ת
static TreePosition SingleRotateWithLeft(TreePosition K2)
{
	TreePosition K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;
	return K1;
}
//����ת
static TreePosition SingleRotateWithRight(TreePosition K1)
{
	TreePosition K2 = K1->Right;
	K1->Right = K2->Left;
	K2->Left = K1;
	return K2;
}

//˫��ת
static TreePosition DoubleRoteateWithLeft(TreePosition K3)
{
	K3->Left = SingleRotateWithRight(K3->Left);

	return SingleRotateWithLeft(K3);
}
//˫��ת
static TreePosition DoubleRoteateWithRight(TreePosition K3)
{
	K3->Right = SingleRotateWithRight(K3->Right);

	return SingleRotateWithLeft(K3);
}

//---------------------------------------------------------
//��ʼ��
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
//��չ
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
//��Ԫ�� X ���뵽��T
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
//ɾ��Ԫ��
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
//������С������λ��
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
//������󣬷���λ��
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
//��ʼ��
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
//����ת
static TreePosition SingleRotateWithLeft(TreePosition K2)
{
	TreePosition K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;
	return K1;
}
//����ת
static TreePosition SingleRotateWithRight(TreePosition K1)
{
	TreePosition K2 = K1->Right;
	K1->Right = K2->Left;
	K2->Left = K1;
	return K2;
}
//��ת
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

#pragma region ͨ��
//--------------------------------------------------
//���������
PtrToTreeNode MakeTreeNode(TreeElementType X)
{
	PtrToTreeNode p = (PtrToTreeNode)calloc(1, sizeof(TreeNode));
	if (p)
		p->Element = X;
	else
		TreeFailError("Alloc Error");
	return p;
}
//���������
PtrToTreeNode DestroyTreeNode(PtrToTreeNode P)
{
	free(P);
	return NULL;
}
//�Ƚ�Ԫ�ش�С
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
//����ĳ��λ�û�ȡԪ��
TreeElementType RetrieveFromTreePos(TreePosition P)
{
	return P->Element;
}
//--------------------------------------------------
//��ʾԪ��
void DisplayTreeElement(TreeElementType* X)
{
	printf("%d ", *X);
}
//--------------------------------------------------
//����ڵ�Ԫ��
void DisplayTreePos(TreePosition P)
{
	TreeElementType elem = RetrieveFromTreePos(P);
	DisplayTreeElement(&elem);
}
//--------------------------------------------------
//������
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
//�����
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
#pragma region ����

#ifdef NON_RECURSION
#include "stack/stack.h"
#endif // NON_RECURSION
//�������
void PreOrder(BinaryTree root, void(*func)(BinaryTree))
{
	//�ݹ�汾
#ifndef NON_RECURSION 
	if (root)
	{
		func(root);
		PreOrder(root->Left, func);
		PreOrder(root->Right, func);
	}
#else
	//�ǵݹ�汾
	if (TreeIsEmpty(root))
	{
		TreeError("��Ϊ��!\n");
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

//�������
void InOrder(BinaryTree root, void(*func)(BinaryTree))
{
	//�ݹ�汾
#ifndef NON_RECURSION 
	if (root)
	{
		InOrder(root->Left, func);
		func(root);
		InOrder(root->Right, func);
	}
#else
	//�ǵݹ�汾
	if (TreeIsEmpty(root))
	{
		TreeError("��Ϊ��!\n");
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

//�������
void PostOrder(BinaryTree root, void(*func)(BinaryTree))
{
	//�ݹ�汾
#ifndef NON_RECURSION 
	if (root)
	{
		PostOrder(root->Left, func);
		PostOrder(root->Right, func);
		func(root);
	}
#else
	//�ǵݹ�汾
	if (TreeIsEmpty(root))
	{
		TreeError("��Ϊ��!\n");
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

//�������
#ifdef SEQUENCE_ORDER
#include "queue/queue.h"
void SeqOrder(BinaryTree root, void(*func)(BinaryTree))
{
	if (TreeIsEmpty(root))
	{
		TreeError("��Ϊ��!\n");
		return;
	}

	Queue Q;
	InitQueue(&Q);
	EnQueue(root, &Q);					 //����������
	BinaryTree tmpBinaryTree = root;

	while (!QueueIsEmpty(Q))				 //���в���
	{
		tmpBinaryTree = FirstOfQueue(Q);			 //��ȡ��ͷԪ��
		DeQueue(&Q);						 //��ͷ���
		func(tmpBinaryTree);						 //���ʵ�ǰ�����

		if (!TreeIsEmpty(tmpBinaryTree->Left))	 //�������Ƿ�Ϊ��
		{
			EnQueue(tmpBinaryTree->Left, &Q);   //��Ϊ�����
		}
		if (!TreeIsEmpty(tmpBinaryTree->Right))	 //�������Ƿ�Ϊ��
		{
			EnQueue(tmpBinaryTree->Right, &Q);  //��Ϊ�����
		}
	}
	DestroyQueue(&Q);
}
#endif // USE_SEQUENCE_ORDER
#pragma endregion

//---------------------------------------------------------
//�ж����Ƿ�Ϊ��
_Bool TreeIsEmpty(BinaryTree tree)
{
	return tree == NullNode || tree == NULL;
}
//--------------------------------------------------------
//�ж�λ���Ƿ�ΪҶ��
_Bool IsLeaf(TreePosition P)
{
	//if ((P->Left != NullNode && P->Left != NULL) && (P->Right != NullNode && P->Right != NULL))
	if ((P->Left != NullNode) && (P->Right != NullNode))
		return true;
	else
		return false;
}
//--------------------------------------------------------
//����Ҷ�ӽ�����
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
//����һ���������
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
//����һ����
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
//����
void TreeError(const char* pMsg)
{
	perror(pMsg);
}
//--------------------------------------------------------
//ʧ�ܴ���
void TreeFailError(const char* errMsg)
{
	perror(errMsg);
	exit(-1);
}
#pragma endregion