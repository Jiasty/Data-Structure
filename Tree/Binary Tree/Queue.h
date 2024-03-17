#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
typedef struct BinaryTreeNode* QDataType;
// 队列结点
typedef struct QListNode 
{  
    QDataType val;
    struct QListNode* pNext; 
}QNode;
// 队列的结构,套一层结构体控制队列的头、尾指针，方便管理结点。不用这种方式后面的接口实现得多一个参数且传二级指针
typedef struct Queue
{ 
    QNode* front; 
    QNode* rear; 
    int size;
}Queue;

// 初始化队列
void QueueInit(Queue* pq); 
// 队尾入队列
void QueuePush(Queue* pq, QDataType data); 
// 队头出队列
void QueuePop(Queue* pq); 
// 获取队列头部元素
QDataType QueueFront(Queue* pq); 
// 获取队列队尾元素
QDataType QueueBack(Queue* pq); 
// 获取队列中有效元素个数,要么遍历，要么在Queue结构体里加一个size计算，空间换时间
int QueueSize(Queue* pq); 
// 检测队列是否为空，如果为空返回true，如果非空返回false 
bool QueueEmpty(Queue* pq); 
// 销毁队列
void QueueDestroy(Queue* pq);

////////////////

// 初始化队列
void QueueInit(Queue* pq)
{
    assert(pq);

    pq->front = NULL; //还没有指向结点
    pq->rear = NULL;
    pq->size = 0;
} 
// 队尾入队列，尾插，可以记录一个尾指针就好尾插
void QueuePush(Queue* pq, QDataType data)
{
    assert(pq);

    //创结点并初始化
    QNode* newnode = (QNode*)malloc(sizeof(QNode));
    if(newnode == NULL)
    {
        perror("malloc fail");
        return;
    }
    newnode->val = data;
    newnode->pNext = NULL;

    //找队尾链接
    if(pq->rear == NULL) //队尾为空则队列为空
    {
        pq->front = pq->rear = newnode;
    }
    else //注意顺序，尾插
    {
        pq->rear->pNext = newnode;
        pq->rear = newnode;
    }
    
    pq->size++;
}
// 队头出队列，头删，不尾删是因为记录尾指针也不方便尾删，得记录尾的前一个
void QueuePop(Queue* pq)
{
    assert(pq);
    assert(pq->front); //队列不为空才删
    //assert(pq->rear); 

    QNode* tmp = pq->front;
    pq->front = tmp->pNext;
    free(tmp);
    tmp = NULL;
    if(pq->front == NULL) //当最初不为空，结点删完后front == NULL，可rear还不为空的话就要出错，所以应在其中一个为空时把另一个指针也置空
    {
        pq->rear = NULL;
    }
    pq->size--;
}
// 获取队列头部元素
QDataType QueueFront(Queue* pq)
{
    assert(pq);
    assert(pq->front);

    return pq->front->val;
}
// 获取队列队尾元素
QDataType QueueBack(Queue* pq)
{
    assert(pq);
    assert(pq->rear);
    //assert(pq->front); 有什么区别？

    return pq->rear->val;
}
// 获取队列中有效元素个数
int QueueSize(Queue* pq)
{
    assert(pq);

    return pq->size;
} 
// 检测队列是否为空，如果为空返回true，如果非空返回false 
bool QueueEmpty(Queue* pq)
{
    assert(pq);

    // //if(pq->front == pq->rear ==NULL)
    // if(pq->size == 0)
    // {
    //     return true;
    // }
    // else
    // {
    //     return false;
    // }

    return pq->size == 0;
} 
// 销毁队列
void QueueDestroy(Queue* pq)
{
    assert(pq);
    //assert(pq->rear); 

    QNode* cur = pq->front;
    while(cur)
    {
        pq->front = cur->pNext;
        free(cur);
        cur = pq->front;
    }
    cur = NULL;
    pq->front = pq->rear = NULL;
    pq->size = 0;
}