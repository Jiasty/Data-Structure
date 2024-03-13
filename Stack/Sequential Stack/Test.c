#include"Stack.h"

void Test1()
{
    Stack st1;
    StackInit(&st1);

    //入栈测试
    StackPush(&st1, 1);
    StackPush(&st1, 2);
    StackPush(&st1, 3);
    StackPush(&st1, 4);

    //获取栈顶元素 
    printf("%d ",StackTop(&st1));//4
    //栈中有效元素个数
    printf("%d ",StackSize(&st1)); //4

    //出栈测试
    StackPop(&st1);
    StackPop(&st1);

    //获取栈顶元素
    printf("%d ",StackTop(&st1)); //2
    //栈中有效数据个数
    printf("%d ",StackSize(&st1)); //2

    StackDestroy(&st1);
    //printf("%d ",StackEmpty(&st1));
}

int main()
{
    Test1();

    return 0;
}