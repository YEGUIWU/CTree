#ifndef __BTREE_H_
//-------------------------------------------------------
//						搜索树结构定义
//元素类型
typedef int BTreeElementType;
//树结点别名
typedef struct BTreeNode BTreeNode;
//二叉树节点位置
typedef BTreeNode* BTreePosition;
//搜索树类型
typedef struct BTreeNode* BTree;
struct BTreeNode
{
	int Number;
	BTreeElementType Element;			//存储数据
	BTreePosition* Children;
};

int SetCountOfNode(int n);
int	 GetCountOfNode();
//初始化树
BTree BTree_Initialize();
//将元素 X 插入到树T
BTree BTree_InsertTo(BTreeElementType X, int father, int self, BTree T);

//先序遍历
void BTree_PreOrder(BTree root, void(*func)(BTree));
//后序遍历
void BTree_PostOrder(BTree root, void(*func)(BTree));
//层序遍历
void BTree_SeqOrder(BTree root, void(*func)(BTree));
#endif // !__BTREE_H_
