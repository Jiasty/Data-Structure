#include<stdio.h>

void InsertSort1(int* arr, int n);
void InsertSort2(int* arr, int n);
void Swap(int* n1, int* n2);

int main()
{
    int a[] = {2, 4, 5, 3, 1};
    //InsertSort1(a, sizeof(a) / sizeof(a[0]));
    InsertSort2(a, sizeof(a) / sizeof(a[0]));
    for(int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
    {
        printf("%d ", a[i]);
    }

    return 0;
}

//时间复杂度O(N ^ 2)
//最好的情况O(N)
//虽然与冒泡排序都O(N ^ 2)，但是对接近有序的数组效率很高，适应性很强
//插入排序具有稳定性，不会改变相同数据的相对位置
//方法一:边比较边交换，利用swap函数而不是挪动数据
void InsertSort1(int* arr, int n)
{
    if(n == 1)
        return;
    // [0, end - 1] end 将 end 位置的元素插入有序区间
    // 最开始的一个元素即使有序
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

//方法二:用下标进行比较，挪动数据赋值覆盖
void InsertSort2(int* arr, int n)
{
    for(int i = 0; i < n - 1; i++)  //注意边界的控制，自行考虑用哪种，此处注意，不是i < n
    {
        int end = i;
        int tmp = arr[end + 1];
        while(end >= 0)
        {
            if(arr[end] > tmp)
            {
                arr[end + 1] = arr[end];
                end--;
            }
            else
            {
                break; //一定注意，tmp > 了arr[end - 1]时要跳出该次循环，否则可能陷入死循环
            }
        }
        arr[end + 1] = tmp;
    }
}

void Swap(int* n1, int* n2)
{
    int tmp = *n1;
    *n1 = *n2;
    *n2 = tmp;
}