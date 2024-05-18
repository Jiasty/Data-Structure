#include"RBTree.h"

namespace Jiastyset
{
    template<class K>
    class set
    {
        struct SetKeyOfT
        {
            const K& operator()(const K& key)
            {
                return key;
            }
        };

    public:
    void _Insert(const K& key)
    {
        _t.Insert(key);
    }
    private:
        RBTree<K, K, SetKeyOfT> _t;
    };
}