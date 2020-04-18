#ifndef __BTREE_H_
#define __BTREE_H_
//-------------------------------------------------------
//						搜索树结构定义
//元素类型
typedef int BTreeElementType;
//节点位置
typedef struct BTreeNode* BTreePosition;
//搜索树类型
//typedef struct BTreeNode* BTree;
//
typedef struct BTreeArrayNode* BTreeArray;


struct BTreeNode
{
	int Number;
	BTreeElementType Element;			//存储数据
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
//先序遍历
void BTree_PreOrder(BTree root, void(*func)(BTreePosition));
//后序遍历
void BTree_PostOrder(BTree root, void(*func)(BTreePosition));
//层序遍历
void BTree_SeqOrder(BTree root, void(*func)(BTreePosition));
//计算树的最大深度
int BTree_MaxDepth(BTree tree);
#endif // !__BTREE_H_
