#pragma once
#include<iostream>
using namespace std;


enum Color
{
    RED,
    BLACK
};

//改红黑树，泛型编程来确定k还是kv模型
template<class T>
struct RBTreeNode
{
    RBTreeNode<T>* _left;
    RBTreeNode<T>* _right;
    RBTreeNode<T>* _parent;
    T _data;

    Color _col;

    RBTreeNode(const T& data)
        :_left(nullptr)
        ,_right(nullptr)
        ,_parent(nullptr)
        ,_data(data)
        ,_col(RED)
    {}
};

template<class T, class Ref, class Ptr>
struct __RBTreeIterator
{
    typedef __RBTreeIterator<T, Ref, Ptr> Self;

    Self& operator!=(const Self& s)
    {
        
    }
};

//此处的K模板参数一定不能删，因为此时实在RBTree.h里面改，需要map和set都照顾，未实例化前不知道到底是map还是set，find时map和set不同
template<class K, class T, class KerOfT>
class RBTree
{
    typedef RBTreeNode<T> Node;
public:
    RBTree() = default; //default强制生成构造函数

    RBTree(const RBTree<K, T, KerOfT>& t)
    {

    }

    ~RBTree()
    {

    }

    bool Insert(const T& data)
    {
        if(_root == nullptr)
        {
            _root = new Node(data);
            _root->_col = BLACK;
            return true;
        }

        KerOfT kot;
        Node* cur = _root, *parent = nullptr;
        while(cur)
        {
            //此处data可能为pair之间比较，pair本身的比较不符合预期
            //需要借助仿函数来确定data的key，需要从map和set层实例化可传过来!!!!!!!!
            if(kot(data) < kot(cur->_data))
            {
                parent = cur;
                cur = cur->_left;
            }
            else if(kot(data) > kot(cur->_data))
            {
                parent = cur;
                cur = cur->_right;
            }
            else
                return false;
        }

        cur = new Node(data);
        if(kot(data) < kot(parent->_data))
        {
            parent->_left = cur;
        }
        else
        {
            parent->_right = cur;
        }
        cur->_parent = parent;

        while(parent && parent->_col == RED)
        {
            //找叔叔判断
            Node* grandfather = parent->_parent;
            if(grandfather->_left == parent)
            {
                //叔叔在右
                Node* uncle = grandfather->_right;
                //判断两种情况
                if(uncle && uncle->_col == RED) //情况1
                {
                    parent->_col = uncle->_col = BLACK;
                    grandfather->_col = RED;
                    //继续往上更新
                    cur = grandfather;
                    parent = cur->_parent;
                    //原本还要判断parent是否为nullptr，这已经提出去了，为根结束就好了
                }
                else //情况2
                {
                    //先旋转再变色，先变色双旋部分会乱颜色
                    if(cur == parent->_left)
                    {
                        //单旋
                        RotateR(grandfather);
                        parent->_col = BLACK;
                        grandfather->_col = RED;
                    }
                    else
                    {
                        //双旋
                        RotateL(parent);
                        RotateR(grandfather);
                        cur->_col = BLACK;
                        grandfather->_col = RED;
                    }
                    //只要经过情况2就结束了，因为子树的根节点为黑色，不破坏其他路径
                    break;
                }

            }
            else
            {
                //叔叔在左
                Node* uncle = grandfather->_left;
                //判断两种情况
                if(uncle && uncle->_col == RED) //情况1
                {
                    parent->_col = uncle->_col = BLACK;
                    grandfather->_col = RED;

                    cur = grandfather;
                    parent = cur->_parent;
                }
                else
                {
                    //先旋转再变色，先变色双旋部分会乱颜色
                    if(cur == parent->_right)
                    {
                        //单旋
                        RotateL(grandfather);
                        parent->_col = BLACK;
                        grandfather->_col = RED;
                    }
                    else
                    {
                        //双旋
                        RotateR(parent);
                        RotateL(grandfather);
                        cur->_col = BLACK;
                        grandfather->_col = RED;
                    }

                    break;
                }
            }
        }
        _root->_col = BLACK; //当parent更新为nullptr时结束循环，不管为黑还是红最后都更新为黑，就不用单独在循环体内写变黑逻辑

        return true;
    }

    // bool Erase()
    // {
        
    // }
    
    bool Find(const T& data)
    {
        Node* cur = _root;
        while(cur)
        {
            if(kot(data) > kot(cur->_data))
                cur = cur->_right;
            else if(kot(data) < kot(cur->_data))
                cur = cur->_left;
            else
                return cur;
        }

        return nullptr;
    }

    void RotateR(Node* parent)
    {
        Node* subL = parent->_left;
        Node* subLR = subL->_right;


        parent->_left = subLR;
        if(subLR)//一定要判断一下subL的右子树是否存在，否则subLR->_parent解引用会报错
			subLR->_parent = parent;

        subL->_right = parent;
        Node* p = parent->_parent; //一定先记住而不是需要判断的时候才用，因为下面一条语句已经将原始数据更改
        parent->_parent = subL;

        if(parent == _root)
        {
            _root = subL;
            _root->_parent = nullptr; //注意此步
        }
        else
        {
            //parent有父母，判断parent是左孩子还是右孩子
            if(parent == p->_left)
            {
                p->_left = subL;
            }
            else
            {
                p->_right = subL;
            }

            subL->_parent = p; //注意要更改_parent指针
        }
    }
    void RotateL(Node* parent)
    {
        Node* subR = parent->_right;
        Node* subRL = subR->_left;


        parent->_right = subRL;
        if(subRL)//一定要判断一下subL的右子树是否存在，否则subLR->_parent解引用会报错
			subRL->_parent = parent;

        subR->_left = parent;
        Node* p = parent->_parent; 
        parent->_parent = subR;

        if(parent == _root)
        {
            _root = subR;
            _root->_parent = nullptr; //注意此步
        }
        else
        {
            //parent有父母，判断parent是左孩子还是右孩子
            if(parent == p->_left)
            {
                p->_left = subR;
            }
            else
            {
                p->_right = subR;
            }

            subR->_parent = p; //注意要更改_parent指针
        }
    }

    void inOrder()
    {
        _inOrder(_root);
        cout << endl;
    }

    bool isBalance() //!!!!!!
    {
        int refNum = 0;
        Node* cur = _root;
        while(cur)
        {
            if(cur->_col == BLACK)
            {
                ++refNum;
            }
            cur = cur->_left;
        }

        return _isBalance(_root, 0, refNum);
    }
private:
    void _inOrder(Node* root)
    {
        if(root == nullptr)
            return;
        
        _inOrder(root->_left);
        cout << root->_kv.first << ":" << root->_kv.second << endl;
        _inOrder(root->_right);
    }

    bool _isBalance(Node* root, int blackNum, const int refNum)
    {
        if(root == nullptr)
        {
            if(blackNum != refNum)
            {
                cout << "每条路径黑色结点不相等" << endl;
                return false;
            }
            return true;
        }
        //检查规则就能检查出是否为红黑树
        if(root == _root && root->_col == RED)
        {
            return false;
        }
        else if(root->_col == RED && root->_parent->_col == RED)
        {
            cout << root->_kv.first << ":存在连续的红色结点" << endl;
            return false;
        }

        if(root->_col == BLACK)
        {
            ++blackNum;
        }

        return _isBalance(root->_left, blackNum, refNum) && _isBalance(root->_right, blackNum, refNum);
    }
    
private:
    Node* _root = nullptr;
    size_t _size = 0; //记录结点数
};


