#pragma once
#include<iostream>
#include<vector>

template<class T>
class UnionFindSet
{
public:
    UnionFindSet(size_t n)
        :_ufs(n, -1)  //初始状态给 -1
    {}

    //合并集合
    void Union(int x1, int x2)
    {
        //保存的原因是后面合并需要用根的位置，但是x1和x2不一定就是根
        int root1 = Findroot(x1);
        int root2 = Findroot(x2);
        //判断是否在一个集合，不在再合并
        if(root1 == root2)
            return;

        //开始合并 小优化:个数少的往个数多的合并，这样只有较少的数的层数增加
        if(abs(_ufs[root1]) < abs(_ufs[root2]))
            swap(root1, root2);

        _ufs[root1] += _ufs[root2];
        _ufs[root2] = root1;
    }

    //寻找该元素所在集合的名称
    int Findroot(int x)
    {
        int root_index = x;
        while(_ufs[root_index] >= 0)
        {
            root_index = _ufs[root_index];
        }

        return root_index;
    }

    //是否在同一个集合
    bool InSet(int x1, int x2)
    {
        return Findroot(x1) == Findroot(x2);
    }

    //有多少集合
    size_t SetSize()
    {
        size_t total = 0;
        //有几个负数就有几个集合
        for(int i = 0; i < _ufs.size(); i++)
        {
            if(_ufs[i] < 0)
                ++total;
        }

        return total;
    }
private:
    vector<T> _ufs;  //假设给的就是编号
    //map
};