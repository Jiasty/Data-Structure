#pragma once
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

    int _bf; //balance factor平衡因子(此处为右子树高度 - 左子树高度)
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
        if(kv.first > parent->_kv.first)
        {
            parent->_right = cur;
        }
        else
        {
            parent->_left = cur;
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
                cur = parent;
                parent = parent->_parents;
            }
            else if(parent->_bf == 2 || parent->_bf == -2)
            {
                //该子树已经不平衡了，需要旋转处理！！！！！！
                if(parent->_bf == 2 && cur->_bf == 1) //左单旋
                {
                    RotateLeft(parent);
                }
                else if(parent->_bf == -2 && cur->_bf == -1) //右单旋
                {
                    RotateRight(parent);
                }
                else if(parent->_bf == 2 && cur->_bf == -1) //以下两种都是双旋的情况，不是偏向一边一直高下去
                {
                    RotateRL(parent);
                }
                else if(parent->_bf == -2 && cur->_bf == 1)
                {
                    RotateLR(parent);
                }
                
                //旋转后就意味着平衡因子已经更新好了，不用继续往上更新了，直接break
                break;
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

    /* bool Erase(const pair<K, V>& kv)//!!!未完成
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

    } */

    //右单旋:左子树太高了
    //左高就让左子树作为新的_root，将自己降为新root的右子树，然后托管新root以前的右子树成为自己的左子树
    void RotateRight(Node* parent)
    {
        Node* subL = parent->_left;
        Node* subLR = subL->_right;


        parent->_left = subLR;
        if(subLR)//一定要判断一下subL的右子树是否存在，否则subLR->_parent解引用会报错
			subLR->_parents = parent;

        subL->_right = parent;
        Node* p = parent->_parents;
        parent->_parents = subL;

        if(parent == _root)
        {
            _root = subL;
            _root->_parents = nullptr; //注意此步
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

            subL->_parents = p; //注意要更改_parents指针
        }

        //底层指针指向转动完成，更改bf
        subL->_bf = 0;
        parent->_bf = 0;
    }
    void RotateLeft(Node* parent)
    {
        Node* subR = parent->_right;
        Node* subRL = subR->_left;


        parent->_left = subRL;
        if(subRL)//一定要判断一下subL的右子树是否存在，否则subLR->_parent解引用会报错
			subRL->_parents = parent;

        subR->_left = parent;
        Node* p = parent->_parents;
        parent->_parents = subR;

        if(parent == _root)
        {
            _root = subR;
            _root->_parents = nullptr; //注意此步
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

            subR->_parents = p; //注意要更改_parents指针
        }

        //底层指针指向转动完成，更改bf
        subR->_bf = 0;
        parent->_bf = 0;
    }

    //双旋对平衡因子要做额外处理，插入位置不同旋转完因子不同
    //左右双旋（先左再右）
    void RotateLR(Node* parent)
    {
        Node* subL = parent->_left;
        Node* subLR = subL->_right;

        //一定在调用单旋前记录原本suLr的bf，不同的插入subL和parent最后的bf不同需单独处理
        int bf = subLR->_bf;

        RotateLeft(subL);
        RotateRight(parent);

        subLR->_bf = 0;
        //单独处理平衡因子
        if(bf == -1) //插入在subLR的左边
        {
            subL->_bf = 0;
            parent->_bf = 1;
        }
        else if(bf == 1)
        {
            subL->_bf = -1;
            parent->_bf = 0;
        }
        else if(bf == 0) //此时插入的就是subLR
        {
            subL->_bf = 0;
            parent->_bf = 0;
        }
        else
        {
            //理论而言不会出现这种情况，为了避免bug，直接将该情况断死报错
            assert(false);
        }
    }
    //右左双旋
    void RotateRL(Node* parent)
    {
        Node* subR = parent->_right;
        Node* subRL = subR->_left;

        //一定在调用单旋前记录原本suRl的bf，不同的插入subR和parent最后的bf不同需单独处理
        int bf = subRL->_bf;

        RotateRight(subR);
        RotateLeft(parent);

        subRL->_bf = 0;
        //单独处理平衡因子
        if (bf == 1)
		{
			subR->_bf = 0;
			parent->_bf = -1;
		}
		else if (bf == -1) //插入在subLR的左边
		{
			parent->_bf = 0;
			subR->_bf = 1;
		}
		else if(bf == 0)//此时插入的就是subLR
		{
			parent->_bf = 0;
			subR->_bf = 0;
		}
        else
        {
            //理论而言不会出现这种情况，为了避免bug，直接将该情况断死报错
            assert(false);
        }
    }


    //注意封装（避免外部需要_root却无法调用）（递归的时候也封装）！！！！！！！！！！！！！！！
    //判断是否平衡
    bool isBalance()
    {
        return _isBalance(_root);
    }
    int GetHeight()
    {
        return _GetHeight(_root);
    }
    void InOrder()  
    {
        _InOrder(_root);
        cout << endl;
    }
private:
    bool _isBalance(Node* root)
    {
        //每棵树都判断一下

        if(root == nullptr)
            return true;

        int leftHeigh = _GetHeight(root->_left);
        int rightHeigh = _GetHeight(root->_right);

        //此处一定不能判断为正确就返回true，因为不保证下面的树为AVL树
        if(abs(rightHeigh - leftHeigh) >= 2)
        {
            cout << root->_kv.first << endl; //第几次插入就不是
            return false;
        }

        //顺便检查平衡因子
        if(rightHeigh - leftHeigh != root->_bf)
        {
            cout << root->_kv.first << endl; //第几个bf错误
            return false;
        }

        //递归判断左右子树,同时为true才true
        return _isBalance(root->_left) && _isBalance(root->_right);
    }
    int _GetHeight(Node* root)
    {
        if(root == nullptr)
            return 0;
        
        int leftH = _GetHeight(root->_left);
        int rightH = _GetHeight(root->_right);

        return max(leftH, rightH) + 1;
    }

    void _InOrder(Node* root)  //这里为什么要传root? 外部调用时要传root，但是_root为私有，所以可以再封装
    {
        if(root == nullptr)
            return;
        
        _InOrder(root->_left);
        cout << root->_kv.first << ":" << root->_kv.second << endl;
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