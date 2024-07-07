#include<iostream>
#include <string.h>
using namespace std;

#include"UnionFindSet.h"
#include"Graph.h"


void test_UnionFindSet()
{
    UnionFindSet<int> ufs(5);

    ufs.Union(2, 4);
    cout << ufs.Findroot(4) << endl;
    cout << ufs.SetSize() << endl;
    cout << ufs.InSet(1, 4) << endl;
}

void TestGraph1()
{
	link_matrix::Graph<char, int, INT_MAX, true> g("0123", 4); //为何一定要显示给INT_MAX，不是有缺省值吗？？？
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
	link_table::Graph<string, int, true> g1(a, 4); //为何没有删除MAX_W时true无效，缺省值为何未起作用？？？
	g1.AddEdge("张三", "李四", 100);
	g1.AddEdge("张三", "王五", 200);
	g1.AddEdge("王五", "赵六", 30);
	g1.Print();
}

void TestBFSAndDFS()
{
	string a[] = { "张三", "李四", "王五", "赵六" };
	link_matrix::Graph<string, int> g1(a, 4); //为何没有删除MAX_W时true无效，缺省值为何未起作用？？？
	g1.AddEdge("张三", "李四", 100);
	g1.AddEdge("张三", "王五", 200);
	g1.AddEdge("王五", "赵六", 30);
	//g1.Print();
	g1.BFS("王五");
	cout << endl;
	g1.DFS("王五");

}

void TestGraphMinTree()
{
	const char* str = "abcdefghi";
	link_matrix::Graph<char, int> g(str, strlen(str));
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
	//link_matrix::Graph<char, int> pminTree;
	//cout << "Prim:" << g.Prim(pminTree, 'a') << endl;
	//pminTree.Print();
}

int main()
{
    //test_UnionFindSet();
    //TestGraph1();
	//TestGraph2();
	//TestBFSAndDFS();
	TestGraphMinTree();

    return 0;
}