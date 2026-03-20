#pragma once
#include <vector>
#include <map>
#include <string> // <<重载打印string可能在string头文件里
#include <queue>
#include <functional>
#include <algorithm>
#include "UnionFindSet.h"

namespace link_matrix
{
    // vertex 顶点 weight 权值(边) 
    // MAX_W 未相联时的权值(大部份情况W为整型)
    // Direction非类型参数, 为false为无向图
    // old: template <class V, class W, W MAX_W = INT_MAX, bool Direction = false> 
    template <class V, class W, bool Direction = false>
    class Graph
    {
        using Self = Graph<V, W, Direction>; // 以便后面相关算法传参数
    private:
        void _DFS(size_t srci, vector<bool> &visited)
        {
            cout << srci << ":" << _vertexes[srci] << endl;
            visited[srci] = true;

            // 找srci相邻顶点且未访问
            size_t row_size = _matrix.size();
            for (size_t i = 0; i < row_size; i++)
                if (_matrix[srci][i] != defaultWeight && visited[i] == false)
                    _DFS(i, visited);
        }
        void _AddEdge(size_t srci, size_t dsti, const W &w)
        {
            _matrix[srci][dsti] = w;
            // 无向图的情况
            if (Direction == false) _matrix[dsti][srci] = w;
        }
    public:
        Graph() = default;
        // 默认最大值由外部控制
        Graph(const V *arr, size_t n, const W &MAX_W)
            : defaultWeight(MAX_W)
        {
            _vertexes.reserve(n);
            for (size_t i = 0; i < n; i++)
            {
                _vertexes.push_back(arr[i]); // 依次将顶点放入顶点集合
                _indexMap[arr[i]] = i;       // 放入集合的同时记录顶点的编号
            }

            // 创建并初始化邻接矩阵
            _matrix.resize(n); // 此处为何使用reserve就会出错? reserve不会初始化不能访问对象，所以下面_matrix[j]就会出错
            for (size_t j = 0; j < n; j++)
                _matrix[j].resize(n, MAX_W);
        }

        // 返回某顶点的编号
        size_t GetVertexIndex(const V &vert)
        {
            // 使用find而不直接用operate[] 的原因应该在于传的顶点可能是错误的，抛异常让用户看到
            auto it = _indexMap.find(vert);
            if (it != _indexMap.end()) return it->second;
            throw invalid_argument("顶点不存在");
        }

        // 添加边，实际上就是在 matrix 中更新两vertex之间的权值
        void AddEdge(const V &src, const V &dst, const W &w)
        {
            size_t srci = GetVertexIndex(src);
            size_t dsti = GetVertexIndex(dst);
            _AddEdge(srci, dsti, w);
        }

        void Print()
        {
            // 顶点
            for (size_t i = 0; i < _vertexes.size(); i++)
                cout << "[" << i << "]->" << _vertexes[i] << endl;
            cout << endl;

            // 矩阵
            cout << "  ";
            int n = _vertexes.size();
            while (n)
            {
                cout << _vertexes.size() - n << " ";
                --n;
            }
            cout << endl;
            for (int i = 0; i < _matrix.size(); i++)
            {
                cout << i << " ";
                for (int j = 0; j < _matrix[i].size(); j++)
                    if (defaultWeight == _matrix[i][j]) cout << "* ";
                    else cout << _matrix[i][j] << " ";
                cout << endl;
            }
            cout << endl;
        }

        void BFS(const V &src) // 针对连通图
        {
            size_t srci = GetVertexIndex(src);
            queue<size_t> q;
            vector<bool> visited(_vertexes.size(), false); // 标记是否进入过队列
            q.push(srci);
            visited[srci] = true;
            int levelSize = 1; // 最开始q里面就一个元素

            // 判断queue是否为空然后出队列再带入新vertexes
            size_t num = _matrix.size(); // 记录行列数
            while (!q.empty())
            {
                for (size_t i = 0; i < levelSize; i++)
                {
                    size_t front = q.front();
                    q.pop();
                    cout << _vertexes[front] << "[" << front << "] ";
                    // 出了front就要带入front的邻接顶点
                    for (size_t j = 0; j < num; j++)
                        if (_matrix[front][j] != defaultWeight && visited[j] == false)
                        {
                            q.push(j);
                            visited[j] = true;
                        }
                }
                cout << endl;
                levelSize = q.size(); // 一层出完了，重新获取下一层的元素个数
            }
        }

        void DFS(const V &src) // 针对连通图
        {
            size_t srci = GetVertexIndex(src);
            vector<bool> visited(_vertexes.size(), false);
            _DFS(srci, visited);
        }

        //----------------------------相关算法-------------------------------//

        ///////////////////////////构造最小生成树的方法(针对连通图)///////////////////////////
        // 1.Kruskal算法(全局视角选边)
        struct Edge // 为kruskal算法创建来描述边
        {
            size_t _srci;
            size_t _dsti;
            W _w;

            Edge(size_t srci, size_t dsti, const W &w)
                : _srci(srci), _dsti(dsti), _w(w)
            {}
            bool operator>(const Edge &other) const { return _w > other._w; }
        };

        // 返回值对象记录了最小生成树的权值
        // 参数为一个无向图(输出型参数)
        W Kruskal(Self &miniTree) 
        {
            // 记录行列数
            size_t n = _matrix.size(); 
            // 初始化miniTree
            miniTree._vertexes = _vertexes;
            miniTree._indexMap = _indexMap;
            miniTree._matrix.assign(n, vector<W>(n, defaultWeight));
            
            // 创建一个小顶堆(对应greater)，将所有的边存进去,以便后面选择权值最小的边
            priority_queue<Edge, vector<Edge>, greater<Edge>> min_que;
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    if (i < j && _matrix[i][j] != defaultWeight) // i < j的目的是避免无向图入同一条边
                        min_que.push(Edge(i, j, _matrix[i][j]));

            // 开始选边（n-1条，不构成环）为了防止构成环，需要UnionFindSet的帮助
            UnionFindSet<int> ufs(n);
            int edge_size = 0;
            W total = W(); // 记录最小生成树的权值返回
            while (!min_que.empty())
            {
                Edge min = min_que.top();
                min_que.pop();

                if (!ufs.InSet(min._srci, min._dsti))
                {
                    cout << _vertexes[min._srci] << "->" << _vertexes[min._dsti] << ": " << min._w << endl;
                    miniTree._AddEdge(min._srci, min._dsti, min._w);

                    ufs.Union(min._srci, min._dsti);
                    total += min._w;
                    ++edge_size;
                    if (edge_size == n - 1) return total;
                }
                else
                {
                    cout << "there is circle!" << endl;
                    cout << _vertexes[min._srci] << "->" << _vertexes[min._dsti] << ":" << min._w << endl;
                }
            }
            return W();
        }

        // 2.Prim算法(从某点开始选边)
        W Prim(Self &miniTree, const V &src)
        {
            // 获取起点下标
            size_t start = GetVertexIndex(src);
            // 记录行列数
            size_t n = _matrix.size(); 
            // 初始化miniTree
            miniTree._vertexes = _vertexes;
            miniTree._indexMap = _indexMap;
            miniTree._matrix.assign(n, vector<W>(n, defaultWeight));
            
            // 先将start的邻接边入队
            vector<bool> visited(n, false);
            visited[start] = true;
            priority_queue<Edge, vector<Edge>, greater<Edge>> min_que;
            for(int j = 0; j < n; j++)
                if(_matrix[start][j] != defaultWeight)
                    min_que.push(Edge(start, j, _matrix[start][j]));
            
            int edge_size = 0;
            W total = W();

            while(!min_que.empty())
            {
                Edge min = min_que.top();
                min_que.pop();
                if(visited[min._dsti]) continue;

                visited[min._dsti] = true;
                for(int k = 0; k < n; k++)
                    if(!visited[k] && _matrix[min._dsti][k] != defaultWeight)
                        min_que.push(Edge(min._dsti, k, _matrix[min._dsti][k]));

                cout << _vertexes[min._srci] << "->" << _vertexes[min._dsti] << ": " << min._w << endl;
                miniTree._AddEdge(min._srci, min._dsti, min._w);

                total += min._w;
                ++edge_size;
                if (edge_size == n - 1) return total;
            }
            return W();
        }

        ///////////////////////////最短路径问题(一般针对有向图)///////////////////////////
        // 1.单源最短路径Dijkstra算法(不带负权时)
        void Dijkstra(const V& src, vector<W>& dist, vector<int>& parentPath)
        {
            size_t start = GetVertexIndex(src);
            size_t n = _vertexes.size();
            dist.assign(n, defaultWeight);
            parentPath.assign(n, -1);
            dist[start] = 0;
            parentPath[start] = start;

            // 已确定最短路径的顶点集合
            vector<bool> visited(n, false);
            priority_queue<pair<W, size_t>, vector<pair<W, size_t>>, greater<pair<W, size_t>>> minVertexQueue;
            minVertexQueue.push({0, start});

            while(!minVertexQueue.empty())
            {
                // 每次确定距离最短的顶点加入 visited 集合
                pair<W, size_t> curv = minVertexQueue.top();
                minVertexQueue.pop();
                size_t u = curv.second;
                // 非连通图防御
                if(visited[u]) continue;
                visited[u] = true;

                // 从已确定最短路径的顶点u进行松弛操作
                for(int v = 0; v < n; v++)
                    if(false == visited[v] && 
                        _matrix[u][v] != defaultWeight && 
                        _matrix[u][v] + dist[u] < dist[v])
                    {
                        dist[v] = _matrix[u][v] + dist[u];
                        parentPath[v] = u;

                        // 刷新历史最低记录
                        // 重复入队也没事if(visited[u]) continue;会直接跳过
                        minVertexQueue.push({dist[v], v}); 
                    }
            }
        }

        // 2.单源最短路径Bellman-Ford算法(带负权时) -- 堆优化后为SPFA算法
        void Bellman-Ford(const V& src, vector<W>& dist, vector<int>& parentPath)
        {
            
        }

        // 3.多源最短路径Floyd-Warshall算法
        void Floyd-Warshall()
        {

        }

        void PrinrtShotPath(const V& src, const vector<W>& dist, const vector<int>& parentPath)
        {
            size_t n = _vertexes.size();
            size_t start = GetVertexIndex(src);
            for(int i = 0; i < n; i++)
            {
                if(start == i) continue;

                vector<int> path;
                int cur = i;
                while(cur != start)
                {
                    path.push_back(cur);
                    cur = parentPath[cur];
                }
                path.push_back(start);
                reverse(path.begin(), path.end());  // TODO: reverse

                for(const auto& e : path)
                {
                    cout << _vertexes[e] << "->";
                }
                cout << dist[i] << endl;
            }
        }

    private:
        vector<V> _vertexes;         // 顶点集合
        map<V, size_t> _indexMap;    // 顶点映射下标关系，方便构建matrix
        vector<vector<W>> _matrix;   // 邻接矩阵
        W defaultWeight;             // 默认最大权值
    };
}



// 邻接表存储
namespace link_table
{
    // 描述边
    template <class W>
    struct Edge
    {
        // size_t srci; //看需求
        size_t _dsti;
        W _w;
        Edge<W> *_next;

        Edge(size_t dsti, const W &w)
            : _dsti(dsti), _w(w), _next(nullptr)
        {}
    };

    template <class V, class W, bool Direction = false> // Direction为false为无向图
    class Graph
    {
        typedef Edge<W> Edge;

    public:
        Graph(const V *arr, size_t n)
        {
            _vertexes.reserve(n);
            for (size_t i = 0; i < n; i++)
            {
                _vertexes.push_back(arr[i]); // 依次将顶点放入顶点集合
                _indexMap[arr[i]] = i;       // 放入集合的同时记录顶点的编号
            }

            // 创建邻接表并初始化
            _table.resize(n, nullptr);
        }

        // 返回某顶点的编号
        size_t GetVertexIndex(const V &vert)
        {
            auto it = _indexMap.find(vert); // 返回iterator

            if (it != _indexMap.end())
            {
                return it->second;
            }
            else
            {
                throw invalid_argument("顶点不存在");
                return -1;
            }
        }

        // 添加边
        void AddEdge(const V &src, const V &dst, const W &w)
        {
            size_t srci = GetVertexIndex(src);
            size_t dsti = GetVertexIndex(dst);

            Edge *eg = new Edge(dsti, w);
            eg->_next = _table[srci];
            _table[srci] = eg;

            if (Direction == false)
            {
                Edge *eg = new Edge(srci, w);
                eg->_next = _table[dsti];
                _table[dsti] = eg;
            }
        }

        void Print()
        {
            for (int i = 0; i < _vertexes.size(); i++)
            {
                cout << "[" << i << "]->" << _vertexes[i] << endl;
            }
            cout << endl;

            for (int i = 0; i < _table.size(); i++)
            {
                cout << _vertexes[i] << "[" << i << "]->";
                Edge *cur = _table[i];
                while (cur)
                {
                    cout << _vertexes[cur->_dsti] << cur->_w << "->";
                    cur = cur->_next;
                }
                cout << "nullptr" << endl;
            }
        }

    private:
        vector<V> _vertexes;   // 顶点集合
        map<V, size_t> _indexMap; // 顶点映射下标关系，方便构建matrix
        vector<Edge *> _table; // 邻接表
    };
}