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




// 初始化栈ok
void StackInit(Stack* ps)
{
    assert(ps);

    ps->arr = NULL;
    ps->capacity = 0;

    // 1. 表示top指向栈顶元素
	ps->top = -1;
    // 2. 表示top指向栈顶元素的下一个位置
	//ps->top = 0;
    //这两种哪个更好?
    //top == 0，当插入一个元素和top指向栈顶元素还得是0，所以会产生歧义，若要使top指向栈顶元素最好top = -1;
    //top == 0 则top就表示数据个数
}
// 入栈ok
void StackPush(Stack* ps, STDataType data)
{
    assert(ps);

    // top == -1;先加top再入值
    // ++top;
    // arr[top];

    // top == 0;先入值再加top
    // arr[top];
    // top++;

    //判断栈是否有空间入，没有则扩容
    if(ps->capacity == ps->top + 1)
    {
        int newCapacity = ps->capacity == 0 ? 4 : ps->capacity * 2;
        STDataType* tmp = (STDataType*)realloc(ps->arr, sizeof(STDataType) * newCapacity);
        if(tmp == NULL)
        {
            perror("realloc error");
            return;
            //exit(-1); 出错了，程序应该停止，不加这两会继续进行下面的语句。
        }

        ps->arr = tmp;
        ps->capacity = newCapacity;
    }

    ps->arr[++ps->top] = data;
}
// 出栈ok
void StackPop(Stack* ps)
{
    assert(ps);
    assert(ps->top + 1);

    ps->top--;
}
// 获取栈顶元素ok
STDataType StackTop(Stack* ps)
{
    assert(ps);
    assert(ps->top + 1);

    return ps->arr[ps->top];
} 
// 获取栈中有效元素个数ok
int StackSize(Stack* ps)
{
    assert(ps);

    return ps->top + 1;
} 
// 检测栈是否为空，如果为空返回true，如果不为空返回false ok
bool StackEmpty(Stack* ps)
{
    assert(ps);

    /*if (pst->top + 1 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}*/

    return ps->top + 1 == 0; //表达式结果为true or false
} 
// 销毁栈ok
void StackDestroy(Stack* ps)
{
    assert(ps);

    free(ps->arr);
    ps->arr = NULL;
    ps->top = -1;
    ps->capacity = 0;

    //Stack st1 这个结构体没有释放，传的一级指针，得在外面释放
}