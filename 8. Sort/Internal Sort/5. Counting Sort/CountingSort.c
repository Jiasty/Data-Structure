#include<stdio.h>
#include<stdlib.h>

void CountingSort(int* arr, int n);

int main()
{
    int a[] = {6, 2, 1, 0, 8, 1, 3, 4, 2, 1, 10, 7};
    CountingSort(a, sizeof(a) / sizeof(a[0]));

    for(int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
    {
        printf("%d ", a[i]);
    }
    return 0;
}


//思路:统计数据出现次数，然后依次覆盖。本质其实是哈希的思想。
//时间复杂度:O(N+range)
//空间复杂度:O(range)
//缺点:不适合很分散的数据，空间消耗大，只适合整数的排序
void CountingSort(int* arr, int n)
{
    int min = arr[0], max = arr[0];
    for(int i = 1; i < n; i++)
    {
        if(arr[i] < min)
        {
            min = arr[i];
        }

        if(arr[i] > max)
        {
            max = arr[i];
        }
    }

    int range = max - min + 1;
    int* count = (int*)calloc(range, sizeof(int));
    if(count == NULL)
    {
        printf("calloc fail");
        return;
    }
    //统计次数
    for(int i = 0; i < n; i++)
    {
        count[arr[i] - min]++;
    }
    //排序（覆盖）
    int j = 0;
    for(int i = 0; i < range; i++)
    {
        while(count[i]--)
        {
            arr[j++] = i + min;
        }
    }
}