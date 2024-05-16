#include<iostream>

using namespace std;

//规则:
//1.结点颜色不是黑就是红
//2.根节点为黑色
//3.红色结点的两个孩子结点都是黑色，红色结点不能连续出现，黑色结点可以
//4.对于每个结点，从该结点到其所有后代叶子结点的简单路径上，黑色结点的数目相同
//5.每个叶子结点都是黑色的(指NIL，非传统的叶子结点，这里是空结点)

//为何满足上述性质，红黑树就能保证:其最长路径的结点数不超过最短路径结点的两倍？

enum Color
{
    RED,
    BLACK
};

template<class K, class V>
struct RBTreeNode
{
    RBTreeNode<K, V>* _left;
    RBTreeNode<K, V>* _right;
    RBTreeNode<K, V>* _parent;
    pair<K, V> _kv;

    Color _col;

    RBTreeNode(const pair<K, V>& kv)
        :_left(nullptr)
        ,_right(nullptr)
        ,_parent(nullptr)
        ,_kv(kv)
        ,_col(RED)
    {}
};

template<class K, class V>
class RBTree
{
    typedef RBTreeNode<K, V> Node;
public:
    bool Insert(const pair<K, V>& kv)
    {
        if(_root == nullptr)
        {
            _root = new Node(kv);
            _root->_col = BLACK;
            return true;
        }

        Node* cur = _root, *parent = nullptr;
        while(cur)
        {
            if(kv.first < cur->_kv.first)
            {
                //此处单独用parent来记录而不用cur->_parent记录的原因cur会走到空
                parent = cur;
                cur = cur->_left;
            }
            else if(kv.first > cur->_kv.first)
            {
                parent = cur;
                cur = cur->_right;
            }
            else
                return false;
        }

        //新插入结点红色好还是黑色好？
        //红色好，插入黑色会破坏原本的RBTree性质4，可能导致每条路径的黑色结点数不同(规则4一定不要破坏)
        //而插入红色就只可能破坏性质3，性质3破坏可以往上调整，而性质4可不好调整，全局都会被破坏
        cur = new Node(kv); //cur走完上面的while循环就已经为空，可以使用来申请新的结点来链接
        if(kv.first < parent->_kv.first)
        {
            parent->_left = cur;
        }
        else
        {
            parent->_right = cur;
        }
        cur->_parent = parent;

        //往上调整颜色:cur父亲为黑色直接结束，为红色才需要调整
        //红色调整主要看uncle的颜色来决定需不需要旋转。需要调整前提:cur为RED，p肯定为RED,g肯定为黑
        //（插入引起颜色调整也有很多情况，当子树黑色结点数为0、1、2...等情况（1 2就是中间的情况），画图）
        //1.cur为红，p为红，g为黑，u为红 :p和u变黑，g变红（g为根就重新变为黑），如果g的p也为红就得继续往上调整
        //2.cur为红，p为红，g为黑，u不存在/u为黑 :先正常变色，然后旋转（单双旋）
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
    
    bool Find(const pair<K, V>& kv)
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