#include<iostream>
using namespace std;

//搜索二叉树较 二分算法比较相像
template<class K>
struct BSTNode
{
    BSTNode(const K& val = K())
        :_left(nullptr)
        ,_right(nullptr)
        ,_val(val)
    {}

    BSTNode* _left;
    BSTNode* _right;
    K _val;
};

template<class K>
class BSTree
{
    typedef BSTNode<K> Node;
public:
    //插入一个值时，树中可能已经存在，存在则不插入，为了标记未插入，就用bool类型返回值返回false
    bool Insert(const K& val)  //注意:插入一定是往下走的，直至找到nullptr
    {
        //考虑 _root 为空的情况
        if(_root == nullptr)
        {
            _root = new Node(val);
            return true;
        }

        Node* cur = _root;
        Node* parent = nullptr;  //cur每次往下走都记录父亲位置的结点，以方便链接结点
        while(cur)
        {
            if(val > cur->_val)
            {
                parent = cur;
                cur = cur->_right;
            }
            else if(val < cur->_val)
            {
                parent = cur;
                cur = cur->_left;
            }
            else
                return false;
        }

        cur = new Node(val);
        if(val < parent->_val)
        {
            parent->_left = cur;
        }
        else
        {
            parent->_right = cur;
        }

        return true;
    }

    bool Find(const K& val)
    {
        Node* cur = _root;
        while(cur)
        {
            if(val > cur->_val)
                cur = cur->_right;
            else if(val < cur->_val)
                cur = cur->_left;
            else
                return true;
        }

        return false;
    }

    bool Erase(const K& val)
    {
        
    }

    //注意！！！！！！！！！！！！！！！1
    void InOrder()  
    {
        _InOrder(_root);
    }
private:
    void _InOrder(Node* root)  //这里为什么要传root? 外部调用时要传root，但是_root为私有，所以可以再封装
    {
        if(root == nullptr)
            return;
        
        _InOrder(root->_left);
        cout << root->_val << " ";
        _InOrder(root->_right);
    }

    // void InOrder()  
    // {
    //     if(_root == nullptr)
    //         return;
        
    //     InOrder((this->_root)->_left);  //如果不传 _root 此处就无法传 _root->_left 就无法递归
    //     cout << _root->_val << " ";
    //     InOrder((this->_root)->_right);
    // }
private:
    Node* _root = nullptr;
};