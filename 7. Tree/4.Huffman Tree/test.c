#include "huffman.c"

//对字符串进行译码
void test()
{
    char st[254], *s; //假设原文本文件不超过253个字符,st[0]是第一个有效字符
    char str[27]; //26个英文字母
    int cn[27];
    HuffmanTree HT;
    HuffmanCode HC;
    printf("输入需要编译的字符串（假设均为大写字母）：\n");
    gets(st);
    num=jsq(st, cn, str); //统计字符的种类及各类字符出现的频率
    ChuffmanTree(HT, HC, cn, str); //建立赫夫曼树
    HuffmanEncoding(HT, HC); //生成赫夫曼编码
    coding(HC, st); //建立电文赫夫曼编码文件
    s=decode(HC); //读编码文件译码
    printf("译码后的字符串：%s\n",s);
    getchar();//等待用户输入任意一个字符，用于暂停屏幕，观察运行结果
}

int main()
{
    test();

    return 0;
}