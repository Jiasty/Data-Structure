#include"SeqList.h"

//// 基本增删查改接口

// 顺序表初始化ok
void SeqListInit(SeqList* psl)
{
    assert(psl);

    psl->array = NULL;
    psl->size = 0;
    psl->capacity = 0;
}
// 顺序表销毁ok
void SeqListDestory(SeqList* psl)
{
    assert(psl); //检查psl是否指向了一个顺序表（的结构体）

    if(psl->array != NULL) //这里注意避免free 空指针
    {
        free(psl->array); //注意不是销毁psl，而是psl指向的SeqList这个结构体里面的array动态开辟的空间。
        psl->array = NULL;
        psl->size = 0;
        psl->capacity = 0;
    }
}

// 检查空间，如果满了，进行增容ok
void CheckCapacity(SeqList* psl)
{
    assert(psl);

    if(psl->capacity == psl->size)
    {
        int newCapacity = psl->capacity == 0 ? 4 : psl->capacity * 2; //一条代码就很好的解决了顺序表为空和非空两种情况的扩容。扩容以2倍速扩

        //接收扩容的空间，再赋给array
        SLDataType* tmp = (SLDataType*)realloc(psl->array,sizeof(SLDataType) * newCapacity);//注意计算SLDataType 
        if (tmp == NULL) //可能申请失败所以得判断一下
		{
			perror("realloc fail");
			//return;
			exit(-1);
		}

        psl->array = tmp;
        psl->capacity = newCapacity;  
    
    }
    //错误：三目运算符的使用和sizeof计算类型大小
    //psl->capacity == 0 ? psl->capacity = 4 && psl->array = (SLDataType*)malloc(sizeof(SLDataType) * capacity)
    //                   : psl->array = (SLDataType*)realloc(psl->array,(SLDataType) * capacity * 2);
}

// 顺序表尾插ok
void SeqListPushBack(SeqList* psl, SLDataType x)
{
    assert(psl);
    CheckCapacity(psl);

    psl->array[psl->size] = x; //注意size的访问
    psl->size++;
}
// 顺序表尾删ok
void SeqListPopBack(SeqList* psl)
{
    assert(psl);
    assert(psl->size > 0);//一定注意是否顺序表里有元素才删
    //assert(psl->array);也许不为空，只是没数据

    psl->size--;
}
// 顺序表头插ok
void SeqListPushFront(SeqList* psl, SLDataType x)
{
    assert(psl);
    CheckCapacity(psl);

    int num = psl->size;
    while(num)
    {
        psl->array[num] = psl->array[num-1];
        --num;
    }
    psl->array[num] = x;
    psl->size++;
}
// 顺序表头删ok
void SeqListPopFront(SeqList* psl)
{
    assert(psl);
    assert(psl->size > 0);

    int p = 0;
    while(p < psl->size)
    {
        psl->array[p] = psl->array[p+1];
        p++;
    }
    psl->size--;
}
// 顺序表在pos位置插入x ok
void SeqListInsert(SeqList* psl, size_t pos, SLDataType x)
{
    assert(psl);
    assert(pos >= 0 && pos <= psl->size);//进一步判断pos有效性

    CheckCapacity(psl);

    //挪动数据
    int end = psl->size; //避免size改变
    while(end > pos)
    {
        psl->array[end] = psl->array[end-1];
        end--;
    }
    psl->array[pos] = x;
    psl->size++;
}
// 顺序表删除pos位置的值
void SeqListErase(SeqList* psl, size_t pos)
{
    assert(psl);
    assert(pos >= 0 && pos <= psl->size);
    
    // 挪动覆盖
    while(pos < psl->size-1)
    {
        psl->array[pos] = psl->array[pos+1];
        pos++;
    }

    // int begin = pos + 1;
	// while (begin < psl->size)
	// {
	// 	psl->a[begin - 1] = psl->a[begin];
	// 	++begin;
	// }
    psl->size--;
}


//！！！ 顺序表查找 只能返回一个，能不能多一个输出型参数（指针）用数组来存储下标
int SeqListFind(SeqList* psl, SLDataType x) //x为想要查找的数据，i为下标
{
    assert(psl);
    //assert(psl->array);为何不检查数组是否开了？
    //没开数组则size就是0，不会进入if

    for(int i = 0;i < psl->size;i++)
    {
        if(psl->array[i] == x)
        {
            return i;
        }
    }
    return -1;//没找到

    
    //int i = 0;
    //while(i >= psl->size) //切勿while(int i = 0 >= psl->size)
    //{
    //    if(psl->array[i] == x)
    //    {
    //        return i;
    //    }
    //}
}

// 顺序表打印ok
void SeqListPrint(SeqList* psl)
{
    assert(psl);

    for(int i=0;i < psl->size;i++)
    {
        printf("%d ",psl->array[i]);
    }
    printf("\n");
}
