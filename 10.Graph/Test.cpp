#include"UnionFindSet.h"


void test_UnionFindSet()
{
    UnionFindSet<int> ufs(5);

    ufs.Union(2, 4);
    cout << ufs.Findroot(4) << endl;
    cout << ufs.SetSize() << endl;
    cout << ufs.InSet(1, 4) << endl;
}

int main()
{
    test_UnionFindSet();
    return 0;
}