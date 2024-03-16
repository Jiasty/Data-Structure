#include"Queue.h"

void Test1()
{
    Queue q1;
    QueueInit(&q1);

    //入队测试
    QueuePush(&q1, 1);
    QueuePush(&q1, 2);
    QueuePush(&q1, 3);
    QueuePush(&q1, 4);

    //队头元素
    printf("%d ",QueueFront(&q1)); //1
    //队尾元素
    printf("%d ",QueueBack(&q1)); //4
    //队列元素个数
    printf("%d ",QueueSize(&q1)); //4

    //出队测试
    QueuePop(&q1);
    // QueuePop(&q1);
    // QueuePop(&q1);
    // QueuePop(&q1);
    // QueuePop(&q1);

    //队头元素
    printf("%d ",QueueFront(&q1)); //2
    //队尾元素
    printf("%d ",QueueBack(&q1)); //4
    //队列元素个数
    printf("%d ",QueueSize(&q1)); //3


    QueueDestroy(&q1);
}

void Test2()
{
    Queue q2;
    QueueInit(&q2);

    //入队测试
    QueuePush(&q2, 1);
    QueuePush(&q2, 2);
    QueuePush(&q2, 3);
    QueuePush(&q2, 4);

    //判空
    printf("%d ",QueueEmpty(&q2)); //0

    QueueDestroy(&q2);
}

int main()
{
    //Test1();
    Test2();
    return 0;
}