#ifndef __BTREE_H_
#define __BTREE_H_
//-------------------------------------------------------
//						�������ṹ����
//Ԫ������
typedef int BTreeElementType;
//�ڵ�λ��
typedef struct BTreeNode* BTreePosition;
//����������
//typedef struct BTreeNode* BTree;
//
typedef struct BTreeArrayNode* BTreeArray;


struct BTreeNode
{
	int Number;
	BTreeElementType Element;			//�洢����
	BTreePosition* Children;
};

typedef struct BTree
{
	BTreePosition root;
	BTreePosition* positions;
	int nPosition;
}BTree;
struct BTreeArrayNode
{
	int data;
	int parent;
};

//
void ShowNodes(BTree tree);
//
void ShowDegrees(BTree tree);
//
int BTree_SetCountOfNode(int n);
//
int	BTree_GetCountOfNode();
//
int BTree_MakeTree(BTree* pTree, BTreeArray tree_array, int n);
//
int BTree_Destroy(BTree* pTree);
//�������
void BTree_PreOrder(BTree root, void(*func)(BTreePosition));
//�������
void BTree_PostOrder(BTree root, void(*func)(BTreePosition));
//�������
void BTree_SeqOrder(BTree root, void(*func)(BTreePosition));
//��������������
int BTree_MaxDepth(BTree tree);
#endif // !__BTREE_H_
