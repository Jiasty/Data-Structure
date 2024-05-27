#include<iostream>
#include<cstring>
#include<assert.h>

using namespace std;

namespace Jiastystring
{
    class string
    {
    public:
        //迭代器(顺序存储就适合原生指针)
        typedef char* iterator;
        typedef const char* const_iterator;
        iterator begin()
        {
            return _str;
        }
        iterator end()
        {
            return _str + _size;
        }
        const_iterator begin() const
        {
            return _str;
        }
        const_iterator end() const
        {
            return _str + _size;
        }

        //默认成员函数
        // string()
        //     :_str(new char[1]) //注意string是有\0的
        //     ,_size(0)
        //     ,_capacity(0)
        // {
        //     _str[0] = '\0';
        // }

        //此种有参构造调用三次strlen，代价大
        // string(const char* str)
        //     :_str(new char[strlen(str) + 1])
        //     ,_size(strlen(str))
        //     ,_capacity(strlen(str))
        // {
        //     strcpy(_str, str);
        // }

        //合二为一成默认构造函数
        string(const char* str = "") //不能传空也不能传'\0'（类型为char不能传给const char*）
            :_size(strlen(str)) //strlen不可传空
        {
            _capacity = _size;
            _str = new char[_capacity + 1];
            strcpy(_str, str);
        }

        //拷贝构造现代写法
        string(const string& s)
        {
            string tmp(s._str);
            swap(tmp);
        }
        //传统写法
        // string(const string& s)
        // {
        //     _str = new char[s._capacity + 1];
        //     strcpy(_str, s._str);
        //     _size = s._size;
        //     _capacity = s._capacity;
        // }

        //赋值现代写法
        string& operator=(const string& s)
        {

        }
        //传统写法
        // string& operator=(const string& s)
        // {
        //     char* tmp = new char[s._capacity + 1];
        //     strcpy(tmp, s._str);
        //     delete[] _str;
        //     _str = tmp;
        //     _size = s._size;
        //     _capacity = s._capacity;

        //     return *this;
        // }

        ~string()
        {
            delete[] _str;
            _str = nullptr;
            _size = _capacity = 0;
        }

        const char* c_str() const
        {
            return _str;
        }


        //遍历
        size_t size() const
        {
            return _size;
        }

        size_t capacity() const
        {
            return _capacity;
        }

        char& operator[](size_t pos)
        {
            //检查越界
            assert(pos < _size);

            return _str[pos];//_str在堆上，可以引用返回
        }

        const char& operator[](size_t pos) const
        {
            assert(pos < _size);

            return _str[pos];
        }

        //Modify
        void resize(size_t n, char ch = '\0')
        {
            if(n <= _size)
            {
                _str[n] = '\0';
            }
            else
            {
                reserve(n);
                for(size_t i = _size; i < n; i++)
                {
                    _str[i] = ch;
                }
                _str[n] = '\0';
                _size = n;
            }
        }

        void reserve(size_t n)
        {
            if(n > _capacity)  //n > _capacity时才扩容
            {
                char* tmp = new char[n + 1]; //永远提前为\0开一个空间
                strcpy(tmp, _str);
                delete[] _str;
                _str = tmp;
                _capacity = n;
            }
        }

        void push_back(char ch)
        {
            //扩容2倍
            if(_capacity == _size)
            {
                reserve(_capacity == 0 ? 4 : 2 * _capacity);
            }
            //插入
            _str[_size] = ch;
            ++_size;
            _str[_size] = '\0';

            //insert(_size, ch); //insert复用
        }

        void append(const char* str)
        {
            //扩容到需要的空间
            size_t len = strlen(str);
            if(_size + len > _capacity)
            {
                reserve(_size + len);
            }
            strcpy(_str + _size, str);//strcpy会将\0给拷贝下来
            _size += len;

            //insert(_size, str);
        }

        string& operator+=(char ch)
        {
            push_back(ch);
            return *this;
        }
        string& operator+=(const char* str)
        {
            append(str);
            return *this;
        }

        void insert(size_t pos, char ch)
        {
            assert(pos <= _size);
            //扩容2倍
            if(_capacity == _size)
            {
                reserve(_capacity == 0 ? 4 : 2 * _capacity);
            }
            //挪动数据 !!!!!!!!!!!!!!!!!!!!!!!!!!!!
            size_t end = _size + 1; //即使将end改为intleixing也会发生整型提升出错,所以还得强转一下pos为int.
            while(end > pos)  //要么改end = _size+1,让循环结束条件不是end<0时结束
            {
                _str[end] = _str[end - 1];
                --end; //end为size_t,不能小于0,所以当pos == 0时就不会结束循环
            }
            _str[pos] = ch;
            ++_size;//勿忘
        }
        void insert(size_t pos, const char* str)//!!!!!!!!!!!!
        {
            assert(pos <= _size);

            int n = strlen(str);
            if(n + _size > _capacity)
            {
                reserve(n + _size);
            }
            //挪动数据
            size_t end = _size + n;
            while(end > pos + n - 1)
            {
                _str[end] = _str[end - n];
                --end;
            }
            strncpy(_str + pos, str, n);//避免将\0覆盖进来就不能用strcpy
            _size += n;
        }

        void erase(size_t pos, size_t len = npos) //在pos位置删除len个字符
        {
            assert(pos < _size); //不能删\0

            if(len == npos || len >= _size - pos) //len + pos >= _size 会有溢出风险当len很大很大时
            {
                _str[pos] = '\0';
                _size = pos;
            }
            else
            {
                strcpy(_str + pos, _str + pos + len);
                _size -= len;
            }
        }

        void swap(string& str)//库里的swap有三次拷贝，代价大
        {
            //此处可以直接用库的wap换成员就行
            //一定要加std，编译器搜寻原则:就近寻找，所以会与自己写的swap函数冲突（报错:参数不匹配）
            std::swap(_str, str._str);//直接交换了地址，减少了自定义类型的构造
            std::swap(_size, str._size);
            std::swap(_capacity, str._capacity);
        }

        //从pos位置开始找ch
        size_t find(char ch, size_t pos = 0) const
        {
            for(size_t i = pos; i < _size; i++)
            {
                if(_str[i] == ch)
                    return i;
            }

            return npos;
        }

        //从pos位置开始找子串
        size_t find(const char* str, size_t pos = 0) const
        {
            assert(pos < _size);

            //字串匹配（strstr、KMP、BM）
            const char* tmp = strstr(_str + pos, str);
            if(!tmp)
                return npos;
            
            return tmp - _str;
        }

        //从pos位置开始取len个
        string substr(size_t pos = 0, size_t len = npos)
        {
            string sub;
            if(len == npos || len >= _size - pos)
            {
                len = _size;
            }

            for(size_t i = pos; i < pos + len; i++)
            {
                sub += _str[i];
            }
            return sub;
        }

        void clear()
        {
            _size = 0;
            _str[_size] = '\0';
        }

        //将关系比较的重载写到类里面，那么左值就固定了
        //...

    private:
        char* _str;
        size_t _size;
        size_t _capacity;
    public:
        static const int npos;
    };

    const int string::npos = -1; //不加static

    //重载了算法库的swap，避免了调用库的swap
    //为何不会和算法库的swap冲突? 算法库里的是模板，这里是定义好的函数，所以先调用此处
    void swap(string& x, string& y)
    {
        x.swap(y);
    }

    //!!!!!!!!!!!!!!!!!!!!!
    ostream& operator<<(ostream& out, const string& s)
    {
        for(auto ch : s)
        {
            cout << ch;
        }

        return out;
    }

    istream& operator>>(istream& in, string& s)
    {
        s.clear();//流提取是覆盖，所以得清数据

        char ch;
        //in >> ch; //c++读字符取不到空格和换行，默认为分割
        ch = in.get();
        char buff[128];
        size_t i = 0;
        //提前开空间减少扩容，但是如何确定开多大
        //采用buff块解决！！！！！！！！！！！！！！！！！！！！！！

        while(ch != ' ' && ch != '\n')
        {
            buff[i++] = ch;
            if(127 == i)
            {
                buff[127] = '\0';
                s += buff; //直接一把+=，减少了扩容
                i = 0;
            }
            ch = in.get();
        }

        if(i > 0)
        {
            buff[i] = '\0';
            s += buff;
        }

        return in;
    }

    istream& getline(istream& in, string& s)
    {
        s.clear();//流提取是覆盖，所以得清数据

        char ch;
        //in >> ch; //c++读字符取不到空格和换行，默认为分割
        ch = in.get();
        char buff[128];
        size_t i = 0;
        //提前开空间减少扩容，但是如何确定开多大
        //采用buff块解决！！！！！！！！！！！！！！！！！！！！！！

        while(ch != '\n')
        {
            buff[i++] = ch;
            if(127 == i)
            {
                buff[127] = '\0';
                s += buff; //直接一把+=，减少了扩容
                i = 0;
            }
            ch = in.get();
        }

        if(i > 0)
        {
            buff[i] = '\0';
            s += buff;
        }

        return in;

        // s.clear();

        // char ch;
        // ch = in.get();
        // while(ch != '\n')
        // {
        //     s += ch;
        //     in >> ch;
        // }

        // return in;   
    }
}