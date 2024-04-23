#include<stdio.h>

void InsertSort(int* arr, int n);
void Swap(int* n1, int* n2);

int main()
{
    int a[] = {1, 2, 4, 5, 3};
    InsertSort(a, sizeof(a) / sizeof(a[0]));
    for(int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
    {
        printf("%d ", a[i]);
    }

    return 0;
}

void InsertSort(int* arr, int n)
{
    if(n == 1)
        return;
    // [0, end - 1] end 将 end 位置的元素插入已有区间
    for(int i = 1; i < n; i++)
    {
        int endi = i;
        while(endi > 0 && (arr[endi - 1] > arr[endi]))
        {
            Swap(&arr[endi - 1], &arr[endi]);
            endi--;
        }
    }

}

void Swap(int* n1, int* n2)
{
    int tmp = *n1;
    *n1 = *n2;
    *n2 = tmp;
}