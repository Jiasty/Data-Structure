#include"SList.h"

//初始化可以不要
void InitSList(SLNode* plist){}
//销毁链表
void DestroySList(SLNode** pplist)
{
    assert(pplist); //这里检查什么？检查链表是否存在？

    SLNode* cur = *pplist;
	while (cur)
	{
		SLNode* next = cur->next;
		free(cur);
		cur = next;
	}

	*pplist = NULL;

    //是否可以理解为一个一个尾删？
    // while(*plist)
    // {
    //     SListPopBack(pplist);
    // }
}

// 动态申请一个结点,顺便输入val值ok
SLNode* BuySListNode(SLNDataType x)
{
    SLNode* newNode = (SLNode*)malloc(sizeof(SLNode));
    if(newNode == NULL)
    {
        perror("malloc fail"); //了解一下
        exit(-1); //什么意思？
        //return; 这里函数有返回值
    }
    newNode->val = x;
    newNode->next = NULL;
    return newNode;
}

// 单链表打印ok
void SListPrint(SLNode* plist)
{
    SLNode* cur = plist; //拷贝一份plist，plist不做改动，其实这里也不会改变外部的头指针，因为形参只是实参的拷贝，形参的改变不会影响实参
    while(cur != NULL)
    {
        printf("%d->",cur->val);
        cur = cur->next;
    }
    printf("NULL\n");
}
// 单链表尾插ok
void SListPushBack(SLNode** pplist, SLNDataType x) //这里传二级指针是因为需要更改头结点地址，要更改地址，就得取到地址的地址
{
    SLNode* newNode = BuySListNode(x);
    if(*pplist == NULL) //意味着头指针没有指向任何一个结点，这里直接让其指向新申请的结点就行
    {
        *pplist = newNode;
    }
    else
    {
        //非空情况，遍历至尾再尾插
        SLNode* tail = *pplist;
        while(tail->next != NULL)
        {
            tail = tail->next;
        }
        tail->next = newNode;
    }
}
// 单链表的头插ok
void SListPushFront(SLNode** pplist, SLNDataType x)
{
    SLNode* newNode = BuySListNode(x);
    
    //无论*pplist是否为NULL都可以实现
    newNode->next = *pplist;
    *pplist = newNode;
}
// 单链表的尾删?
void SListPopBack(SLNode** pplist)
{
    //为空就不删
    assert(*pplist);

    //当只有一个结点的时候需要特殊判断
    //if(*pplist->next == NULL) 错点:->优先级比*高，所以 *pplist 应用括号包起来
    if((*pplist)->next == NULL)
    {
        free(*pplist);
        *pplist = NULL;
    }
    else
    {
        SLNode* tail = *pplist;
		while (tail->next->next != NULL)
		{
			tail = tail->next;
		}

		free(tail->next);
		tail->next = NULL;
    }
}
// 单链表头删ok
void SListPopFront(SLNode** pplist)
{
    assert(*pplist);

    //头删在一个结点和多个结点的情况下，以下代码都能实现
    SLNode* tmp = *pplist;
    *pplist = tmp->next;
    free(tmp);
    tmp = NULL;

    // SLNode* tmp = *pplist;
	// free(tmp);   //此处先释放tmp其实也没问题，因为 (*pplist)->next 是记住了tmp的位置
	// *pplist = (*pplist)->next;
    // tmp = NULL;
}
// 单链表查找ok
SLNode* SListFind(SLNode* plist, SLNDataType x) //只读，传一级指针就可以
{

    // if(plist == NULL)
    // {
    //     return NULL;
    // }
    // else
    // {
    //     SLNode* cur = plist;
    //     while(cur)
    //     {
    //         if(cur->val == x)
    //         {
    //             return cur;
    //         }
    //         cur = cur->next;
    //     }
    // }
    //上方代码比较冗长，可以优化成下方

    SLNode* cur = plist;
	while (cur)
	{
		if (cur->val == x)
		{
			return cur;
		}
		else
		{
			cur = cur->next;
		}
	}

	return NULL;
}
// 单链表在pos位置之后插入x
// 分析思考为什么不在pos位置之前插入？
void SListInsertAfter(SLNode* pos, SLNDataType x) //pos是指某个结点的地址，可以用查找接口
{
    //这里和SListEraseAfter(SLNode* pos)为啥不用检查assert(pplist);和assert(*pplist);？
    assert(pos); //pos是一个有效地址

    //适合pos为头结点、中间位置结点和尾结点的情况
    SLNode* newNode = BuySListNode(x);
    newNode->next = pos->next;
    pos->next = newNode;
}
// 单链表删除pos位置之后的值
// 分析思考为什么不删除pos位置？
void SListEraseAfter(SLNode* pos)
{
    assert(pos);
	assert(pos->next); //pos下一个位置有结点才删除

    SLNode* tmp = pos->next;
    pos->next = tmp->next;
    //pos->next = pos->next->next;
    free(tmp);
    tmp = NULL;
}

//在pos前的插入和删除 (error!!! :implicit declaration of function 'SLTErase' [-Wimplicit-function-declaration])
void SLTInsert(SLNode** pplist, SLNode* pos, SLNDataType x) //pos是指某个结点的地址，可以用查找接口
{
    // 严格限定pos一定是链表里面的一个有效节点
    assert(pos); //pos是一个有效地址
	assert(pplist); //链表存在。 为何前面有 pplist 的接口不需要检查 pplist，这里需要单独检查？
	assert(*pplist); //链表存在结点

    //1.链表为空的情况
    //2.链表只有一个结点的情况
    //3.链表有一个以上结点的情况

    if(pos == *pplist) //头插
    {
        SListPushFront(pplist, x);
    }
    else
    {
        SLNode* newNode = BuySListNode(x);
        SLNode* prev = *pplist;
        while(prev->next != pos)
        {
            prev = prev->next;
        }
        //以下顺序可以交换，因为pos的位置可知，即使先改 prev->next 也能找到pos
        prev->next = newNode;
        newNode->next = pos;
    }
}
void SLTErase(SLNode** pplist, SLNode* pos)
{
    assert(pos);
    assert(pplist);
	assert(*pplist);

    if(pos == *pplist) //头删
    {
        SListPopFront(pplist);
    }
    else
    {
        // SLNode* prev = *pplist;
        // while(prev->next->next != pos)
        // {
        //     prev = prev->next;
        // }
        // SLNode* prevnext = prev->next;
        // prev = prevnext->next;
        // free(prevnext);
        // prevnext = NULL;

        //删除pos位置
        SLNode* prev = *pplist;
		while (prev->next != pos)
		{
			prev = prev->next;
		}

		prev->next = pos->next;
		free(pos);
		pos = NULL;
    }
}