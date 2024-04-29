#include<stdio.h>

void SelectionSort1(int* arr, int n);
void SelectionSort2(int* arr, int n);
void Swap(int* n1, int* n2);


int main()
{
    int a[]= {11, 4, 2, 1, 9, 6, 3, 2};
    //SelectionSort1(a, sizeof(a) / sizeof(a[0]));
    SelectionSort2(a, sizeof(a) / sizeof(a[0]));
    for(int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
    {
        printf("%d ", a[i]);
    }

    return 0;
}

//时间复杂度O:(N ^ 2)
//最好的情况O:(N ^ 2)
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
    //外层循环控制趟数和范围
    //begin == end时其他数都排好了，最后中间的数自然也是排好的，就不用排了
    for (int begin = 0, end = n - 1; begin < end; ++begin, --end)
    {
        //一趟选出最小和最大的数
        int minIndex = begin;
        int maxIndex = end;
        //{11, 4, 2, 1, 9, 6, 3, 2}
        for (int k = begin; k <= end; ++k) //注意范围，可能最大值在最开头
        {
            if(arr[k] < arr[minIndex])
            {
                minIndex = k;
            }

            if(arr[k] > arr[maxIndex])
            {
                maxIndex = k;
            }

        }
        //如果只记录下标，当最大的数就在i = 0位置时
        //第一次交换就把最大的数换走了，此时交换到最末尾的数为新交换的i = 0位置的最小的值
        Swap(&arr[begin], &arr[minIndex]);
        //所以加一个判断
        if(maxIndex == begin)
        {
            maxIndex = minIndex; //此时max已经换到min位置了
        }
        Swap(&arr[end], &arr[maxIndex]);
    }
}

void Swap(int* n1, int* n2)
{
    int tmp = *n1;
    *n1 = *n2;
    *n2 = tmp;
}