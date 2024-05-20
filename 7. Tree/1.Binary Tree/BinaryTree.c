#include"BinaryTree.h"
#include"Queue.h" //某些接口会用到队列 //为什么不能包在 BinaryTree.h里面?
#include"Stack.h"

//创建二叉树结点ok
BTNode* BuyTreeNode(BTDataType x)
{
    BTNode* newNode = (BTNode*)malloc(sizeof(BTNode));
    if(newNode == NULL)
    {
        perror("malloc fail");
        exit(-1);
    }

    newNode->data = x;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}
//构建树(测试用，直接手动构造)
BTNode* CreatTree()
{
    BTNode *root = BuyTreeNode(1);
    root->left = BuyTreeNode(2);
    root->right = BuyTreeNode(3);
    root->left->left = BuyTreeNode(4);
    root->left->right = BuyTreeNode(5);
    root->right->left = BuyTreeNode(6);
    root->right->right = BuyTreeNode(7);
    // BTNode* node1 = BuyTreeNode(1);
	// BTNode* node2 = BuyTreeNode(2);
	// BTNode* node3 = BuyTreeNode(3);
	// BTNode* node4 = BuyTreeNode(4);
	// BTNode* node5 = BuyTreeNode(5);
	// BTNode* node6 = BuyTreeNode(6);
	// BTNode* node7 = BuyTreeNode(7);

	// node1->left = node2;
	// node1->right = node4;
	// node2->left = node3;
	// node4->left = node5;
	// node4->right = node6;
	// node5->right = node7;

	return root;
}
// 通过前序遍历的数组"ABD##E#H##CF##G##"构建二叉树！！！
// pi 是什么? 是下标的地址
// 为何要采用这种模式? 
BTNode* BinaryTreeCreate(BTDataType* a, int* pi)
{
    if(a[*pi] == '#')
    {
        (*pi)++; // ++ 优先级高于 *
        return NULL;
    }
    BTNode* root = (BTNode*)malloc(sizeof(BTNode));
    if(root = NULL)
    {
        perror("malloc fail");
        exit(-1);
    }

    root->data = a[(*pi)++];
    //左右子树构建完毕再返回
    root->left = BinaryTreeCreate(a, pi);
    root->right = BinaryTreeCreate(a, pi);

    return root;
}
// 二叉树销毁ok
void BinaryTreeDestory(BTNode** root)
{
    assert(root);

    if(*root == NULL)
    {
        return;
    }

    BinaryTreeDestory(&((*root)->left));
    BinaryTreeDestory(&((*root)->right));
    free(*root);
    *root = NULL; //不用二级指针置空那就在外面置空
}

// 二叉树前序遍历ok 深度优先遍历DFS
void PreOrder(BTNode* root)
{
    //不用assert
    if (root == NULL)
	{
		printf("N ");
		return;
	}

    printf("%d ",root->data);
    //root->left被传给该函数里的root，所以不用手动控制root移动
    //函数调用会创立栈帧。不同域里面允许有同名变量
    PreOrder(root->left); 
    PreOrder(root->right);
}
// 二叉树中序遍历ok
void InOrder(BTNode* root)
{
    if (root == NULL)
	{
		printf("N ");
		return;
	}

    InOrder(root->left);
    printf("%d ",root->data);
    InOrder(root->right);
}
// 二叉树后序遍历ok
void PostOrder(BTNode* root)
{
    if (root == NULL)
	{
		printf("N ");
		return;
	}

    PostOrder(root->left);
    PostOrder(root->right);
    printf("%d ",root->data);
}
// 层序遍历(需要包一下队列) 广度优先遍历BFS
void LevelOrder(BTNode* root)
{
    Queue q;
    QueueInit(&q);
    //层序遍历逻辑
    if(root)
    {
        QueuePush(&q, root);
    }

    int Levelsize = 1;
    while(!QueueEmpty(&q))
    {
        while(Levelsize--) //减到0就说明出完了，然后就换行再获取下一层个数
        {
            BTNode* front = QueueFront(&q);
            QueuePop(&q); //QueueNode 的释放不影响TreeNode,所以front不受影响
            //怎么一层一层打印? 1. 再开一个队列记录层数，C语言不好实现 2. val 改为结构体多存层数
            //                 3. Levelsize 记录每一层数据个数,控制一层一层出

            printf("%d ",front->data);
            
            if(front->left)
            {
                QueuePush(&q, front->left);
            }
            if(front->right)
            {
                QueuePush(&q, front->right);
            }
        }
        printf("\n");
        Levelsize = QueueSize(&q);
    }
    
    QueueDestroy(&q);
}

// 二叉树节点个数ok
int BinaryTreeSize(BTNode* root)
{
    if(root == NULL)
    {
        return 0;
    }

    //遍历树统计个数极其麻烦
    //设静态变量统计个数会造成第二次调用函数时静态变量不会重置
    //分治思想，左子树和右子树分别统计   
    return BinaryTreeSize(root->left) + BinaryTreeSize(root->right) + 1; // + 1 是为了算上自己

    //简略版(三目运算符替换if...else...)
    //return root == NULL ? 0 : BinaryTreeSize(root->left) + BinaryTreeSize(root->right) + 1;
}
// 二叉树叶子节点个数！！！ok
int BinaryTreeLeafSize(BTNode* root)
{
    //此处返回情况较多，可以分开写
    //1. 是空，返回 0 
    if(root == NULL)
    {
        return 0;
    }
    //2. 不是空是叶子，返回 1
    if(root->left == NULL && root->right == NULL)
    {
        return 1;
    }
    //3. 不是空也不是叶子  分治分别统计左子树和右子树的叶子结点个数
    return BinaryTreeLeafSize(root->left) + BinaryTreeLeafSize(root->right);
}
// 二叉树第k层节点个数ok
int BinaryTreeLevelKSize(BTNode* root, int k)
{
    // 1. root 为空 或者k不正确(或者将k强制定为k > 0)
    //assert(k > 0);
    if(root == NULL || k < 1 || k > BinaryTreeHeight(root))
    {
        return 0;
    }
    // 2. root 不为空且 k == 1
    if(root && k == 1)
    {
        return 1;
    }
    // 3. root 不为空且 k > 1
    return BinaryTreeLevelKSize(root->left, k - 1) + BinaryTreeLevelKSize(root->right, k - 1);
}
//二叉树的高度!!!!
int BinaryTreeHeight(BTNode* root)
{
    if(root == NULL)
    {
        return 0;
    }

    //记录下高度，不用在传高的子树的高度的时候再次去计算高度，减少函数调用
    int left = BinaryTreeHeight(root->left);
    int right = BinaryTreeHeight(root->right);
    return left > right ? left + 1 : right + 1;

    //下列代码只比较不记录，返回值的时候还得重新计算大的高度值
    // return root == NULL ? 0 : 
    //     BinaryTreeHeight(root->left) > BinaryTreeHeight(root->right) ?
    //     BinaryTreeHeight(root->left) + 1 : BinaryTreeHeight(root->right) + 1;
}
// 二叉树查找值为x的节点
BTNode* BinaryTreeFind(BTNode* root, BTDataType x)
{
    if(root == NULL)
    {
        return NULL;
    }

    if(root->data == x)
    {
        return root;
    }

    //有什么问题?
    //这是一个表达式，只会返回 0 或 1
    //所以还是接收一下地址，有则返回
    //return BinaryTreeFind(root->left, x) || BinaryTreeFind(root->right, x);

    BTNode* ret1 = BinaryTreeFind(root->left, x);
    if(ret1)
    {
        return ret1;
    }

    BTNode* ret2 = BinaryTreeFind(root->right, x);
    if(ret2)
    {
        return ret2;
    }

    return NULL; //如果最外层返回NULL才是没有该结点
}
// 判断二叉树是否是完全二叉树。!!!!
bool BinaryTreeComplete(BTNode* root)
{
    Queue q;
    QueueInit(&q);
    //层序遍历逻辑
    if(root)
    {
        QueuePush(&q, root);
    }

    while(!QueueEmpty(&q))
    {
        //出到空就停，然后看队列是否为空
        BTNode* front = QueueFront(&q);
        QueuePop(&q);
        if(front == NULL) //遇空跳出循环
        {
            break;
        }
        //空也带进去 空也算有效数据吗?
        QueuePush(&q, front->left);
        QueuePush(&q, front->right);
    }
    
    while(!QueueEmpty(&q))
    {
        BTNode* front = QueueFront(&q);
        QueuePop(&q);
        
        if(front)
        {
            QueueDestroy(&q);
            return false;
        }

        QueuePush(&q, front->left);
        QueuePush(&q, front->right);
    }
    
    QueueDestroy(&q);
    return true;
}


// 二叉树前序遍历
void PreOrderNonRec(BTNode* root)
{
    if(root == NULL)
        return;

    Stack* s;
    StackInit(s);

    StackPush(s, root);
    while(!StackEmpty(s))
    {
        //保存栈顶结点
        BTNode* tmp = StackTop(s);
        printf("%d ", tmp->data);
        StackPop(s);

        if(tmp->right)
            StackPush(s, tmp->right);
        if(tmp->left)
            StackPush(s, tmp->left);
    }
    
    StackDestroy(s);
    
}
// 二叉树中序遍历
void InOrderNonRec(BTNode* root)
{
    if(root == NULL)
        return;

    Stack* s;
    StackInit(s);

    BTNode* cur = root;
    while(cur || !StackEmpty(s))
    {
        while(cur)
        {
            //一直入左结点
            StackPush(s, cur);
            cur = cur->left;
        }
        //此时栈顶的结点没有左子树
        cur = StackTop(s);
        printf("%d ", cur->data);
        StackPop(s);
        cur = cur->right;
    }

    StackDestroy(s);
}
// 二叉树后序遍历
void PostOrderNonRec(BTNode* root)
{
    if(root == NULL)
        return;

    Stack* s;
    StackInit(s);

    BTNode* cur = root, *prev = root;
    while(cur || !StackEmpty(s))
    {
        //沿着左子树入栈
        while(cur)
        {
            StackPush(s, cur);
            cur = cur->left;
        }
        cur = StackTop(s); //cur走到空出循环取栈顶元素

        //如果栈顶元素有右子树且未被访问则入栈
        if(cur->right && cur->right != prev)
        {
            cur = cur->right;
        }
        else //访问过或没有
        {
            printf("%d ", cur->data);
            prev = cur; //访问了才记录
            cur = NULL; //防止一直访问原来的左子树
            StackPop(s);
        }
    }
    StackDestroy(s);
}