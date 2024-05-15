#include <stdio.h>
#include <string.h>

//类型定义
//M=n0+n1+n2 M=0*n0+1*n1+2*n2+1=n1+2*n2+1 故n0=n2+1
//Huffman树中无度为的顶点，即n1=0
//M=(n0)+(n1)+(n2)=(n2+1)+0+(n2)=2*n2+1
//M=(n0)+(n1)+(n2)=(n0)+0+(n0-1)=2*n0-1
#define n 100 //叶子结点数
#define m 2*n-1 //赫夫曼树中结点总数

//每个字符的Huffman编码
typedef struct {
    char ch;
    char bits[n+1]; //存放编码位串，最长n-1位，注意还有串尾符，故char bits[n]即可
    int len; //编码长度
}CodeNode;

//Huffman码书 是所有字符的Huffman编码的汇总
typedef CodeNode HuffmanCode[n+1];//0号单元不用
//Huffman树的结点类型
typedef struct {
    int weight; //权值
    int lchild, rchild, parent; //左右孩子及双亲指针
}HTNode;
//Huffman树是Huffman结点的集合
typedef HTNode HuffmanTree[m+1]; //0号单元不用
int num;

//------------------------------------------------
//建立赫夫曼树的三个函数

//统计字符串s中各种字母的个数以及字符的种类
//输入参数为字符串s
//输出参数为int cnt[], char str[]
//返回值给全局变量num赋值
int jsq(char *s, int cnt[], char str[]);

//在HT[1..k]中选择parent为空（没有父节点）且权值最小的两个根结点
//其序号分别存入s1和s2
void select(HuffmanTree T, int k, int *s1, int *s2);

//构造赫夫曼树HT
//输入参数为int cnt[], char str[]
//输出参数为HuffmanTree HT, HuffmanCode HC
void ChuffmanTree(HuffmanTree HT, HuffmanCode HC, int cnt[], char str[]);

//对str所代表的的字符串进行编码，并写入文件
void coding(HuffmanCode HC, char *str);

//------------------------------------------------
//(电文译码)
//代码文件codefile.txt的译码
char * decode(HuffmanCode HC);

//------------------------------------------------
//(生成编码)
//根据赫夫曼树HT求赫夫曼编码表HC中余下的信息
//输入参数HuffmanTree HT
//输出参数HuffmanCode HC
void HuffmanEncoding(HuffmanTree HT, HuffmanCode HC);