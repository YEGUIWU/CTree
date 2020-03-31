#ifndef _YE_GUI_WU_TREE_H_
#define _YE_GUI_WU_TREE_H_
#include <stdio.h>  //��׼�������
#include <stdlib.h> //�ڴ�����ͷ�
#include <memory.h> //�ڴ����
#include <stdbool.h>
//ʹ��������
#define SEARCH_TREE 1
//ʹ��ƽ��������
//#define AVL_TREE 1
//ʹ����չ��
#define SPLAY_TREE 1
//ʹ�ú����
//#define REDBLACK_TREE 1

//�����ǵݹ����
#define NON_RECURSION 1
//ʹ�ò������
#define USE_SEQUENCE_ORDER 1

//-------------------------------------------------------
//						�������ṹ����

//Ԫ������
//typedef int TreeElementType;
typedef int TreeElementType;
typedef struct TreeNode TreeNode;

//------------------------------------------------------
//						ͨ�ñ���
//�������ڵ�λ��
typedef TreeNode* TreePosition;
//����������
typedef struct TreeNode* Tree;

//-------------------------------------------------------
//						����������

//----------------------------------------------
//						������
#ifdef SEARCH_TREE
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
TreePosition FindMinOnTree(Tree T);
//������󣬷���λ��
TreePosition FindMaxOnTree(Tree T);
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
TreePosition FindMinOnTree(Tree T);
//�������
TreePosition FindMaxOnTree(Tree T);
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
Tree SplayTheTree(TreeElementType Item, TreePosition P);
//������С������λ��
TreePosition FindMinOnTree(Tree T);
//������󣬷���λ��
TreePosition FindMaxOnTree(Tree T);

#elif REDBLACK_TREE
typedef enum ColorType {Red, Black} ColorType;
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
void PrintTree(RedBlackTree T);
#endif




//-------------------------------------------------------
//						ͨ�����ӿ�����
//
Tree InitializeTree();
//��Ԫ�� X ���뵽��T
Tree InsertToTree(TreeElementType X, Tree T);
//��Ԫ�� X ����T��ɾ��
Tree DeleteFromTree(TreeElementType X, Tree T);

//------------------------------------------------------
//							ͨ��

//�Ƚ�Ԫ�ش�С
int CompareTreeElement(TreeElementType* lElem, TreeElementType* rElem);
//���Ԫ��
void DisplayTreeElement(TreeElementType* elem);
//����ڵ�Ԫ��
void DisplayTreePos(TreePosition P);
//����Ԫ�أ�����λ��
TreePosition FindElementFromTree(TreeElementType X, Tree T);
//����ĳ��λ�û�ȡԪ��
TreeElementType RetrieveFromTreePos(TreePosition P);
//�����
Tree DestroyTree(Tree T);
//����һ����
Tree CopyTree(Tree src_tree);

//------------------------------------------------------
//�������
void InOrder(Tree root, void(*func)(Tree));
//�������
void PreOrder(Tree root, void(*func)(Tree));
//�������
void PostOrder(Tree root, void(*func)(Tree));
#ifdef USE_SEQUENCE_ORDER
void SeqOrder(Tree root, void(*func)(Tree));
#define SEQUENCE_ORDER 1
#endif // USE_SEQUENCE_ORDER

//---------------------------------
_Bool TreeIsEmpty(Tree tree);
//�ж�λ���Ƿ�ΪҶ��
_Bool IsLeaf(TreePosition P);
//����Ҷ�ӽ��
int CountLeaf(Tree root);
//����һ���������
int CountDepth(Tree root);
#endif // _Tree_H
