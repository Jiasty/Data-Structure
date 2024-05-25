#include<iostream>
#include<cstring>
#include<assert.h>

using namespace std;

namespace Jiastystring
{
    class string
    {
    public:
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
    private:
        char* _str;
        size_t _size;
        size_t _capacity;
    };
}