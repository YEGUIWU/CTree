#ifndef _YE_GUI_WU_TREE_H_
#define _YE_GUI_WU_TREE_H_
#include <stdio.h>  //标准输入输出
#include <stdlib.h> //内存分配释放
#include <memory.h> //内存操作
#include <stdbool.h>
//使用搜索树
#define SEARCH_TREE 1
//使用平衡搜索树
//#define AVL_TREE 1
//使用伸展树
#define SPLAY_TREE 1
//使用红黑树
//#define REDBLACK_TREE 1

//开启非递归遍历
#define NON_RECURSION 1
//使用层序遍历
#define USE_SEQUENCE_ORDER 1

//-------------------------------------------------------
//						搜索树结构定义

//元素类型
//typedef int TreeElementType;
typedef int TreeElementType;
typedef struct TreeNode TreeNode;

//------------------------------------------------------
//						通用别名
//二叉树节点位置
typedef TreeNode* TreePosition;
//搜索树类型
typedef struct TreeNode* Tree;

//-------------------------------------------------------
//						搜索树历程

//----------------------------------------------
//						搜索树
#ifdef SEARCH_TREE
struct TreeNode
{
	TreeElementType Element;			//存储数据
	struct TreeNode* Left;              //左子树
	struct TreeNode* Right;             //右子树
#ifdef NON_RECURSION
	long VisitCount;
#endif // NON_RECURSION

};

//查找最小，返回位置
TreePosition FindMinOnTree(Tree T);
//查找最大，返回位置
TreePosition FindMaxOnTree(Tree T);
#define SEARCH_TREE_COME_TRUE

//---------------------------------------------
//					平衡搜索树
#elif AVL_TREE
struct TreeNode
{
	TreeElementType Element;			//存储数据
	struct TreeNode* Left;              //左子树
	struct TreeNode* Right;             //右子树
	int Height;							//高度
#ifdef NON_RECURSION
	long VisitCount;
#endif // NON_RECURSION
};

//查找最小
TreePosition FindMinOnTree(Tree T);
//查找最大
TreePosition FindMaxOnTree(Tree T);
#define AVL_TREE_COME_TRUE
#elif SPLAY_TREE
struct TreeNode
{
	TreeElementType Element;			//存储数据
	struct TreeNode* Left;              //左子树
	struct TreeNode* Right;             //右子树
#ifdef NON_RECURSION
	long VisitCount;
#endif // NON_RECURSION
};
Tree SplayTheTree(TreeElementType Item, TreePosition P);
//查找最小，返回位置
TreePosition FindMinOnTree(Tree T);
//查找最大，返回位置
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
//						通用树接口历程
//
Tree InitializeTree();
//将元素 X 插入到树T
Tree InsertToTree(TreeElementType X, Tree T);
//将元素 X 从树T中删除
Tree DeleteFromTree(TreeElementType X, Tree T);

//------------------------------------------------------
//							通用

//比较元素大小
int CompareTreeElement(TreeElementType* lElem, TreeElementType* rElem);
//输出元素
void DisplayTreeElement(TreeElementType* elem);
//输出节点元素
void DisplayTreePos(TreePosition P);
//查找元素，返回位置
TreePosition FindElementFromTree(TreeElementType X, Tree T);
//根据某个位置获取元素
TreeElementType RetrieveFromTreePos(TreePosition P);
//清空树
Tree DestroyTree(Tree T);
//拷贝一棵树
Tree CopyTree(Tree src_tree);

//------------------------------------------------------
//中序遍历
void InOrder(Tree root, void(*func)(Tree));
//先序遍历
void PreOrder(Tree root, void(*func)(Tree));
//后序遍历
void PostOrder(Tree root, void(*func)(Tree));
#ifdef USE_SEQUENCE_ORDER
void SeqOrder(Tree root, void(*func)(Tree));
#define SEQUENCE_ORDER 1
#endif // USE_SEQUENCE_ORDER

//---------------------------------
_Bool TreeIsEmpty(Tree tree);
//判断位置是否为叶子
_Bool IsLeaf(TreePosition P);
//计算叶子结点
int CountLeaf(Tree root);
//计算一棵树的深度
int CountDepth(Tree root);
#endif // _Tree_H
