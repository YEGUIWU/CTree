#ifndef _YE_GUI_WU_TREE_H_
#define _YE_GUI_WU_TREE_H_
#include <stdio.h>  //��׼�������
#include <stdlib.h> //�ڴ�����ͷ�
#include <memory.h> //�ڴ����
#include <stdbool.h>

//-------------------------------------------------------
//						Ԥ�����趨
//ʹ�ö���������
#define SEARCH_TREE 1
//ʹ��ƽ�����������
//#define AVL_TREE 1
//ʹ����չ��
//#define SPLAY_TREE 1
//ʹ�ú����
//#define REDBLACK_TREE 1

//ʹ�ò������
#define USE_SEQUENCE_ORDER 1
//�����ǵݹ����
#define NON_RECURSION 1




//-------------------------------------------------------
//						�������ṹ����
//Ԫ������
typedef int TreeElementType;
//��������
typedef struct TreeNode TreeNode;
//�������ڵ�λ��
typedef TreeNode* TreePosition;
//����������
typedef struct TreeNode* BinaryTree;
#ifdef  SEARCH_TREE
//-------------------------------------------------------
//						����������
struct TreeNode
{
	TreeElementType Element;			//�洢����
	struct TreeNode* Left;              //������
	struct TreeNode* Right;             //������
#ifdef NON_RECURSION
	long VisitCount;
#endif // NON_RECURSION

};

//������С������λ��
TreePosition FindMinOnTree(BinaryTree T);
//������󣬷���λ��
TreePosition FindMaxOnTree(BinaryTree T);
#define SEARCH_TREE_COME_TRUE

//---------------------------------------------
//					ƽ��������
#elif AVL_TREE
struct TreeNode
{
	TreeElementType Element;			//�洢����
	struct TreeNode* Left;              //������
	struct TreeNode* Right;             //������
	int Height;							//�߶�
#ifdef NON_RECURSION
	long VisitCount;
#endif // NON_RECURSION
};

//������С
TreePosition FindMinOnTree(BinaryTree T);
//�������
TreePosition FindMaxOnTree(BinaryTree T);
#define AVL_TREE_COME_TRUE
#elif SPLAY_TREE
struct TreeNode
{
	TreeElementType Element;			//�洢����
	struct TreeNode* Left;              //������
	struct TreeNode* Right;             //������
#ifdef NON_RECURSION
	long VisitCount;
#endif // NON_RECURSION
};
BinaryTree SplayTheTree(TreeElementType Item, TreePosition P);
//������С������λ��
TreePosition FindMinOnTree(BinaryTree T);
//������󣬷���λ��
TreePosition FindMaxOnTree(BinaryTree T);

#elif REDBLACK_TREE
typedef enum ColorType { Red, Black } ColorType;
struct TreeNode
{
	TreeElementType Element;
	struct TreeNode* Left;
	struct TreeNode* Right;
	ColorType Color;
#ifdef NON_RECURSION
	long VisitCount;
#endif // NON_RECURSION
};
void PrintTree(BinaryTree T);
#endif




//-------------------------------------------------------
//						ͨ�����ӿ�����
//��ʼ����
BinaryTree InitializeTree();
//��Ԫ�� X ���뵽��T
BinaryTree InsertToTree(TreeElementType X, BinaryTree T);
//��Ԫ�� X ����T��ɾ��
BinaryTree DeleteFromTree(TreeElementType X, BinaryTree T);

//------------------------------------------------------
//							ͨ��

//�Ƚ�Ԫ�ش�С
int CompareTreeElement(TreeElementType* lElem, TreeElementType* rElem);
//���Ԫ��
void DisplayTreeElement(TreeElementType* elem);
//����ڵ�Ԫ��
void DisplayTreePos(TreePosition P);
//����Ԫ�أ�����λ��
TreePosition FindElementFromTree(TreeElementType X, BinaryTree T);
//����ĳ��λ�û�ȡԪ��
TreeElementType RetrieveFromTreePos(TreePosition P);
//�����
BinaryTree DestroyTree(BinaryTree T);
//����һ����
BinaryTree CopyTree(BinaryTree src_tree);

//------------------------------------------------------
//�������
void InOrder(BinaryTree root, void(*func)(BinaryTree));
//�������
void PreOrder(BinaryTree root, void(*func)(BinaryTree));
//�������
void PostOrder(BinaryTree root, void(*func)(BinaryTree));
#ifdef USE_SEQUENCE_ORDER
void SeqOrder(BinaryTree root, void(*func)(BinaryTree));
#define SEQUENCE_ORDER 1
#endif // USE_SEQUENCE_ORDER

//---------------------------------
_Bool TreeIsEmpty(BinaryTree tree);
//�ж�λ���Ƿ�ΪҶ��
_Bool IsLeaf(TreePosition P);
//����Ҷ�ӽ��
int CountLeaf(BinaryTree root);
//����һ���������
int CountDepth(BinaryTree root);


#endif // _Tree_H
