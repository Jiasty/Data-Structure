#include"List.h"

//双链表初始化，初始化出头节点OK
//双链表要单独写Init函数的原因就是它独特的结构，带有头节点且循环
ListNode* ListInit()
{
    ListNode* plist = ListCreatNode(-1);

    //一定注意与创普通结点不同，这里是双链表头节点，一定得循环
	plist->next = plist;
	plist->prev = plist;

	return plist;
}

// 创建一个双链表的结点并返回地址.顺带初始化val OK
//ListNode* ListCreatNode()不初始化val
ListNode* ListCreatNode(LTDataType x)
{
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if(newNode == NULL)
    {
        perror("malloc fail");
        exit(-1); //注意函数返回值类型ListNode* 别用return
    }

    newNode->val = x;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}
// 双向链表销毁
void ListDestory(ListNode* plist)
{
    assert(plist);

    ListNode* cur = plist->next;
    while(cur != plist)
    {
        ListNode* curNext = cur->next;
        free(cur);
        plist->next = curNext;
        curNext->prev = plist;
        cur = curNext;

        //其实不用再链接结点
        // ListNode* next = cur->next;
		// free(cur);
		// cur = next;
    }
    cur = NULL;
    free(plist);
    plist = NULL;

    printf("List have been destoried\n");
}

// 双向链表打印OK
void ListPrint(ListNode* plist)
{
    assert(plist);

    printf("head<=>");

    ListNode* cur = plist->next; //因为是双链表，有效结点为 plist->next
    while(cur != plist) //while(cur)注意这是双向链表，没有空的时候
    {
        printf("%d<=>",cur->val);
        cur = cur->next;
    }
    printf("head\n");
}

// 双向链表尾插
void ListPushBack(ListNode* plist, LTDataType x)
{
    assert(plist);

    ListNode* newNode = ListCreatNode(x);
    ListNode* tail = plist->prev;

    //不管有没有有效结点都适用
	// phead            tail  newnode
	tail->next = newNode;
	newNode->prev = tail;
	newNode->next = plist;
	plist->prev = newNode;

    //ListInsert(plist, x); //在plist前面插，就是尾插

    // //以下代码就会出现尾插出问题 :head<=>4<=>head why?
    // if(plist->next == plist) //只有头节点
    // {
    //     plist->next = newNode;
    //     newNode->prev = plist;
    //     newNode->next = plist;
    //     plist->prev = newNode;
    // }
    // else //有其他结点
    // {
    //     tail->next = newNode;
    //     newNode->prev = tail;
    //     newNode->next = plist;
    //     plist->next = newNode;
        
    // }
}
// 双向链表尾删OK
void ListPopBack(ListNode* plist)
{
    assert(plist);
    assert(plist->next != plist);
    // if(plist->next == plist)
    //     return;

    ListNode* tail = plist->prev;
    ListNode* tailPrev = tail->prev;

    free(tail);
    tailPrev->next = plist;
    plist->prev = tailPrev;
    tail = NULL;

    //ListErase(plist, plist->prev);

    //一个指针控制
    // ListNode* tail = plist->prev;
    // tail->prev->next = plist;
    // plist->prev = tail->prev;
    // free(tail);
    // tail = NULL;
}
// 双向链表头插ok
void ListPushFront(ListNode* plist, LTDataType x)
{
    assert(plist);

    ListNode* newNode = ListCreatNode(x);

    newNode->next = plist->next;
    plist->next->prev = newNode;
    plist->next = newNode;
    newNode->prev = plist;

    //ListInsert(plist->next, x);
}
// 双向链表头删ok
void ListPopFront(ListNode* plist)
{
    assert(plist);
    assert(plist->next != plist);
    // if(plist->next == plist)
    //     return;

    ListNode* popNext = plist->next->next;

    free(plist->next);
    plist->next = popNext;
    popNext->prev = plist;

    //ListErase(plist, plist->next);

    //LTNode* first = phead->next;
	//LTNode* second = first->next;

	//phead->next = second;
	//second->prev = phead;
	//free(first);
	//first = NULL;
}

// 双向链表查找ok
ListNode* ListFind(ListNode* plist, LTDataType x)
{
    assert(plist);

    ListNode* cur = plist->next;
    while(cur != plist)
    {
        if(cur->val == x)
        {
            return cur;
        }
        cur = cur->next;
    }

    return NULL; //这一步一定注意返回没有找到的情况
}

// 双向链表在pos的前面进行插入ok
void ListInsert(ListNode* pos, LTDataType x)
{
    assert(pos);

    ListNode* newNode = ListCreatNode(x);
    pos->prev->next = newNode;
    newNode->prev = pos->prev;
    newNode->next = pos;
    pos->prev = newNode;
}
// 双向链表删除pos位置的结点ok
void ListErase(ListNode* plist, ListNode* pos)
{
    assert(pos);
    assert(pos != plist); 

    pos->prev->next = pos->next;
    pos->next->prev = pos->prev;
    free(pos);
    pos = NULL;
}

// 删除pos位置不可避免plist被删
// void LTErase(LTNode* pos)
// {
// 	assert(pos);

// 	LTNode* posNext = pos->next;
// 	LTNode* posPrev = pos->prev;

// 	posPrev->next = posNext;
// 	posNext->prev = posPrev;
// 	free(pos);
// 	//pos = NULL;
// }
