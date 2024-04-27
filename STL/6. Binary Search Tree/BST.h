#include<iostream>
using namespace std;

//搜索二叉树较 二分算法比较相像
template<class K>
struct BSTNode
{
    BSTNode(const K& key = K())
        :_left(nullptr)
        ,_right(nullptr)
        ,_key(key)
    {}

    BSTNode* _left;
    BSTNode* _right;
    K _key;
};

template<class K>
class BSTree
{
    typedef BSTNode<K> Node;
public:
    //插入一个值时，树中可能已经存在，存在则不插入，为了标记未插入，就用bool类型返回值返回false
    bool Insert(const K& key)  //注意:插入一定是往下走的，直至找到nullptr
    {
        //考虑 _root 为空的情况
        if(_root == nullptr)
        {
            _root = new Node(key);
            return true;
        }

        Node* cur = _root;
        Node* parent = nullptr;  //cur每次往下走都记录父亲位置的结点，以方便链接结点
        while(cur)
        {
            if(key > cur->_key)
            {
                parent = cur;
                cur = cur->_right;
            }
            else if(key < cur->_key)
            {
                parent = cur;
                cur = cur->_left;
            }
            else
                return false;
        }

        cur = new Node(key);
        if(key < parent->_key)
        {
            parent->_left = cur;
        }
        else
        {
            parent->_right = cur;
        }

        return true;
    }

    bool Find(const K& key)
    {
        Node* cur = _root;
        while(cur)
        {
            if(key > cur->_key)
                cur = cur->_right;
            else if(key < cur->_key)
                cur = cur->_left;
            else
                return true;
        }

        return false;
    }

    bool Erase(const K& key)
    {
        //1、没有孩子:直接删
        //2、有1个孩子:parent托管
        //3、有2个孩子:替换法删除（就像二叉树的根节点删除）
        //用左子树的最大结点（图像最右边的结点）或右子树的最小结点（图像最左边的结点）与要删除结点交换后再删除该结点
        //左子树最大结点比左子树其他结点都大，但比右子树的结点都小，换到根之后符合二叉搜索树
        //右子树最小结点比右子树其他结点都小，但比左子树的结点都大，换到根之后符合二叉搜索树

        Node* parent = nullptr;
        Node* cur = _root;
        while(cur)
        {
            if(key < cur->_key)
            {
                parent = cur;
                cur = cur->_left;
            }
            else if(key > cur->_key)
            {
                parent = cur;
                cur = cur->_right;
            }
            else  // 找到了，进行删除，并且返回true
            {
                // 1和2两种情况可以合并
                if(cur->_left == nullptr)
                {
                    if(cur == _root)  //当数据都在一边时，注意
                    {
                        _root = cur->_right;
                    }
                    else if(cur == parent->_left) //我是父亲的左还是右，父亲的左还是右指向我的孩子
                    {
                        parent->_left = cur->_right;
                    }
                    else
                    {
                        parent->_right = cur->_right;
                    }

                    delete cur;
                }
                else if(cur->_right == nullptr)
                {
                    if(cur == _root)
                    {
                        _root = cur->_left;
                    }
                    else if(cur == parent->_left)
                    {
                        parent->_left = cur->_left;
                    }
                    else
                    {
                        parent->_right = cur->_left;
                    }

                    delete cur;
                }
                else //3.有两个子的情况，找左子树的max或右子树的min!!!!!!!!!!!!
                {
                    Node* leftmax = cur;
                    Node* maxParent = cur;  //一定不能给nullptr，当cur为_root时会报错
                    while(leftmax->_right)
                    {
                        maxParent = leftmax;
                        leftmax = leftmax->_right;
                    }
                    
                    swap(cur->_key, leftmax->_key);
                    //leftmax = cur后要更改一下链接关系
                    //maxParent->_right = leftmax->_left; 会在删除_root时将右子树删除掉
                    if(leftmax == maxParent->_left)
                        maxParent->_left = leftmax->_left;
                    else  //一般非_root结点就是这种情况
                        maxParent->_right = leftmax->_left;
                    delete leftmax;
                }

                return true;
            }
        }
        //没找到，返回false
        return false;

    }

    //注意！！！！！！！！！！！！！！！
    void InOrder()  
    {
        _InOrder(_root);
        cout << endl;
    }
private:
    void _InOrder(Node* root)  //这里为什么要传root? 外部调用时要传root，但是_root为私有，所以可以再封装
    {
        if(root == nullptr)
            return;
        
        _InOrder(root->_left);
        cout << root->_key << " ";
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