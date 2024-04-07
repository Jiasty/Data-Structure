#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int SLNDataType; //single list node data type

typedef struct SListNode
{
    SLNDataType val;
    struct SListNode* next;
    //SLNode* next; //为何不可？
}SLNode;


//增删查改功能接口

//初始化和销毁
void InitSList(SLNode* plist); //单链表其实可以不用初始化，直接将phead指向NULL就行
void DestroySList(SLNode** pplist);


// 动态申请一个结点
SLNode* BuySListNode(SLNDataType x);
// 单链表打印
void SListPrint(SLNode* plist);
// 单链表尾插
void SListPushBack(SLNode** pplist, SLNDataType x);
// 单链表的头插
void SListPushFront(SLNode** pplist, SLNDataType x);
// 单链表的尾删
void SListPopBack(SLNode** pplist);
// 单链表头删
void SListPopFront(SLNode** pplist);
// 单链表查找
SLNode* SListFind(SLNode* plist, SLNDataType x);
// 单链表在pos位置之后插入x
// 分析思考为什么不在pos位置之前插入？
void SListInsertAfter(SLNode* pos, SLNDataType x);
// 单链表删除pos位置之后的值
// 分析思考为什么不删除pos位置？
void SListEraseAfter(SLNode* pos);