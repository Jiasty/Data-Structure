#include"SeqList.h"

void Test1()
{
    SeqList s1;
    SeqListInit(&s1);
    //尾插尾删测试
    SeqListPushBack(&s1, 1);
    SeqListPushBack(&s1, 2);
    SeqListPushBack(&s1, 3);
    SeqListPushBack(&s1, 4);
    //1 2 3 4
    SeqListPopBack(&s1);
    SeqListPopBack(&s1);
    //1 2
    SeqListPrint(&s1);

    //头插头删测试
    SeqListPushFront(&s1, 1);
    SeqListPushFront(&s1, 2);
    SeqListPushFront(&s1, 3);
    //3 2 1 1 2
    SeqListPopFront(&s1);
    SeqListPopFront(&s1);
    //1 1 2
    SeqListPrint(&s1);
    
    //任意位置插入删除
    SeqListInsert(&s1, 2, 11);
    SeqListPrint(&s1);
    //1 1 11 2

    SeqListErase(&s1, 2);
    SeqListPrint(&s1);
    //1 1 2

    SeqListDestory(&s1);//注意顺序表的销毁，易忘
}

void Test2()
{
    SeqList s2;
    SeqListInit(&s2);

    SeqListPushBack(&s2, 1);
    SeqListPushBack(&s2, 2);
    SeqListPushBack(&s2, 2);
    SeqListPushBack(&s2, 4);

    //find测试
    SeqListFind(&s2, 2);//怎么接收到两个位置？
    



    SeqListDestory(&s2);
}

int main()
{
    Test1();
    //Test2();

    return 0;
}