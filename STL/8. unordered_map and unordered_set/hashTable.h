#pragma once
#include<iostream>
#include<vector>
#include<assert.h>
using namespace std;

namespace open_address
{
    //以下使用开放定址法来实现HashTable
    enum State //加标记来解决删除时造成的数据丢失问题
    {
        EMPTY,
        EXIST,
        DELETE
    };

    template<class K, class V>
    class hashData
    {
        pair<K, V> _kv;
        State _state;
    };

    template<class K, class V>
    class hashTable
    {
    public:
        bool Insert(const hashData<K, V>* kv)
        {
            //先根据哈希函数找到对应位置
            int addr = kv->_kv.first % _table.size();
        }

        hashData<K, V>* Find()
        {

        }

        bool Erase(hashData<K, V>* kv)
        {
            assert(kv->_state == EXIST);
            
            data->_state = DELETE;
        }

    private:
        vector<hashData<K, V>> _table;
        size_t _n; //记录已存储数据个数（vector里面的_size是记录可用地址个数,记住取模也是模size而非capacity）？？？
    };
}


namespace hash_bucket
{
    template<class K, class V>
    class hashData
    {
        pair<K, V> _kv;
    };

    template<class K, class V>
    class hashTable
    {
    public:

    private:

    };
}