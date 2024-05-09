#include<stdio.h>
#include"Stack.h"

void QuickSort(int* arr, int begin, int end);
void QuickSortNonR(int* arr, int begin, int end);

void QuickSort_Trisection(int* arr, int begin, int end);
int GetRandom(int* arr, int begin, int end);

int PartSort1(int* arr, int begin, int end);
int PartSort2(int *arr, int begin, int end);
int PartSort3(int *arr, int begin, int end);
int GetMidi(int* arr, int begin, int end);
void Swap(int* p1, int* p2);


int main()
{
    //int a[] = {6, 1, 2, 7, 9, 3, 4, 5, 10, 8};
    int a[] = {6, 1, 2, 6, 7, 9, 6, 3, 4, 5, 10, 8};

    //QuickSort(a, 0, sizeof(a) / sizeof(a[0]) - 1);
    //QuickSortNonR(a, 0, sizeof(a) / sizeof(a[0]) - 1);
    QuickSort_Trisection(a, 0, sizeof(a) / sizeof(a[0]) - 1);
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		printf("%d ", a[i]);
	}

    return 0;
}


//时间复杂度:O(NlogN)
//最坏的情况:O(N ^ 2)  当完全有序时
//快排适合重复数据比较多的情况,不适合有序的情况（因为每次取key都是第一个数）,为了解决这个问题可以采用三数取中，快速找到中间的key
void QuickSort(int *arr, int begin, int end) //由于快排为递归，如果传数组个数就不好递归
{
    if(begin >= end) //n == 1或者不存在（>）时结束
        return;

    int keyi = PartSort3(arr, begin, end);
    
    QuickSort(arr, begin, keyi - 1);
    QuickSort(arr, keyi + 1, end);
}

//借助栈来模拟递归的过程，将递归区间入栈
void QuickSortNonR(int* arr, int begin, int end)
{
    Stack ST;
    StackInit(&ST);

    //入左右区间
    StackPush(&ST, end);
    StackPush(&ST, begin);

    while(!StackEmpty(&ST))
    {
        //出左右区间并记录
        int left = StackTop(&ST);
        StackPop(&ST);
        int right = StackTop(&ST);
        StackPop(&ST);

        //进行单趟排序
        int keyi = PartSort3(arr, left, right);

        //[begin, keyi - 1] keyi [keyi + 1, end]
        //再次入区间
        if(left < keyi - 1) //判断为了避免某一段区间没有值或只有一个值还去分割
        {
            StackPush(&ST, keyi - 1);
            StackPush(&ST, left);
        }
        if(right > keyi + 1)
        {
            StackPush(&ST, end);
            StackPush(&ST, keyi + 1);
        }
    }

    StackDestroy(&ST);
}

///////////////////////////////////////////////////////////////////////
//霍尔版本
//思路:定第一个数为key，然后右指针先找比key小的数，然后左指针找比key大的数，再交换，
//最后两指针相遇的数与key交换（此时一定比key小），原因是右指针先开始行动
//霍尔版本的快排坑比较多，不好控制
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
    //[begin, keyi - 1] keyi [keyi + 1, end] 
}
//挖坑法
//思路:单趟定第一个数为key，将其定为坑，右边开始找小，交换填坑，形成新的坑位，左边开始找大，交换填坑，
//直到两指针相遇时中止，将原本的key填入到相遇的坑位。
int PartSort2(int* arr, int begin, int end)
{
    int midi = GetMidi(arr, begin, end);
    Swap(&arr[midi], &arr[begin]);

    int key = arr[begin];
    int hole = begin;

    while(begin < end)
    {
        //右边找小填左边的坑
        while(begin < end && arr[end] >= key)
        {
            --end;
        }
        arr[hole] = arr[end]; //此处挖坑法直接覆盖数据就好，不用记录下标
        hole = end; //更新坑位
        while(begin < end && arr[begin] <= key)
        {
            ++begin;
        }
        arr[hole] = arr[begin];
        hole = begin;
    }
    arr[hole] = key; //相遇结束，将key填入坑位

    return hole;
}
//前后指针法
//思路:cur指针（后）找比key小的值停住，然后prev指针找大，然后交换两值，最后cur结束后，prev处的值与key交换。重复
//cur与prev之间的值都是比key大的值，就像是把大的值往后推
int PartSort3(int* arr, int begin, int end)
{
    int midi = GetMidi(arr, begin, end);
    Swap(&arr[midi], &arr[begin]);

    int prev = begin, cur = prev + 1;
    int keyi = begin;

    while(cur <= end) //cur < end最后一个值就进不去
    {
        //简化
        if(arr[cur] < arr[keyi] && ++prev != cur)//只有cur处的值比key小时才进去，其他情况就++cur
            Swap(&arr[prev], &arr[cur]);
        ++cur;

        // if(arr[cur] < arr[keyi])//只有cur处的值比key小时才进去，其他情况就++cur
        // {
        //     ++prev; //注意cur与prev之间的值都是比key大的值，所以prev++一下就行
        //     Swap(&arr[prev], &arr[cur]);
        //     ++cur;
        // }
        // else
        // {
        //     ++cur;
        // }
    }
    Swap(&arr[keyi], &arr[prev]);
    keyi = prev;

    return keyi;
}

//三数取中选key，解决数据重复导致效率减慢的问题
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


///////////////////////////////////////////////////////////
//三分数组方式优化 < = >
void QuickSort_Trisection(int* arr, int begin, int end)
{
    if(begin >= end)
        return;

    //数组分三块
    int key = GetRandom(arr, begin, end);
    int left = begin - 1, right = end + 1;
    int i = begin;

    while(i < right)
    {
        if(arr[i] < key)
        {
            Swap(&arr[++left], &arr[i++]);
        }
        else if(arr[i] == key)
        {
            i++;
        }
        else
        {
            Swap(&arr[--right], &arr[i]);
        }
    }

    //[begin, left] [left + 1, right - 1] [right, end];
    QuickSort_Trisection(arr, begin, left);
    QuickSort_Trisection(arr, right, end);
}

int GetRandom(int* arr, int begin, int end)
{
    int r = rand();
    return arr[(r % (end - begin + 1)) + begin];
}