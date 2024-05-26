#include"string.h"

using namespace Jiastystring;

void test1()
{
    Jiastystring::string str1("You are my apple of eyes");
    Jiastystring::string:: iterator it = str1.begin();
    while(it != str1.end())
    {
        cout << *it++ << " ";
    }
    cout << endl;

    for(auto e : str1)
    {
        cout << e << " ";
    }
    cout << endl;

    const Jiastystring::string str2("hello world");
    Jiastystring::string:: const_iterator cit = str2.begin();
    while(cit != str2.end())
    {
        //(*cit)++; 不可修改
        cout << *cit++ << " ";
    }
    cout << endl;

    for(auto ch : str2)
    {
        cout << ch << " ";
    }
    cout << endl;
    
}

void test2()
{
    Jiastystring::string str1("hello world");
    str1.push_back('1');
    str1.push_back('2');
    str1.append("125715");
    str1 += '0';
    str1 += "1111";
    cout << str1.c_str() << endl;
    for(auto ch : str1)
    {
        cout << ch << " ";
    }
    cout << endl;
}

void test3()
{
    //insert and erase
    Jiastystring::string str1("hello world");
    str1.insert(5, 'x');
    cout << str1.c_str() << endl;
    str1.insert(0, 'x');
    cout << str1.c_str() << endl;

    str1.erase(5, 3);
    cout << str1.c_str() << endl;

    str1.resize(20, 'x');
    cout << str1.c_str() << endl;
}

void test4()
{
    Jiastystring::string str1("hello world");

    Jiastystring::string str2 = str1;//不深拷贝就会在析构时释放两次
}

int main()
{
    //test1();
    //test2();
    //test3();
    test4();
    return 0;
}