#include"AVL.h"

void AVL_Test()
{
    int a[] = {8, 3, 10, 1, 6};

    AVLTree<int, int> At;
    for(auto& e : a)
    {
        At.Insert({e, e});
    }

    At.InOrder();

}

int main()
{
    AVL_Test();
    return 0;
}

