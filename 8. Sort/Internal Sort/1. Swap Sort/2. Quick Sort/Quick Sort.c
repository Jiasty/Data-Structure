#include<stdio.h>

void Hoare_QuickSort(int* arr, int begin, int end);
void Dig_QuickSort();
void Pointer_QuickSort();

int PartSort1(int* arr, int begin, int end);
int PartSort2();
int PartSort3();
int GetMidi(int* arr, int begin, int end);
void Swap(int* p1, int* p2);


int main()
{
    //int a[] = {6, 1, 2, 7, 9, 3, 4, 5, 10, 8};
    int a[] = {6, 1, 2, 6, 7, 9, 6, 3, 4, 5, 10, 8};
    Hoare_QuickSort(a, 0, sizeof(a) / sizeof(a[0]) - 1);
    //Dig_QuickSort();
    //Pointer_QuickSort();
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		printf("%d ", a[i]);
	}

    return 0;
}


//时间复杂度:O(NlogN)
//最坏的情况:O(N ^ 2)  当完全有序时
//快排适合重复数据比较多的情况,不适合有序的情况（因为每次取key都是第一个数）,为了解决这个问题可以采用三数取中，快速找到中间的key

//思路:定第一个数为key，然后右指针先找比key小的数，然后左指针找比key大的数，再交换，
//最后两指针相遇的数与key交换（此时一定比key小），原因是右指针先开始行动
//霍尔版本的快排坑比较多，不好控制
void Hoare_QuickSort(int *arr, int begin, int end) //由于快排为递归，如果传数组个数就不好递归
{
    if(begin >= end) //n == 1或者不存在（>）时结束
        return;

    int keyi = PartSort1(arr, begin, end);
    
    Hoare_QuickSort(arr, begin, keyi - 1);
    Hoare_QuickSort(arr, keyi + 1, end);
}

//挖坑法
void Dig_QuickSort()
{

}

//前后指针法（）
void Pointer_QuickSort()
{

}

//霍尔版本
int PartSort1(int* arr, int begin, int end)
{
    int midi = GetMidi(arr, begin, end);
    Swap(&arr[midi], &arr[begin]);//快排如果中间数做key十分麻烦，所以三数取中后换到begin位置！！！！！

    int left = begin, right = end;  //left从begin+1位置开始会出现left == right直接交换key（但是有可能key不小于相遇的数）
    //之前让left从begin+1位置开始是为了进入下方的循环，此时循环加上了=的情况，也会进入循环，就可以让left从begin开始
    int keyi = begin;  //记录key的下标最好,如果记录值无法知道key的位置并且该值为一个局部变量
    while(left < right)
    {
        //右找小
        //注意外部的left < right控制整体的排序是否结束，内部不受控制，以免越界内部也得判断left < right
        //一定是找小和大的数，不找相同的数  
        while(left < right && arr[right] >= arr[keyi])
        {
            --right;
        }
        //左找大
        while(left < right && arr[left] <= arr[keyi])
        {
            ++left;
        }
        Swap(&arr[left], &arr[right]);

    }

    Swap(&arr[keyi], &arr[right]);
    keyi = left;
    return keyi;
    //当区间数据量小于一定程度时继续递归消耗很大，可以采用插入排序进行小区间优化
    //release下其实没啥效果
    // if(end - begin + 1 <= 10)
    // {
    //     InsertSort(arr + begin, end - begin + 1);
    // }
    // else
    // {
    //     //...
    // }
    //[begin, keyi - 1] kei [keyi + 1, end] 
}
//挖坑法
int PartSort2()
{

}
//前后指针法
int PartSort3()
{

}

int GetMidi(int* arr, int begin, int end)
{
    int midi = (begin + end) / 2;
	// begin midi end 三个数选中位数
	if (arr[begin] < arr[midi])
	{
		if (arr[midi] < arr[end])
			return midi;
		else if (arr[begin] > arr[end])
			return begin;
		else
			return end;
	}
	else // a[begin] > a[midi]
	{
		if (arr[midi] > arr[end])
			return midi;
		else if (arr[begin] < arr[end])
			return begin;
		else
			return end;
	}
}

void Swap(int* p1, int* p2)
{
    int tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}