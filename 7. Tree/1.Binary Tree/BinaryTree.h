#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

typedef int BTDataType;

typedef struct BinaryTreeNode
{
    BTDataType data;
    struct BinaryTreeNode* left;
    struct BinaryTreeNode* right;
}BTNode;

//普通二叉树的增删查改没意义

//创建二叉树结点
BTNode* BuyTreeNode(BTDataType x);
//构建树(测试用，直接手动构造)
BTNode* CreatTree();
// 通过前序遍历的数组"ABD##E#H##CF##G##"构建二叉树
BTNode* BinaryTreeCreate(BTDataType* a, int* pi);
// 二叉树销毁
void BinaryTreeDestory(BTNode** root);

// 二叉树前序遍历
void PreOrder(BTNode* root);
// 二叉树中序遍历
void InOrder(BTNode* root);
// 二叉树后序遍历
void PostOrder(BTNode* root);
// 层序遍历
void LevelOrder(BTNode* root);
// 二叉树前序遍历
void PreOrderNonRec(BTNode* root);
// 二叉树中序遍历
void InOrderNonRec(BTNode* root);
// 二叉树后序遍历
void PostOrderNonRec(BTNode* root);

// 二叉树节点个数
int BinaryTreeSize(BTNode* root);
// 二叉树叶子节点个数
int BinaryTreeLeafSize(BTNode* root);
// 二叉树第k层节点个数
int BinaryTreeLevelKSize(BTNode* root, int k);
//二叉树的高度
int BinaryTreeHeight(BTNode* root);
// 二叉树查找值为x的节点
BTNode* BinaryTreeFind(BTNode* root, BTDataType x);
// 判断二叉树是否是完全二叉树
bool BinaryTreeComplete(BTNode* root);

