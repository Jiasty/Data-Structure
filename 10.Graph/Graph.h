#pragma once
#include<vector>
#include<map>

namespace link_matrix
{
    //    vertex 顶点 weight 权值 MAX_W 未相联的标志
    template<class V, class W, W MAX_W = INT_MAX, bool Direction = false> //Direction为false为无向图
    class Graph
    {
        typedef Graph<V, W, MAX_W, Direction> Self;  //以便后面相关算法传参数
    public:

        Graph(const V* arr, size_t n)
        {
            _vertexes.reserve(n);
            for(int i = 0; i < n; i++)
            {
                _vertexes.push_back(arr[i]);  //依次将顶点放入顶点集合
                _indexMap[arr[i]] = i;  //放入集合的同时记录顶点的编号
            }

            //创建并初始化邻接矩阵
            _matrix.reserve(n);
            for(int j = 0; j < n; j++)
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
                return it->seconde;
            }
            else
            {
                throw invalid_argument("顶点不存在");

				return -1;
            }
            //使用find而不直接用operate[] 的原因应该在于抛异常让用户看到
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

        }

        void BFS()
        {

        }

        void DFS()
        {

        }

        //-----------------------------------------------------------//
        //相关算法

        //构造最小生成树的方法
        //1、Kruskal算法
        W Kruskal(const Self& miniTree)  //求一整个图的最小生成树，参数为一个图
        {

        }

        //2、Prim算法

    private:
        vector<V> _vertexes;  //顶点集合
        map<V, int> _indexMap;  //顶点下标关系
        vector<vector<W>> _matrix;  //邻接矩阵
    };
}

namespace link_table
{

}