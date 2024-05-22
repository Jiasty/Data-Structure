#include <stdio.h>
#include <stdlib.h>

// 定义二叉树节点结构
typedef struct BTNode {
    int data;
    struct BTNode *left;
    struct BTNode *right;
} BTNode;

// 定义栈节点结构
typedef struct StackNode {
    BTNode *treeNode;
    struct StackNode *next;
} StackNode;

// 定义栈结构
typedef struct Stack {
    StackNode *top;
} Stack;

// 栈操作：初始化
void StackInit(Stack *s) {
    s->top = NULL;
}

// 栈操作：压栈
void StackPush(Stack *s, BTNode *treeNode) {
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->treeNode = treeNode;
    newNode->next = s->top;
    s->top = newNode;
}

// 栈操作：出栈
void StackPop(Stack *s) {
    if (s->top == NULL) {
        return;
    }
    StackNode *temp = s->top;
    s->top = s->top->next;
    free(temp);
}

// 栈操作：获取栈顶元素
BTNode* StackTop(Stack *s) {
    if (s->top == NULL) {
        return NULL;
    }
    return s->top->treeNode;
}

// 判断栈是否为空
int StackEmpty(Stack *s) {
    return s->top == NULL;
}

// 栈操作：销毁栈
void StackDestroy(Stack *s) {
    while (!StackEmpty(s)) {
        StackPop(s);
    }
}

// 二叉树的前序非递归遍历
void PreOrderNonRec(BTNode *root) {
    if (root == NULL) {
        return;
    }

    Stack s;
    StackInit(&s);

    StackPush(&s, root);
    while (!StackEmpty(&s)) {
        // 保存栈顶结点
        BTNode *tmp = StackTop(&s);
        printf("%d ", tmp->data);
        StackPop(&s);

        // 先压入右子节点，再压入左子节点
        if (tmp->right) {
            StackPush(&s, tmp->right);
        }
        if (tmp->left) {
            StackPush(&s, tmp->left);
        }
    }

    StackDestroy(&s);
}

// 辅助函数：创建新节点
BTNode* createNode(int data) {
    BTNode *newNode = (BTNode *)malloc(sizeof(BTNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int main() {
    // 创建示例二叉树
    BTNode *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    printf("前序遍历结果: ");
    PreOrderNonRec(root);
    printf("\n");

    return 0;
}