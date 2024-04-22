#include<stdio.h>
#include<stdbool.h>

void BubbleSort(int* a, int n);
void Swap(int* n1, int* n2);

int main()
{
    return 0;
}

void BubbleSort(int* a, int n)
{
	for (int j = 0; j < n; j++)
	{
		bool exchange = false;
		for (int i = 1; i < n-j; i++)
		{
			if (a[i - 1] > a[i])
			{
				Swap(&a[i - 1], &a[i]);
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