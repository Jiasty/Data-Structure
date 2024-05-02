#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void MergeSort(int* arr, int n);
void Merge(int* arr, int begin, int end, int* tmp);
void MergeSortNonR(int* arr, int n);

int main()
{
    int a[] = {10, 8, 7, 1, 3, 9, 4, 2, 11};
    //MergeSort(a, sizeof(a) / sizeof(a[0]));
    MergeSortNonR(a, sizeof(a) / sizeof(a[0]));
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
//归并排序也能作为外排序
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

//归并排序用栈不好实现，区间分割完后，归并时栈已经为空，不知道归并到哪个区间，主要由于后序递归会有归并的操作
//而快排可以用栈处理是因为它是前序递归，区间分割完后就不需要做其他处理
//思路:直接开始分组归并，自己做分割的过程
void MergeSortNonR(int *arr, int n)
{
    int* tmp = (int*)malloc(sizeof(int) * n);
    if(tmp == NULL)
    {
        perror("malloc fail");
    }

    //gap代表归并的每组数据个数
    int gap = 1;
    while(gap < n)
    {
        for(int i = 0; i < n; i += 2 * gap)
        {
            int begin1 = i, end1 = i + gap - 1;
            int begin2 = i + gap, end2 = i + 2 * gap - 1;
            //[begin1, end1] [begin2, end2]归并
            
            if(end1 >= n || begin2 >= n) //越界情况
            {
                break;
            }
            if(end2 >= n)
            {
                end2 = n - 1;
            }

            int j = begin1;
            while(begin1 <= end1 && begin2 <= end2)//有一个完就结束，然后单独处理剩下的
            {
                if(arr[begin1] < arr[begin2])
                {
                    tmp[j++] = arr[begin1++];
                }
                else
                {
                    tmp[j++] = arr[begin2++];
                }
            }

            while(begin1 <= end1)
            {
                tmp[j++] = arr[begin1++];
            }
            while(begin2 <= end2)
            {
                tmp[j++] = arr[begin2++];
            }

            //放循环内，归并一点拷贝一点，避免不必要的问题
            memcpy(arr + i, tmp + i, sizeof(int) * (end2 - i + 1)); //此处要控制范围
        }
        gap *= 2;
    }

    free(tmp);
}