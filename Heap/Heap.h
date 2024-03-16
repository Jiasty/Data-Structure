#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

//堆中某个节点的值总是不大于或不小于其父节点的值。
//将根节点最大的堆叫做最大堆或大根堆，根节点最小的堆叫做最小堆或小根堆。
/////////此处为小堆
typedef int HeapDataType;

//通常把堆(一种完全二叉树)使用顺序结构的数组来存储，完全二叉树适合用顺序结构存储
typedef struct Heap
{
    HeapDataType* arr; //数据域，底层为数组，逻辑结构为完全二叉树
    int size; //有效数据个数
    int capacity; //容量
}Heap;

// 堆的构建
void HeapCreate(Heap* hp);
// 堆的销毁
void HeapDestory(Heap* hp);
// 堆的插入
//插入的数据不符合堆的规定时需要调整数据
//知道子结点位置求父结点位置 index[dad] == (index[son] - 1) / 2
void HeapPush(Heap* hp, HeapDataType x);
// 堆的删除！！！，规定删除堆顶结点，根结点，删尾结点没意义
// 思想:应先交换头尾结点(就是为了方便删除)，再尾删，再向下调整。
//知道父结点位置求子结点位置 index[left] == index[dad] * 2 + 1
//                         index[right] == (index[dad] + 1) * 2
void HeapPop(Heap* hp);
// 取堆顶的数据
HeapDataType HeapTop(Heap* hp);
// 堆的数据个数
int HeapSize(Heap* hp);
// 堆的判空，空为true
bool HeapEmpty(Heap* hp);

//交换函数
void Swap(HeapDataType* p1, HeapDataType* p2);
//向上调整，child是任意一个孩子的下标
void AdjustUp(HeapDataType* a, int child);
//向下调整,因为得用 hp->size 又没有传hp，所以多加一个参数
void AdjustDown(HeapDataType* a, int size, int parent);

//堆打印数据
void HeapPrint(Heap* hp);