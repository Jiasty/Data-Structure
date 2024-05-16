#include "RBTree.h"

void test1()
{
    //int a[] = {4, 12, 24, 6, 1, 2, 4, 7};
    int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13, 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
    //int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };


    RBTree<int, int> RBT;
    for(auto& e : a)
    {
        //调试用
        // if(e == 4)
        // {
        //     int i = 0;
        // }
        RBT.Insert({e, e});
        //cout << At.isBalance() << endl;
    }

    cout << "-------" << endl;
    RBT.inOrder();
    cout << RBT.isBalance() << endl;
}

int main()
{
    test1();
    return 0;
}