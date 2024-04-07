#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
//Linked Queue 尾入头出

typedef int QDataType;
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