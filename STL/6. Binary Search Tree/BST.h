#include<iostream>

using namespace std;

template<class k>
struct BSTNode
{
    BSTNode* _left;
    BSTNode* _right;
    k _val;

    BSTNode(k& val)
        :_left(nullptr)
        ,_right(nullptr)
        ,_val(val)
    {}
};

template<class k>
class BSTree
{
public:


private:
    BSTNode* _root;
};