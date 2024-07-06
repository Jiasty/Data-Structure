#pragma once
#include<vector>
#include<map>
#include<string> // <<重载打印string可能在string头文件里
#include<queue>



namespace link_matrix
{
    //   vertex 顶点 weight 权值(边) MAX_W 未相联时的权值(大部份情况W为整型)
    template<class V, class W, W MAX_W = INT_MAX, bool Direction = false> //Direction为false为无向图
    class Graph
    {
        typedef Graph<V, W, MAX_W, Direction> Self;  //以便后面相关算法传参数
    public:
        Graph()
        {}

        Graph(const V* arr, size_t n)
        {
            _vertexes.reserve(n);
            for(size_t i = 0; i < n; i++)
            {
                _vertexes.push_back(arr[i]);  //依次将顶点放入顶点集合
                _indexMap[arr[i]] = i;  //放入集合的同时记录顶点的编号
            }

            //创建并初始化邻接矩阵
            _matrix.resize(n);  //此处为何使用reserve就会出错？？？reserve不会初始化不能访问对象，所以下面_matrix[j]就会出错
            for(size_t j = 0; j < n; j++)
            {
                _matrix[j].resize(n, MAX_W);
            }
        }

        //返回某顶点的编号
        size_t GetVertexIndex(const V& vert)
        {
            auto it = _indexMap.find(vert);  //返回iterator

            if(it != _indexMap.end())
            {
                return it->second;
            }
            else
            {
                //assert(false);
                throw invalid_argument("顶点不存在");
				return -1;
            }
            //使用find而不直接用operate[] 的原因应该在于传的顶点可能是错误的，抛异常让用户看到
        }

        //添加边，实际上就是在 matrix 中更新两vertex之间的权值
        void AddEdge(const V& src, const V& dst, const W& w)
        {
            size_t srci = GetVertexIndex(src);
            size_t dsti = GetVertexIndex(dst);

            _matrix[srci][dsti] = w;

            //无向图的情况
            if(Direction == false)
            {
                _matrix[dsti][srci] = w;
            }
        }

        void Print()
        {
            //顶点
            for(size_t i = 0; i < _vertexes.size(); i++)
            {
                cout << "[" << i << "]->" << _vertexes[i] << endl;
            }
            cout << endl;

            //矩阵
            cout << "  ";
            int n = _vertexes.size();
            while(n)
            {
                cout << 4 - n << " ";
                --n;
            }
            cout << endl;
            for(int i = 0; i < _matrix.size(); i++)
            {
                cout << i << " ";
                for(int j = 0; j < _matrix[i].size(); j++)
                {
                    if(MAX_W == _matrix[i][j])
                        cout << "* ";
                    else
                        cout << _matrix[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }

        void BFS(const V& src) //针对连通图
        {
            size_t srci = GetVertexIndex(src);
            queue<int> q;
            vector<bool> visited(_vertexes.size(), false); //标记是否进入过队列
            q.push(srci);
            visited[srci] = true;
            int levelSize = 1; //最开始q里面就一个元素

            //判断queue是否为空然后出队列再带入新vertexes
            int num = _matrix.size(); //记录行列数
            while(!q.empty())
            {
                for(int i = 0; i < levelSize; i++)
                {
                    int front = q.front();
                    q.pop();
                    cout << _vertexes[front] << "[" << front << "] ";
                    //出了front就要带入front的邻接顶点
                    for(int i = 0; i < num; i++)
                    {
                        if(_matrix[front][i] != MAX_W && visited[i] == false)
                        {
                            q.push(i);
                            visited[i] = true;
                        }
                    }
                }
                cout << endl;

                levelSize = q.size(); //一层出完了，重新获取下一层的元素个数
            }
        }

        void _DFS(size_t srci, vector<bool>& visited)
        {
            cout << srci << ":" << _vertexes[srci] << endl;
            visited[srci] = true;

            //找srci相邻顶点且未访问
            for(int i = 0; i < _matrix.size(); i++)
            {
                if(_matrix[srci][i] != MAX_W && visited[i] == false)
                {
                    _DFS(i, visited);
                }
            }
        }
        void DFS(const V& src) //针对连通图
        {
            size_t srci = GetVertexIndex(src);
            vector<bool> visited(_vertexes.size(), false);
            _DFS(srci, visited);
        }

        //-----------------------------------------------------------//
        //相关算法
        //如果定义了一个有向图，会不会使用到该方法？？？
        //构造最小生成树的方法（接近最优解），针对连通图
        //1、Kruskal算法
        W Kruskal(const Self& miniTree)  //求一整个图的最小生成树，参数为一个无向图
        {

        }

        //2、Prim算法

    private:
        vector<V> _vertexes;  //顶点集合
        map<V, int> _indexMap;  //顶点映射下标关系，方便构建matrix
        vector<vector<W>> _matrix;  //邻接矩阵
    };
}


namespace link_table
{
    //描述边
    template<class W>
    struct Edge
    {
        //size_t srci; //看需求
        size_t _dsti;
        W _w;
        Edge<W>* _next;

        Edge(size_t dsti, const W& w)
            :_dsti(dsti)
            ,_w(w)
            ,_next(nullptr)
        {}
    };
    
    template<class V, class W, bool Direction = false> //Direction为false为无向图
    class Graph
    {
        typedef Edge<W> Edge;
    public:
        Graph(const V* arr, size_t n)
        {
            _vertexes.reserve(n);
            for(size_t i = 0; i < n; i++)
            {
                _vertexes.push_back(arr[i]);  //依次将顶点放入顶点集合
                _indexMap[arr[i]] = i;  //放入集合的同时记录顶点的编号
            }

            //创建邻接表并初始化
            _table.resize(n, nullptr);
        }

        //返回某顶点的编号
        size_t GetVertexIndex(const V& vert)
        {
            auto it = _indexMap.find(vert);  //返回iterator

            if(it != _indexMap.end())
            {
                return it->second;
            }
            else
            {
                //assert(false);
                throw invalid_argument("顶点不存在");
				return -1;
            }
        }

        //添加边
        void AddEdge(const V& src, const V& dst, const W& w)
        {
            size_t srci = GetVertexIndex(src);
            size_t dsti = GetVertexIndex(dst);

            Edge* eg = new Edge(dsti, w);
            eg->_next = _table[srci];
            _table[srci] = eg;

            if(Direction == false)
            {
                Edge* eg = new Edge(srci, w);
                eg->_next = _table[dsti];
                _table[dsti] = eg;
            }
        }

        void Print()
        {
            for(int i = 0; i < _vertexes.size(); i++)
            {
                cout << "[" << i << "]->" << _vertexes[i] << endl;
            }
            cout << endl;

            for(int i = 0; i < _table.size(); i++)
            {
                cout << _vertexes[i] << "[" << i << "]->";
                Edge* cur = _table[i];
                while(cur)
                {
                    cout << _vertexes[cur->_dsti] << cur->_w << "->";
                    cur = cur->_next;
                }
                cout << "nullptr" << endl;
            }
        }
    private:
        vector<V> _vertexes;  //顶点集合
        map<V, int> _indexMap;  //顶点映射下标关系，方便构建matrix
        vector<Edge*> _table;  //邻接表
    };
}