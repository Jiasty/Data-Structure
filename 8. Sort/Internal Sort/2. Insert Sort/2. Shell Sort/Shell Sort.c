#include<stdio.h>

void ShellSort1(int* arr, int n);
void ShellSort2(int* arr, int n);
void Swap(int* n1, int* n2);

int main()
{
    int a[] = {3, 4, 0, 6, 9, 2, 1, 7};
    //ShellSort1(a, sizeof(a) / sizeof(a[0]));
    ShellSort2(a, sizeof(a) / sizeof(a[0]));
    for(int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
    {
        printf("%d ", a[i]);
    }

    return 0;
}


//时间复杂度:平均O(N ^ 1.3)
//希尔排序是最早突破O(N ^ 2)复杂度的排序算法之一
//希尔排序分为两部分:1、预排序（使接近有序，然后插入排序提高效率）  2、直接插入排序
//1、预排序:对每个分组各自进行插入排序
//2、直接插入排序:gap会--，当gap == 1时就是直接插入排序，实现有序
//插入排序不适合
//插入排序不具有稳定性

//方法一:一组一组排
void ShellSort1(int* arr, int n)
{
    //gap越大，大的数更快跳跃到后面，小的数越快跳跃到前面，但是越不接近有序
    //gap越小，跳的越慢，但是越接近有序，gap == 1就是直接插入排序
    //gap随n进行变化，且可以多次预排序来适应上述gap大小的问题，先大后小
    int gap = n; //定间隔，分组（gap为几就有几组）利用gap控制预排序和最后一次插入排序

    while(gap > 1)  //gap > 1 预排序  gap == 1 插入排序
    {
        //一定要保证最后一次是1
        //gap /= 2;  //分组比较多
        gap  = gap / 3 + 1;  // +1保证最后一次gap为1（gap == 2 时）

        //分别对每一组进行插入排序(此时两数据之间就是差 gap 而不是 1)
        for(int j = 0; j < gap; j++) //此层循环控制每一组的插入排序
        {
            for(int i = j; i < n - gap; i += gap)  //此处i < n-gap,避免越界，i为起始位置，取决于哪一组（j），一定注意
            {
                int end = i;
                int tmp = arr[end + gap]; //如果上述循环结束条件为i < n-1 此处可能会越界，
                //因为i-2位置还不满足结束条件，就会继续，而i-2+gap就会越界
                while(end >= 0)
                {
                    if(arr[end] > tmp)
                    {
                        arr[end + gap] = arr[end];
                        end -= gap;
                    }
                    else
                        break;
                }
                arr[end + gap] = tmp;
            }
        }
    }

}

//方法二:多组并排，预排序优化
void ShellSort2(int* arr, int n)
{
    int gap = n;

    while(gap > 1)
    {
        //gap /= 2;
        gap  = gap / 3 + 1;
        for(int i = 0; i < n - gap; ++i)  //此时是多组一起排，周期性跳跃排，而不是等一组排完再排下一组，就可以减少一趟循环
        {
            int end = i;
            int tmp = arr[end + gap];
            while(end >= 0)
            {
                if(arr[end] > tmp)
                {
                    arr[end + gap] = arr[end];
                    end -= gap;
                }
                else
                    break;
            }
            arr[end + gap] = tmp;
        }
    }
}

void Swap(int* n1, int* n2)
{
    int tmp = *n1;
    *n1 = *n2;
    *n2 = tmp;
}