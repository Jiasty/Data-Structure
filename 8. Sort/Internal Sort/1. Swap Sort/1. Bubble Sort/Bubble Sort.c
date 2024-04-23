#include<stdio.h>
#include<stdbool.h>

void BubbleSort(int* a, int n);
void Swap(int* n1, int* n2);

int main()
{
	int a[] = {1, 2, 6, 3, 1, 4, 5};
	BubbleSort(a, sizeof(a) / sizeof(a[0]));
	for(int i = 0; i < sizeof(a) / sizeof(a[0]);i++)
		printf("%d ", a[i]);
    return 0;
}

void BubbleSort(int* a, int n)
{
	for (int j = 0; j < n; j++)  // 外层循环控制趟数和影响内层循环每趟的长度
	{
		bool exchange = false;  //可能中间就已经排完了，如果为false就直接跳出循环
		for (int i = 0; i < n - j - 1; i++)  //每趟循环长度由趟数决定
		{
			if (a[i] > a[i + 1])
			{
				Swap(&a[i], &a[i + 1]);
				exchange = true;
			}
		}

		if (exchange == false)
			break;
	}
}

void Swap(int* n1, int* n2)
{
    int tmp = *n1;
    *n1 = *n2;
    *n2 = tmp;
}