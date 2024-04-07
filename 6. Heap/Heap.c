#include"Heap.h"

// 堆的构建,初始化
void HeapCreate(Heap* hp)
{
    assert(hp);

    hp->arr = NULL;
    hp->size = 0;
    hp->capacity = 0;
}
// 堆的销毁
void HeapDestory(Heap* hp)
{
    assert(hp);

    free(hp->arr); //free会对空进行判断，为空也没事
    hp->arr = NULL; 
    hp->size = 0;
    hp->capacity = 0;
}
// 堆的插入
void HeapPush(Heap* hp, HeapDataType x)
{
    assert(hp);

    //判满扩容再插入数据
    if(hp->size == hp->capacity)
    {
        int newCapacity = hp->capacity == 0 ? 4 : hp->capacity * 2;
        HeapDataType* tmp = (HeapDataType*)realloc(hp->arr, sizeof(HeapDataType) * newCapacity);
        if(tmp == NULL)
        {
            perror("malloc fail");
            return;
        }

        hp->arr = tmp;
        hp->capacity = newCapacity;
    }
    
    hp->arr[hp->size] = x;
    hp->size++;

    //插入后还得向上调整，可以单独写一个函数
    AdjustUp(hp->arr, hp->size - 1); //注意这里size - 1是因为size已经++了，为了找到尾孩子得减 1
}
// 堆的删除
void HeapPop(Heap* hp)
{
    assert(hp);
    assert(hp->size > 0); //不为空才pop

    //首位交换数据后尾删
    Swap(&hp->arr[0], &hp->arr[hp->size - 1]);
    --hp->size;

    //再向下调整
    AdjustDown(hp->arr, hp->size, 0);
}
// 取堆顶的数据
HeapDataType HeapTop(Heap* hp)
{
    assert(hp);
    assert(hp->size > 0); //assert(hp->arr);注意arr地址可能不为空，但是里面没有插入数据，读出来会是随机值
    

    return hp->arr[0];
}
// 堆的数据个数
int HeapSize(Heap* hp)
{
    assert(hp);

    return hp->size;
}
// 堆的判空，空为true
bool HeapEmpty(Heap* hp)
{
    assert(hp);

    return hp->size == 0;
}

//交换函数
void Swap(HeapDataType* p1, HeapDataType* p2)
{
    HeapDataType tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}
//向上调整，child是任意一个孩子的下标
//为什么不传Heap* hp?
//时间复杂度?
void AdjustUp(HeapDataType* a, int child)
{
    int parent = (child - 1) / 2;

    while(child > 0)  //while(child)也行，但最好让其保持原生意义，为指针时另当别论
    {
        if(a[child] < a[parent])
        {
            Swap(&a[child], &a[parent]);
            child = parent;
            parent = (parent - 1) / 2;
        }
        else
        {
            break;
        }
    }
}
//向下调整
//时间复杂度?
void AdjustDown(HeapDataType* a, int size, int parent)
{
    int child = parent * 2 + 1; //这是左孩子的位置，假设法假设左孩子比右孩子小

    while(child < size)
    {
        //判断两兄弟大小再更新child
        if(a[child] > a[child + 1] && child + 1 < size) //child + 1 < size 保证极端情况下右孩子存在
        {
            ++child;
        }

        if(a[child] < a[parent])
        {
            Swap(&a[child], &a[parent]);
            parent = child;
            child = parent * 2 + 1;
        }
        else
        {
            break;
        }
    }
}

//堆打印数据
void HeapPrint(Heap* hp)
{
    assert(hp);

    int num = 0;
    while(num != hp->size)
    {
        printf("%d ",hp->arr[num]);
        num++;
    }

    printf("\n");
}