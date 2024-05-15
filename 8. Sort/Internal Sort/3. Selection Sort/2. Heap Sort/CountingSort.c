#include<stdio.h>
#include<stdlib.h>

void CountingSort(int* arr, int n);

int mian()
{
    int a[] = { 6, 2, 1, 8, 1, 3, 4, 2, 1, 10, 7 };
    CountingSort(a, sizeof(a) / sizeof(a[0]));

    for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
    {
        printf("%d ", a[i]);
    }
    return 0;
}


//思路:统计数据出现次数，然后依次覆盖。本质其实是哈希的思想。
//时间复杂度:O(N+range)
//空间复杂度:O(range)
//缺点:不适合很分散的数据，空间消耗大，只适合整数的排序
void CountingSort(int* a, int n)
{
	int min = a[0], max = a[0];
	for (int i = 1; i < n; i++)
	{
		if (a[i] < min)
			min = a[i];

		if (a[i] > max)
			max = a[i];
	}

	int range = max - min + 1;
	int* count = (int*)calloc(range, sizeof(int));
	if (count == NULL)
	{
		printf("calloc fail\n");
		return;
	}

	// 统计次数
	for (int i = 0; i < n; i++)
	{
		count[a[i] - min]++;
	}

	// 排序
	int i = 0;
	for (int j = 0; j < range; j++)
	{
		while (count[j]--)
		{
			a[i++] = j + min;
		}
	}
}