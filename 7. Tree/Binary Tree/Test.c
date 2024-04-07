#include"BinaryTree.h"

void Test1()
{
    BTNode* Tree1 = CreatTree();

    // PreOrder(Tree1);
    // printf("\n");
    // InOrder(Tree1);
    // printf("\n");
    // PostOrder(Tree1);
    // printf("\n");
    // LevelOrder(Tree1);
    // printf("\n");

    //printf("%d ",BinaryTreeSize(Tree1));
    
    //printf("%d ",BinaryTreeLeafSize(Tree1));
    
    //printf("%d ",BinaryTreeHeight(Tree1));

    //printf("%d ",BinaryTreeLevelKSize(Tree1, 1));
    
    //printf("%p ",BinaryTreeFind(Tree1, 3));
    
    printf("%d ",BinaryTreeComplete(Tree1));

    BinaryTreeDestory(&Tree1);
}

int main()
{
    Test1();

    return 0;
}