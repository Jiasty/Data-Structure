#include"BinaryTree.c"


void Test1()
{
    int a[] = {1, 4, 5, 3, 2, 9, 6};
    int i = 0;
    BTNode* Tree1 = CreatTree();
    PostOrderNonRec(Tree1);
    printf("\n");

    //PreOrder(Tree1);
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
    
    //printf("%d ",BinaryTreeComplete(Tree1));

    BinaryTreeDestory(&Tree1);
}

int main()
{
    Test1();

    return 0;
}