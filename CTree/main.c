#include "Tree/BTree.h"
#include "Tree/BinaryTree.h"
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#define N 10
//�� ���Ľ�������(�����, ������ݣ��������)����ʽ�Ӽ�������һ��n������n��3���������ĸ������Ϊ - 1��������˫�ױ�ʾ���洢��һλ�����С�
//�� ������������������İ�˫�ױ�ʾ���洢����ת���γɰ����ӡ��ֵ���������ʽ���沢�����
//�� ������������������������ʽ�������б����������Ӧ�ı������С�
//�� ���ĺ�������������������ʽ�������б����������Ӧ�ı������С�
//�� ���Ĳ�α���������α�����ʽ�������б����������Ӧ�ı������С�
//�� ���н��ȵ�ͳ�ƣ��ֱ�ͳ�����ж�Ϊ0��1��2���Ľ����Ŀ��

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
    //�������
    BTree_PreOrder(tree, DisplayBTreeNode);
    //�������
    BTree_PostOrder(tree, DisplayBTreeNode);
    //��ӡ�������
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
//��ӡͷ
void static inline Output_Header(const char* head)
{
    printf("[%s]: ", head);
}
//--------------------------------------------------------
//��ӡ�ָ���
void static inline Output_Cutoff_Rule()
{
    printf("\n------------------------------------------------------------\n");
}
//--------------------------------------------------------
//��ӡ��ʾ
static void inline Tips()
{
    system("cls");
    Output_Cutoff_Rule();
    printf("[����0] ��ǰ˫�ױ�\n");
    printf("[����1] ����n����\n");
    printf("[����2] ����˫�ױ�\n");
    printf("[����3] �ֵ���������ʽ���沢���\n");
    printf("[����4] �������\n");
    printf("[����5] �������\n");
    printf("[����6] �������\n");
    printf("[����7] ���н��ȵ�ͳ��\n");
    printf("[����8] ʹ��Ĭ��˫�ױ�\n");
    printf("[����9] �˳�\n");
    Output_Cutoff_Rule();
}
int main()
{
	char choice;//�û�ѡ��
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
            printf("\n��ṹ����\n");
            printf("----------------------\n");
            printf("| ��� | ���� | ˫�� |\n");
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
            Output_Header("������n (n > 2)");
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
            Output_Header("�ڵ���n (n > 0)");
            fgets(buf, BUFSIZ, stdin);
            n = atoi(buf);

            pArray = malloc(sizeof(struct BTreeArrayNode) * n);
            for (int i = 0; i < n; ++i)
            {
                printf("---��%d�����----\n", i + 1);
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
		case '4'://�������
            BTree_PreOrder(tree, DisplayBTreeNode);
            system("pause");
			break;
		case '5'://�������
            BTree_PostOrder(tree, DisplayBTreeNode);
            system("pause");
			break;
		case '6'://�������
            BTree_SeqOrder(tree, DisplayBTreeNode);
            system("pause");
			break;
		case '7'://ͳ�ƽ�����
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