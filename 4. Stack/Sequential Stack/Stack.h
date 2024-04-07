#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
//Sequential Stack 相较于Linked Stack更好，扩容也是少数

typedef int STDataType;

typedef struct Stack
{
    STDataType* arr; //栈数据域
    int top; // 标识栈顶
    int capacity; // 容量,
    //int rear;
    //int count;
}Stack;

// 初始化栈
void StackInit(Stack* ps); 
// 入栈
void StackPush(Stack* ps, STDataType data); 
// 出栈
void StackPop(Stack* ps);
// 获取栈顶元素
STDataType StackTop(Stack* ps); 
// 获取栈中有效元素个数
int StackSize(Stack* ps); 
// 检测栈是否为空，如果为空返回true，如果不为空返回false 
bool StackEmpty(Stack* ps); 
// 销毁栈
void StackDestroy(Stack* ps);