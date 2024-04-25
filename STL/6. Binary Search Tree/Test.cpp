#include "BST.h"

void Test()
{
    BSTree<int> BT;

    BT.Insert(8);
    BT.Insert(1);
    BT.Insert(5);
    BT.Insert(6);
    BT.InOrder();
    cout << BT.Find(5) << endl;

}

int main()
{
    Test();
}