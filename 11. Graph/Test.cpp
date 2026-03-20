#include <iostream>
#include <string.h>
#include "UnionFindSet.h"
#include "Graph.h"

using namespace std;

void test_UnionFindSet()
{
    UnionFindSet<int> ufs(5);

	cout << "集合数" << ufs.SetSize() << endl;
	cout << "合并2 4" << endl;
    ufs.Union(2, 4);
    cout << "4所在集合的根: " << ufs.FindRoot(4) << endl;
    cout << "集合数" << ufs.SetSize() << endl;
    cout << "1和4是否在一个集合: " << (ufs.InSet(1, 4) ? "true" : "false") << endl;
}

void TestGraph1()
{
	link_matrix::Graph<char, int, true> g("0123", 4, INT_MAX);
	g.AddEdge('0', '1', 1);
	g.AddEdge('0', '3', 4);
	g.AddEdge('1', '3', 2);
	g.AddEdge('1', '2', 9);
	g.AddEdge('2', '3', 8);
	g.AddEdge('2', '1', 5);
	g.AddEdge('2', '0', 3);
	g.AddEdge('3', '2', 6);

	g.Print();
}

void TestGraph2()
{
	string a[] = { "张三", "李四", "王五", "赵六" };
	link_table::Graph<string, int, true> g1(a, 4);
	g1.AddEdge("张三", "李四", 100);
	g1.AddEdge("张三", "王五", 200);
	g1.AddEdge("王五", "赵六", 30);
	g1.Print();
}

void TestBFSAndDFS()
{
	string a[] = { "张三", "李四", "王五", "赵六" };
	link_matrix::Graph<string, int> g1(a, 4, INT_MAX);
	g1.AddEdge("张三", "李四", 100);
	g1.AddEdge("张三", "王五", 200);
	g1.AddEdge("王五", "赵六", 30);
	// g1.Print();
	g1.BFS("王五");
	cout << endl;
	g1.DFS("王五");

}

void TestGraphMinTree()
{
	const char* str = "abcdefghi";
	link_matrix::Graph<char, int> g(str, strlen(str), INT_MAX);
	g.AddEdge('a', 'b', 4);
	g.AddEdge('a', 'h', 8);
	g.AddEdge('a', 'h', 9);
	g.AddEdge('b', 'c', 8);
	g.AddEdge('b', 'h', 11);
	g.AddEdge('c', 'i', 2);
	g.AddEdge('c', 'f', 4);
	g.AddEdge('c', 'd', 7);
	g.AddEdge('d', 'f', 14);
	g.AddEdge('d', 'e', 9);
	g.AddEdge('e', 'f', 10);
	g.AddEdge('f', 'g', 2);
	g.AddEdge('g', 'h', 1);
	g.AddEdge('g', 'i', 6);
	g.AddEdge('h', 'i', 7);
	link_matrix::Graph<char, int> kminTree;
	cout << "Kruskal:" << g.Kruskal(kminTree) << endl;
	kminTree.Print();
	// link_matrix::Graph<char, int> pminTree;
	// cout << "Prim:" << g.Prim(pminTree, 'a') << endl;
	// pminTree.Print();
}


void TestGraphDijkstra()
{
	const char* str = "syztx";
	link_matrix::Graph<char, int, true> g(str, strlen(str), INT_MAX);
	g.AddEdge('s', 't', 10);
	g.AddEdge('s', 'y', 5);
	g.AddEdge('y', 't', 3);
	g.AddEdge('y', 'x', 9);
	g.AddEdge('y', 'z', 2);
	g.AddEdge('z', 's', 7);
	g.AddEdge('z', 'x', 6);
	g.AddEdge('t', 'y', 2);
	g.AddEdge('t', 'x', 1);
	g.AddEdge('x', 'z', 4);
	vector<int> dist;
	vector<int> parentPath;
	g.Dijkstra('s', dist, parentPath);
	g.PrinrtShotPath('s', dist, parentPath);
	// 图中带有负权路径时，贪心策略则失效了。
	// 测试结果可以看到s->t->y之间的最短路径没更新出来
	/*const char* str = "sytx";
	Graph<char, int, INT_MAX, true> g(str, strlen(str));
	g.AddEdge('s', 't', 10);
	g.AddEdge('s', 'y', 5);
	g.AddEdge('t', 'y', -7);
	g.AddEdge('y', 'x', 3);
	vector<int> dist;
	vector<int> parentPath;
	g.Dijkstra('s', dist, parentPath);
	g.PrinrtShotPath('s', dist, parentPath);*/
}


int main()
{
    // test_UnionFindSet();
    // TestGraph1();
	// TestGraph2();
	// TestBFSAndDFS();
	// TestGraphMinTree();
	TestGraphDijkstra();

    return 0;
}