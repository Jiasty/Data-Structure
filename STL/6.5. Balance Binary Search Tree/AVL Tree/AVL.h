#include<iostream>
#include<assert.h>

using namespace std;

//一棵AVL树或者是空树，或者是具有以下性质的二叉搜索树：
//1、它的左右子树都是AVL树
//2、左右子树高度之差(简称平衡因子)的绝对值不超过1(-1/0/1)(在结点数为2，4等情况时做不到完全平衡)
//平衡因子 = 右子树高度 - 左子树高度 (或左子树高度 - 右子树高度)


//结点插入
//1、按照搜索树规则插入
//2、更新插入结点的祖先结点的平衡因子
//  (++  -- 是根据平衡因子的计算来看的，看是右减左还是左减右)
//  a.插入父亲结点的左边，父亲结点平衡因子--
//  b.插入父亲结点的右边，父亲结点平衡因子++
//  c.父亲结点平衡因子 == 0，父亲结点所在子树高度不变，不再继续往上更新。
//  d.父亲结点平衡因子 == 1/-1，父亲结点所在子树高度变了，继续往上更新
//  e.父亲结点平衡因子 == 2/-2，父亲所在子树已经不平衡了，需要！！旋转处理！！
//不可能出现其他值，插入之前树是AVL树，平衡因子要么是1/-1/0，++ -- 最多就是c d e三种情况


template<class K, class V>
struct AVLTNode
{
    AVLTNode(const pair<K, V>& kv)
        :_left(nullptr)
        ,_right(nullptr)
        ,_parents(nullptr)
        ,_kv(kv)
        ,_bf(0)
    {}

    AVLTNode* _left;
    AVLTNode* _right;
    AVLTNode* _parents;
    //更新平衡因子是往上走，需要记住parents结点
    pair<K, V> _kv;

    int _bf; //平衡因子(此处为右子树高度 - 左子树高度)
};

template<class K, class V>
class AVLTree
{
    typedef AVLTNode<K, V> Node;
public:
    bool Insert(const pair<K, V>& kv)
    {
        //考虑 _root 为空的情况
        if(_root == nullptr)
        {
            _root = new Node(kv);
            return true;
        }

        Node* cur = _root;
        Node* parent = nullptr;
        while(cur)
        {
            if(kv.first > cur->_kv.first)
            {
                parent = cur;
                cur = cur->_right;
            }
            else if(kv.first < cur->_kv.first)
            {
                parent = cur;
                cur = cur->_left;
            }
            else
                return false;
        }

        cur = new Node(kv);
        if(kv.first < parent->_kv.first)
        {
            parent->_left = cur;
        }
        else
        {
            parent->_right = cur;
        }
        
        //三叉链，链接parent
        cur->_parents = parent;
        //更新平衡因子，从下往上更新
        while(parent) //parent为nullptr意味着cur为_root结点，已经不需要更新了
        {
            //更新插入结点的parent
            if(cur == parent->_left)
            {
                parent->_bf--;
            }
            else
            {
                parent->_bf++;
            }

            //判断parent的bf再来看是否还要继续往上更新
            if(parent->_bf == 0)
            {
                //结束更新
                break;
            }
            else if(parent->_bf == 1 || parent->_bf == -1)
            {
                //继续往上更新
                cur = cur->_parents;
                parent = parent->_parents;
            }
            else if(parent->_bf == 2 || parent->_bf == -2)
            {
                //该子树已经不平衡了，需要旋转处理！！！！！！
                // ...
            }
            else
            {
                //理论而言不会出现这种情况，为了避免bug，直接将该情况断死报错
                assert(false);
            }
        }

        return true;
    }

    Node* Find(const pair<K, V>& kv)
    {
        Node* cur = _root;
        while(cur)
        {
            if(kv.first > cur->_kv.first)
                cur = cur->_right;
            else if(kv.first < cur->_kv.first)
                cur = cur->_left;
            else
                return cur;
        }

        return nullptr;
    }

    bool Erase(const pair<K, V>& kv)
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
            if(kv.first < cur->_kv.first)
            {
                parent = cur;
                cur = cur->_left;
            }
            else if(kv.first > cur->_kv.first)
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
                    
                    swap(cur->_kv.first, leftmax->_kv.first);
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

    //右单旋:左子树太高了
    //左高就让左子树作为新的_root，将自己降为新root的右子树，然后托管新root以前的右子树成为自己的左子树
    void RotateRight(Node* parent)
    {

    }
    void RotateLeft(Node* parent)
    {
        
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
        cout << root->_kv.first << ":" << root->_kv.second << " " << endl;
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