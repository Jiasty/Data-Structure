#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void MergeSort(int* arr, int n);
void Merge(int* arr, int begin, int end, int* tmp);

int main()
{
    int a[] = {6, 1, 2, 6, 7, 9, 6, 3, 4, 5, 10, 8};
    MergeSort(a, sizeof(a) / sizeof(a[0]));

	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		printf("%d ", a[i]);
	}

    return 0;
}

//思路:将一个序列进行分治，先使每个子序列有序。再将两个有序表合并成一个有序表，称为二路归并。整体为后续递归。
//需要借助一个额外的数组来存储归并得到得数据，再拷贝回原数组
//时间复杂度: O(N*logN) 空间复杂度: O(N)
//稳定性: 稳定
void MergeSort(int* arr, int n)
{
    int* tmp = (int*)malloc(sizeof(int) * n);
    if(tmp == NULL)
    {
        perror("malloc fail");
    }

    Merge(arr, 0, n - 1, tmp);
    free(tmp);
}

//子函数来控制区间和额外数组的地址，不可能用主函数递归，每次都创建新的数组
void Merge(int* arr, int begin, int end, int* tmp)
{
    if(begin >= end)
        return;

    //分割区间
    int midi = (begin + end) / 2;
    //[begin, midi] [midi + 1, end]
    Merge(arr, begin, midi, tmp);
    Merge(arr, midi + 1, end, tmp);
    
    //归并到tmp!!!!!!!!!!!
    //定归并区间
    int begin1 = begin, end1 = midi;
    int begin2 = midi + 1, end2 = end;
    int i = begin;
    while(begin1 <= end1 && begin2 <= end2)//有一个完就结束，然后单独处理剩下的
    {
        if(arr[begin1] < arr[begin2])
        {
            tmp[i++] = arr[begin1++];
        }
        else
        {
            tmp[i++] = arr[begin2++];
        }
    }

    while(begin1 <= end1)
    {
        tmp[i++] = arr[begin1++];
    }
    while(begin2 <= end2)
    {
        tmp[i++] = arr[begin2++];
    }

    memcpy(arr + begin, tmp + begin, sizeof(int) * (end - begin + 1));
}