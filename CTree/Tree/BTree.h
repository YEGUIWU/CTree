#ifndef __BTREE_H_
//-------------------------------------------------------
//						�������ṹ����
//Ԫ������
typedef int BTreeElementType;
//��������
typedef struct BTreeNode BTreeNode;
//�������ڵ�λ��
typedef BTreeNode* BTreePosition;
//����������
typedef struct BTreeNode* BTree;
struct BTreeNode
{
	int Number;
	BTreeElementType Element;			//�洢����
	BTreePosition* Children;
};

int SetCountOfNode(int n);
int	 GetCountOfNode();
//��ʼ����
BTree BTree_Initialize();
//��Ԫ�� X ���뵽��T
BTree BTree_InsertTo(BTreeElementType X, int father, int self, BTree T);

//�������
void BTree_PreOrder(BTree root, void(*func)(BTree));
//�������
void BTree_PostOrder(BTree root, void(*func)(BTree));
//�������
void BTree_SeqOrder(BTree root, void(*func)(BTree));
#endif // !__BTREE_H_
