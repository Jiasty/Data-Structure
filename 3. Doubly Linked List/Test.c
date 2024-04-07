#include"List.h"

void Test1()
{
    ListNode* phead = ListInit(); //定义一个双链表

    //尾插
    ListPushBack(phead, 1);
    ListPushBack(phead, 2);
    ListPushBack(phead, 3);
    ListPushBack(phead, 4);

    ListPrint(phead);
    //head<=>1<=>2<=>3<=>4<=>head

    //尾删
    ListPopBack(phead);
    ListPopBack(phead);
    // ListPopBack(phead);
    // ListPopBack(phead);
    // ListPopBack(phead);

    ListPrint(phead);
    //head<=>1<=>2<=>head

    //头插
    ListPushFront(phead, 5);
    ListPushFront(phead, 6);
    ListPushFront(phead, 7);

    ListPrint(phead);
    //head<=>7<=>6<=>5<=>1<=>2<=>head

    //头删
    ListPopFront(phead);
    ListPopFront(phead);
    // ListPopFront(phead);
    // ListPopFront(phead);
    // ListPopFront(phead);
    // ListPopFront(phead);

    ListPrint(phead);
    //head<=>5<=>1<=>2<=>head

    ListDestory(phead);
}

void Test2()
{
    ListNode* phead2 = ListInit();

    //尾插数据
    ListPushBack(phead2, 1);
    ListPushBack(phead2, 3);
    ListPushBack(phead2, 4);
    ListPushBack(phead2, 6);

    ListPrint(phead2);
    //head<=>1<=>3<=>4<=>6<=>head

    ListNode* ppos = ListFind(phead2, 3);
    ListInsert(ppos, 33);
    //ListInsert(phead2, 33);

    ListPrint(phead2);
    //head<=>1<=>33<=>3<=>4<=>6<=>head

    //ppos = phead2;
    ListErase(phead2, ppos);
    //ListErase(phead2); //如何避免？

    ListPrint(phead2);
    //head<=>1<=>33<=>4<=>6<=>head

    ListDestory(phead2);
}

int main()
{
    Test1();
    //Test2();

    return 0;
}