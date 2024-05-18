#include"RBTree.h"

namespace Jiastymap
{
    template<class K, class V>
    class map
    {
        struct MapKeyOfT
        {
            const K& operator()(const pair<K, V>& kv)
            {
                return kv.first;
            }
        };
    public:
        void _Insert(const pair<K, V>& kv)
        {
            _t.Insert(kv);
        }

    private:
        RBTree<K, pair<K, V>, MapKeyOfT> _t;
    };
}