#include"AVL.h"

void AVL_Test()
{
    //int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
    //{ 8, 3, 1, 10, 6, 4, 7, 14, 13 };
    int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };


    AVLTree<int, int> At;
    for(auto& e : a)
    {
        //调试用
        // if(e == 4)
        // {
        //     int i = 0;
        // }
        At.Insert({e, e});
        //cout << At.isBalance() << endl;
    }

    cout << "-------" << endl;
    At.InOrder();
    cout << At.isBalance() << endl;
}

void test2()
{
    
}

int main()
{
    AVL_Test();
    return 0;
}

