#include<stdio.h>

void SelectionSort1(int* arr, int n);
void SelectionSort2(int* arr, int n);
void Swap(int* n1, int* n2);


int main()
{
    int a[]= {4, 2, 1, 9, 6, 3, 2};
    SelectionSort1(a, sizeof(a) / sizeof(a[0]));
    for(int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
    {
        printf("%d ", a[i]);
    }

    return 0;
}

//方法一:从头往后找最小
void SelectionSort1(int* arr, int n)
{
    for(int i = 0; i < n; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if(arr[j] < arr[minIndex])
                minIndex = j;
        }
        Swap(&arr[i], &arr[minIndex]);
    }
}

//方法二:前后一起开始找，前换小，后换大
void SelectionSort2(int* arr, int n)
{

}

void Swap(int* n1, int* n2)
{
    int tmp = *n1;
    *n1 = *n2;
    *n2 = tmp;
}