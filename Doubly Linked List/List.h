//#pragma once //什么意思？
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

//带头+双向+循环链表
typedef int LTDataType;

typedef struct ListNode
{
    LTDataType val;
    struct ListNode* next;
    struct ListNode* prev;
}ListNode;

//双链表初始化，初始化出头节点
ListNode* ListInit();

// 创建一个双链表的结点并返回地址.顺带初始化val
ListNode* ListCreatNode(LTDataType x);
// 双向链表销毁
void ListDestory(ListNode* plist);

// 双向链表打印
void ListPrint(ListNode* plist);

// 双向链表尾插
void ListPushBack(ListNode* plist, LTDataType x);
// 双向链表尾删
void ListPopBack(ListNode* plist);
// 双向链表头插
void ListPushFront(ListNode* plist, LTDataType x);
// 双向链表头删
void ListPopFront(ListNode* plist);

// 双向链表查找
ListNode* ListFind(ListNode* plist, LTDataType x);

// 双向链表在pos的前面进行插入
void ListInsert(ListNode* pos, LTDataType x);
// 双向链表删除pos位置的结点
void ListErase(ListNode* plist, ListNode* pos);