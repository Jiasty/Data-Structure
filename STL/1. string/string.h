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

        string(const string& s)
        {
            _str = new char[s._capacity + 1];
            strcpy(_str, s._str);
            _size = s._size;
            _capacity = s._capacity;
        }

        string& operator=(const string& s)
        {
            char* tmp = new char[s._capacity + 1];
            strcpy(tmp, s._str);
            delete[] _str;
            _str = tmp;
            _size = s._size;
            _capacity = s._capacity;

            return *this;
        }

        ~string()
        {
            delete[] _str;
            _str = nullptr;
            _size = _capacity = 0;
        }

        const char* c_str()
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
        void insert(size_t pos, const char* str)
        {
            
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

    private:
        char* _str;
        size_t _size;
        size_t _capacity;
    public:
        static const int npos;
    };

    const int string::npos = -1; //不加static
}