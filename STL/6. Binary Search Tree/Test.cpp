#include "BST.h"

void Test()
{
    BSTree<int> BT;

    int a[] = {8, 7, 1, 5, 4, 6};
    for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
    {
        BT.Insert(a[i]);
    }
    
    BT.InOrder();
    
    for (auto e : a)
    {
        BT.Erase(e);
        BT.InOrder();
    }
    
    cout << BT.Find(5) << endl;
    cout << BT.Find(11) << endl;

}

int main()
{
    Test();
}