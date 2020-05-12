#include "Tree/BTree.h"
#include "Tree/BinaryTree.h"
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#define N 10
//⑴ 树的建立：以(结点编号, 结点数据，父结点编号)的形式从键盘输入一棵n叉树（n≥3），根结点的父结点编号为 - 1，将树按双亲表示法存储在一位数组中。
//⑵ 树的输出：将所建立的按双亲表示法存储的树转换形成按孩子—兄弟链表法的形式保存并输出。
//⑶ 树的先序遍历：按先序遍历方式对树进行遍历，输出对应的遍历序列。
//⑷ 树的后序遍历：按后序遍历方式对树进行遍历，输出对应的遍历序列。
//⑸ 树的层次遍历：按层次遍历方式对树进行遍历，输出对应的遍历序列。
//⑹ 树中结点度的统计：分别统计树中度为0、1、2…的结点数目。

void DisplayBTreeNode(BTreePosition pos);
void DisplayBinaryTreeNode(TreePosition pos);
BTreeArray MakeData();

int demo()
{
    BTree_SetCountOfNode(3);
    BTreeArray pArray = MakeData();
    BTree tree;
    BinaryTree binary_tree;
    BTree_MakeTree(&tree, pArray, N);
    BinaryTree_MakeTree(&binary_tree, (BinaryTreeArray)pArray, N);
    //
    PreOrder(binary_tree, DisplayBinaryTreeNode);
    //先序遍历
    BTree_PreOrder(tree, DisplayBTreeNode);
    //后序遍历
    BTree_PostOrder(tree, DisplayBTreeNode);
    //打印树的深度
    printf("%d\n", BTree_MaxDepth(tree));
    ShowNodes(tree);
    ShowDegrees(tree);

    //--------------------------------------
    BTree_SeqOrder(tree, DisplayBTreeNode);


    //--------------------------------------
    free(pArray);
    BTree_Destroy(&tree);
    binary_tree = DestroyTree(binary_tree);
    return 0;
}
//--------------------------------------------------------
//打印头
void static inline Output_Header(const char* head)
{
    printf("[%s]: ", head);
}
//--------------------------------------------------------
//打印分隔线
void static inline Output_Cutoff_Rule()
{
    printf("\n------------------------------------------------------------\n");
}
//--------------------------------------------------------
//打印提示
static void inline Tips()
{
    system("cls");
    Output_Cutoff_Rule();
    printf("[输入0] 当前双亲表\n");
    printf("[输入1] 设置n叉树\n");
    printf("[输入2] 输入双亲表\n");
    printf("[输入3] 兄弟链表法的形式保存并输出\n");
    printf("[输入4] 先序遍历\n");
    printf("[输入5] 后序遍历\n");
    printf("[输入6] 层序遍历\n");
    printf("[输入7] 树中结点度的统计\n");
    printf("[输入8] 使用默认双亲表\n");
    printf("[输入9] 退出\n");
    Output_Cutoff_Rule();
}
int main()
{
	char choice;//用户选择
	char buf[BUFSIZ];
    BTreeArray pArray = NULL;
    BTree tree;
    BinaryTree binary_tree = InitializeTree();
    int n = N;
   
	while (true)
	{
		Tips();
		choice = _getch();
		switch (choice)
		{
		case '0':
            printf("\n表结构如下\n");
            printf("----------------------\n");
            printf("| 编号 | 数据 | 双亲 |\n");
            if (pArray)
            {
                for (int i = 0; i < n; ++i)
                {
                    printf("| %4d | %4c | %4d |\n", i, pArray[i].data, pArray[i].parent);
                }
            }
            system("pause");
			break;
		case '1':
            Output_Header("请输入n (n > 2)");
            fgets(buf, BUFSIZ, stdin);
            BTree_SetCountOfNode(atoi(buf));
			break;
		case '2':
            if (pArray)
            {
                free(pArray);
                if (tree.root)
                {
                    BTree_Destroy(&tree);
                }
            }
            Output_Header("节点数n (n > 0)");
            fgets(buf, BUFSIZ, stdin);
            n = atoi(buf);

            pArray = malloc(sizeof(struct BTreeArrayNode) * n);
            for (int i = 0; i < n; ++i)
            {
                printf("---第%d个结点----\n", i + 1);
                Output_Header("data");
                pArray[i].data = getchar(); getchar();
                Output_Header("parent");
                fgets(buf, BUFSIZ, stdin);
                pArray[i].parent = atoi(buf);
            }

            BinaryTree_MakeTree(&binary_tree, (BinaryTreeArray)pArray, n);
            BTree_MakeTree(&tree, pArray, n);
			break;
		case '3':
            if (TreeIsEmpty(binary_tree))
            {
                BinaryTree_MakeTree(&binary_tree, (BinaryTreeArray)pArray, n); 
            }   
            PreOrder(binary_tree, DisplayBinaryTreeNode);
			system("pause");
			break;
		case '4'://先序遍历
            BTree_PreOrder(tree, DisplayBTreeNode);
            system("pause");
			break;
		case '5'://后序遍历
            BTree_PostOrder(tree, DisplayBTreeNode);
            system("pause");
			break;
		case '6'://层序遍历
            BTree_SeqOrder(tree, DisplayBTreeNode);
            system("pause");
			break;
		case '7'://统计结点度数
            ShowDegrees(tree);
            system("pause");
			break;
		case '8':
            if (pArray)
            {
                free(pArray);
                if (tree.root)
                {
                    BTree_Destroy(&tree);
                }
            }
            pArray = MakeData();
            BinaryTree_MakeTree(&binary_tree, (BinaryTreeArray)pArray, n);
            BTree_MakeTree(&tree, pArray, n);
            n = N;
            break;
		case '9':
            free(pArray);
            BTree_Destroy(&tree);
            binary_tree = DestroyTree(binary_tree);
			exit(EXIT_SUCCESS);
			break;
		}
	}
}

void DisplayBTreeNode(BTreePosition pos)
{
    //printf("%d %c\n", pos->Number, pos->Element);
    printf("%c\n", pos->Element);
}
void DisplayBinaryTreeNode(TreePosition pos)
{
    printf("%c\n", pos->Element);
}
BTreeArray MakeData()
{
    BTreeArray pArray = malloc(sizeof(struct BTreeArrayNode) * N);
    pArray[0].data = 'R';
    for (int i = 1; i < 10; ++i)
    {
        pArray[i].data = 'A' + i - 1;
    }
    pArray[0].parent = -1;
    pArray[1].parent = 0;
    pArray[2].parent = 0;
    pArray[3].parent = 0;
    pArray[4].parent = 1;
    pArray[5].parent = 1;
    pArray[6].parent = 3;
    pArray[7].parent = 6;
    pArray[8].parent = 6;
    pArray[9].parent = 6;
    return pArray;
}