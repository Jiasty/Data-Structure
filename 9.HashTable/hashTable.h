#pragma once
#include<iostream>
#include<vector>
using namespace std;

template<class K>
struct HashFunc
{
    size_t operator()(const K& key)
	{
		return (size_t)key; //能强转整型的转整型
        //有的类型无法强转就得特化
	}
};

//特化
template<>
struct HashFunc<string>
{
    // abcd
	// bcad
	// aadd
	// BKDR
	size_t operator()(const string& key)
	{
		size_t hash = 0;
		for (auto ch : key)
		{
			hash *= 131;
			hash += ch;
		}

		return hash;
	}
};

namespace open_address
{
    //以下使用开放定址法来实现HashTable
    enum State //加标记来解决删除时造成的数据丢失问题
    {
        EMPTY,
        EXIST,
        DELETE
    };

    struct StringHashFunc
	{
		// abcd
		// bcad
		// aadd
		// BKDR
		size_t operator()(const string& key)
		{
			size_t hash = 0;
			for (auto ch : key)
			{
				hash *= 131;
				hash += ch;
			}

			return hash;
		}
	};

    template<class K, class V>
    struct hashData
    {
        pair<K, V> _kv;
        State _state = EMPTY;  //为何此处缺省值给EMPTY而不是EXIST? 构造函数先开好了10个空间，此时应该都是EMPTY，插入后再改状态
    };

    template<class K, class V, class Hash = HashFunc<K>>
    class hashTable
    {
    public:
        hashTable()
        {
            _table.resize(10);
        }


        bool Insert(const pair<K, V>& kv)
        {
            if(Find(kv.first))
                return false;

            //检查装填因子，看是否扩容
            if(_n * 10 / _table.size() >= 7) //原式子_n / _table.size() >= 0.7，为控制为整型，两边同时 *10
            {
                //扩容
                //由于扩容后各个元素与地址之间的映射关系会改变，所以直接创建新表，释放旧表

                //size_t newsize = _tables.size() * 2;
				//vector<HashData<K, V>> newtables(newsize);

                hashTable<K, V> newHTable; //创建新哈希表而非新vector，可以复用哈希表的Insert
                newHTable._table.resize(_table.size() * 2);

                for(size_t i = 0; i < _table.size(); i++)
                {
                    if(_table[i]._state == EXIST)
                    {
                        newHTable.Insert(_table[i]._kv);
                    }
                }
                
                _table.swap(newHTable._table);
            }

            //先根据哈希函数找到对应位置
            //如果kv.first不是整型，则无法取模，应采用仿函数来解决
            Hash h;//创建仿函数对象
            size_t addr = h(kv.first) % _table.size();
            
            //线性探测，如果未冲突不进入探测
            while(_table[addr]._state == EXIST)
            {
                addr = (addr + 1) % _table.size();
            }
            _table[addr]._kv = kv;
            _table[addr]._state = EXIST;
            ++_n;

            return true;
        }

        hashData<K, V>* Find(const K& key)
        {  
            Hash h;
            size_t addr = h(key) % _table.size();

            //线性探测
            while(_table[addr]._state != EMPTY)
            {
                if(_table[addr]._state == EXIST && _table[addr]._kv.first == key) //注意一定要判断是否存在，可能已经删除
                    return &_table[addr];

                addr = (addr + 1) % _table.size();
            }

            return nullptr;
        }

        bool Erase(const K& key)
        {
            hashData<K, V>* ret = Find(key);

            if(ret == nullptr)
            {
                return false;
            }
            else
            {
                ret->_state = DELETE;
                --_n;

                return true;
            }
        }

    private:
        vector<hashData<K, V>> _table;
        size_t _n; //记录已存储数据个数（vector里面的_size是记录可用地址个数,记住取模也是模size而非capacity）？？？
    };

    void TestHT1()
	{
		int a[] = { 10001,11,55,24,19,12,31 };
		hashTable<int, int> ht;
		for (auto e : a)
		{
			ht.Insert(make_pair(e, e));
		}

		cout << ht.Find(55) << endl;
		cout << ht.Find(31) << endl;

		ht.Erase(55);
		cout << ht.Find(55) << endl;
		cout << ht.Find(31) << endl;
	}

	void TestHT2()
	{
		int a[] = { 10001,11,55,24,19,12,31 };
		hashTable<int, int> ht;
		for (auto e : a)
		{
			ht.Insert(make_pair(e, e));
		}

		ht.Insert(make_pair(32, 32));
		ht.Insert(make_pair(32, 32));
	}

    struct Person
	{
		//string _id;

		string _name;
		int _age;
		string school;
	};

	void TestHT3()
	{
		hashTable<Person, int> xxht;

		//HashTable<string, int, StringHashFunc> ht;
		hashTable<string, int> ht;
		ht.Insert(make_pair("sort", 1));
		ht.Insert(make_pair("left", 1));
		ht.Insert(make_pair("insert", 1));

		cout << StringHashFunc()("bacd") << endl;
		cout << StringHashFunc()("abcd") << endl;
		cout << StringHashFunc()("aadd") << endl;
	}
}


namespace hash_bucket
{
    template<class T>
    class hashNode
    {
        T _data;
        hashNode<T>* _next;

        hashNode(const T& data)//哈希结点创造出来一定有值
            :_data(data)
            ,_next(nullptr)
        {}
    };

    template<class K, class T>
    class hashTable
    {
        typedef hashNode<T> Node;
    public:

    bool Insert(const Node& node)
    {

    }

    bool Erase()
    {

    }

    Node* Find(const K& key)
    {
        
    }

    private:
    vector<Node*> _table;
    size_t _n;
    };
}