#pragma once
#include<vector>
#include<map>

//weight 权值
template<class V, class W, bool Direction>
class Graph
{
private:
    vector<V> _vertexes;  //顶点集合
    map<V, int> _indexMap  //顶点下标关系
    vector<vector<W>> _edges;  //边集合
};