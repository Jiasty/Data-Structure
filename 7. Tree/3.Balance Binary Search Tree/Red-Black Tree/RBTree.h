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
    struct RBTreeNode* _left;
    struct RBTreeNode* _right;
    struct RBTreeNode* _parent;
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
            _root = new Node(kv, BLACK);
            return true;
        }

        //新插入结点红色好还是黑色好？
        //红色好，插入黑色会破坏原本的RBTree性质4，可能导致每条路径的黑色结点数不同(规则4一定不要破坏)
        //而插入红色就只可能破坏性质3，性质3破坏可以往上调整，而性质4可不好调整，全局都会被破坏
    }
    bool Erase()
    {

    }
    bool Find()
    {

    }
    void inOrder()
    {

    }

    bool isBalance()
    {

    }
    
private:
    Node* _root = nullptr;
    size_t _size = 0; //记录结点数
};