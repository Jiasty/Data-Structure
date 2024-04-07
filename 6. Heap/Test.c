#include"Heap.h"

void Test1()
{
    Heap h1;
    HeapCreate(&h1);

    //插入测试,插入顺序不同，堆是不同的
    int a[] = { 4,6,2,1,5,8,2,9};
	for (int i = 0; i < sizeof(a) / sizeof(int); ++i)
	{
		HeapPush(&h1, a[i]);
	}

    HeapPrint(&h1);
    printf("%d \n",HeapTop(&h1));

    //删除测试
    HeapPop(&h1);
    HeapPop(&h1);
    HeapPop(&h1);
    printf("%d \n",HeapTop(&h1));

    printf("%d \n",HeapSize(&h1));
    
    printf("%d \n",HeapEmpty(&h1));

    HeapDestory(&h1);
}

int main()
{
    Test1();

    return 0;
}