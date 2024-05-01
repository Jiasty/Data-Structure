#include"Heap.h"

void HeapSort(int* arr, int n);

int main()
{
    int a[] = {6, 2, 4, 1, 0, 7, 11, 3, 2};
    HeapSort(a, sizeof(a) / sizeof(a[0]));
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		printf("%d ", a[i]);
	}

    return 0;
}

void HeapSort(int* arr, int n)
{
    //为了不额外开空间进行排序，应建大堆，最大数与最后一个数交换，然后向下调整堆
	for (int i = (n - 1 - 1) / 2; i >= 0; --i)
	{
		AdjustDown(arr, n, i);
	}

	// O(N*logN)
	int end = n - 1;
	while (end > 0)
	{
		Swap(&arr[0], &arr[end]);
		AdjustDown(arr, end, 0);
		--end;
	}
}

//vscode下为何要单独把定义拿到此处才行（包heap.c文件也能解决，这是为何？）
//交换函数
void Swap(HeapDataType* p1, HeapDataType* p2)
{
    HeapDataType tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

void AdjustDown(HeapDataType* a, int size, int parent)
{
    int child = parent * 2 + 1; //这是左孩子的位置，假设法假设左孩子比右孩子小

    while(child < size)
    {
        //判断两兄弟大小再更新child
        if(a[child] < a[child + 1] && child + 1 < size) //child + 1 < size 保证极端情况下右孩子存在
        {
            ++child;
        }

        if(a[child] > a[parent])
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