#include<iostream>

using namespace std;

enum
{
    RED,
    BLACK
};

template<class K, class V>
struct RBTNode
{
    struct RBTNode* _left;
    struct RBTNode* _right;
    struct RBTNode* _parent;
    pair<K, V> _kv;

    int _bf = 0;
    

    RBTNode(const pair<K, V>& kv)
        :_left(nullptr)
        ,_right(nullptr)
        ,_parent(nullptr)
        ,_kv(kv)
        ,_bf(0)
    {}
};

template<class K, class V>
class RBTree
{
    typedef RBTNode<K, V> Node;
public:
    bool Insert();
    bool Erase();
    bool Find();
    void inOrder

    bool isBalance();
    
private:
    Node* _root = nullptr;
};