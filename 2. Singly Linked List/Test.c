#include"SList.h"

void Test1()
{
    SLNode* phead = NULL; //这里定义一个链表，最好直接用指针
    
    //尾插测试
    SListPushBack(&phead, 1);
    SListPushBack(&phead, 2);
    SListPushBack(&phead, 3);
    SListPushBack(&phead, 4);
    SListPushBack(&phead, 5);

    SListPrint(phead);
    //1->2->3->4->5->NULL

    //头插测试
    SListPushFront(&phead, 6);
    SListPushFront(&phead, 7);

    SListPrint(phead);
    //7->6->1->2->3->4->5->NULL

    // 单链表的尾删
    SListPopBack(&phead);
    SListPopBack(&phead);

    SListPrint(phead);
    //7->6->1->2->3->NULL

    // 单链表头删
    SListPopFront(&phead);
    SListPopFront(&phead);

    SListPrint(phead);
    //1->2->3->NULL
}

void Test2()
{
    SLNode* phead = NULL;

    //尾插
    SListPushBack(&phead, 1);
    SListPushBack(&phead, 2);
    SListPushBack(&phead, 3);
    SListPushBack(&phead, 4);
    SListPushBack(&phead, 5);

    SListPrint(phead);
    //1->2->3->4->5->NULL

    SLNode* temp = SListFind(phead, 3);
    printf("%d ", temp->val);
    printf("%p ", temp);

    // 单链表在pos位置之后插入x
    SListInsertAfter(temp, 11);
    SListPrint(phead);
    //1->2->3->11->4->5->NULL

    // 单链表删除pos位置之后的值
    SListEraseAfter(temp);
    SListPrint(phead);
    //1->2->3->4->5->NULL

    // //在pos前的插入和删除
    // SLTInsert(&phead, temp, 22);
    // SListPrint(phead);
    // //1->2->22->3->4->5->NULL

    // SLTErase(&phead, temp);
    // SListPrint(phead);
    // //1->2->3->4->5->NULL

}
int main()
{
    //Test1();
    Test2();
    return 0;
}