#include<iostream>
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

int main()
{
    //test_UnionFindSet();
    //TestGraph1();
	//TestGraph2();
	TestBFSAndDFS();

    return 0;
}