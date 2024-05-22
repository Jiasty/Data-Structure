#include "huffman.h"

//------------------------------------------------
//建立赫夫曼树的三个函数
int jsq(char *s, int cnt[], char str[]) 
{ //为计算权值做准备
    char *p;
    int i, j, k;
    int temp[27] = {0};
    
    //对数组初始化
    // for(i=1; i<=26; i++)
    //     temp[i]=0;//各字符计数器清零temp[1]为'A'的个数temp[26]为'Z'的个数

    for(p=s; *p!='\0'; p++) 
    { //统计各种字符的个数
        if(*p>='A' && *p<='Z') 
        {
            k=*p-64; // 'A'(65) <-->1
            temp[k]++;
        }
    }

    j=0;
    for(i=1; i<=26; i++) //统计有多少字符
        if(temp[i]!=0) 
        {
            j++;
            str[j]=i+64; //送对应的字母到数组中
            cnt[j]=temp[i]; //存入对应字母的权值
        }

    return j; //返回值给全局变量num赋值
}


void select(HuffmanTree T, int k, int *s1, int *s2) 
{
    int i, j;
    int min=32767;
    for(i=1; i<=k; i++)
        if(T[i].weight<min && T[i].parent==0)
        {
            j=i; 
            min=T[i].weight;
        }
    *s1=j;
    min=32767;
    for(i=1; i<=k; i++)
        if(T[i].weight<min && T[i].parent==0 && i!=*s1) 
        {
            j=i; min=T[i].weight;
        }
    *s2=j;
}

void ChuffmanTree(HuffmanTree HT, HuffmanCode HC, int cnt[], char str[]) 
{
    int i, s1, s2;
    for(i=1; i<=2*num-1; i++) 
    { //初始化HT
        HT[i].lchild=0; HT[i].rchild=0;
        HT[i].parent=0; HT[i].weight=0;
    }
    for(i=1; i<=num; i++) //输入num个叶结点的权值
        HT[i].weight=cnt[i];
    //HT[1..num]为叶子节点
    //HT[num+1..2*num-1]为构造出的非叶子节点
    for(i=num+1; i<=2*num-1; i++) 
    {
        //在HT[1..i-1]中选择parent为且权值最小的两个根结点，
        //其序号分别为s1和s2
        select(HT, i-1, &s1, &s2);
        HT[s1].parent=i; HT[s2].parent=i;
        HT[i].lchild=s1; HT[i].rchild=s2; //s1和s2可互换
        HT[i].weight=HT[s1].weight + HT[s2].weight;
    }
    for(i=1; i<=num; i++) //输入num个叶结点对应的字符
        HC[i].ch=str[i];
    //输出字符与对应的出现次数
    i=1;
    while(i<=num) 
    {
        printf("字符%c, 次数为:%d\n", HC[i].ch, cnt[i]);
        i++;
    }
    printf("--------------------\n");
}


//对str所代表的的字符串进行编码，并写入文件
void coding(HuffmanCode HC, char *str) 
{
    int i,j;
    FILE *fp;
    fp=fopen("codefile.txt","w");
    while(*str) 
    {
        for(i=1; i<=num; i++) //顺次查找
            if(HC[i].ch==*str) 
            {
                for(j=0; j<HC[i].len; j++)
                    fputc(HC[i].bits[j], fp); //注意'\0'没有输出
                break;
            }
    str++;
    }
    fclose(fp);
}
//------------------------------------------------
//(电文译码)
//代码文件codefile.txt的译码
char * decode(HuffmanCode HC) 
{
    FILE *fp;
    char str[254]; //存结果，假设原文本文件（编码前的信息）不超过253个字符
    char *p;
    char cd[n+1]; //cd[0]要用,cd[n]即可（从0号下标开始存，最长n-1位，cd[0..n-2]即可，cd[n-1]放串尾符）
    int i, j;
    int k=0; //str[k]放当前的字符
    int cjs; //标志变量cjs串结束，一个字符的编码是否读结束
    fp=fopen("codefile.txt","r");
    while(!feof(fp)) 
    {
        cjs=0; //一个字符的编码还没有 读结束
        //Huffman编码优点：不是共享前缀码
        //逐步试探法：设'A'编码1110
        //试1 无匹配 cd[0..1]="1"
        //试11 无匹配 cd[0..2]="11"
        //试111 无匹配 cd[0..3]="111"
        //试1110 匹配了 cd[0..4]="1110"
        //每个字符编码最长为num-1位占用cd[0..num-2]
        for(i=0; i<num-1 && cjs==0 && !feof(fp); i++) 
        {
            cd[i]=' '; cd[i+1]='\0'; //初始化cd串,串长暂为1
            cd[i]=fgetc(fp);
            for(j=1; j<=num; j++) //顺次查找法
                if(strcmp(HC[j].bits, cd)==0) 
                {
                    str[k]=HC[j].ch;
                    k++;
                    cjs=1; //一个字符的编码已经读结束
                    break;
                }
        }
    }
    str[k]='\0';
    p=str;
    fclose(fp);
    return p;
}
//------------------------------------------------
//(生成编码)
//根据赫夫曼树HT求赫夫曼编码表HC中余下的信息
//输入参数HuffmanTree HT
//输出参数HuffmanCode HC
void HuffmanEncoding(HuffmanTree HT, HuffmanCode HC) 
{
    int c, p, i; //c和p分别指示T中孩子和双亲的位置
    //cd数组临时存放编码串。n个叶子，每个最长n-1位编码，最后还要串结束符
    char cd[n+1]; //cd[0]不用。 cd[num+1]就足够了但num是变量
    int start; //指示编码在cd中起始位置
    cd[n]='\0'; //最后一位放上串结束符
    for(i=1; i<=num; i++) 
    { //对每个字符（对应叶子节点）进行编码
        start=n; //初始位置从后向前回退，start指向'\0'的位置
        c=i; //从叶子结点HT[i]开始上溯当前节点为子女节点c，准备找其双亲结点p
        while((p=HT[c].parent)>0) 
        { //直至上溯到HT[c]是树根为止
            //若HT[c]是HT[p]的左孩子，则生成0；否则生成1
            cd[--start]=(HT[p].lchild==c)? '0': '1';
            c=p;
        }//end of while
        strcpy(HC[i].bits, &cd[start]);
        HC[i].len=n-start; //n指向'\0'的位置, start是首位
    }//end of for
    //输出字符与对应的编码
    i=1;
    while(i<=num) 
    {
        printf("字符%c, 编码为:%s\n", HC[i].ch, HC[i].bits);
        i++;
    }
    printf("--------------------\n");
}