#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int KeyType; 
typedef struct {
	  KeyType  key;
	  char others[20];
} TElemType; //二叉树结点类型定义


typedef struct BiTNode{  //二叉链表结点的定义
	  TElemType  data;
	  KeyType Sum;
	  struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;
//status SaveBiTree(BiTree T, char FileName[]);
//status LoadBiTree(BiTree &T, char FileName[]);

typedef struct BITREES{
  struct{
	char Name[30];
	BiTree T;
  }elem[20];
  int length;
}BiForest;

status CreateBiTree(BiTree &T,TElemType definition[]);
void CreateBiNode(BiTree &Root,TElemType definition[]);
status ClearBiTree(BiTree &T);
status isEmpty(BiTree T);
int BiTreeDepth(BiTree T);
int BiTreeHeight(BiTree T,BiTree p);
BiTNode* LocateNode(BiTree T,KeyType e);
status PreOrderCheck(BiTree T1,BiTree T2);
status Assign(BiTree &T,KeyType e,TElemType value);
BiTNode* GetSibling(BiTree T,KeyType e);
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c);
BiTree Search(BiTree T,BiTree eNode);
BiTree FindMax(BiTree T);
status DeleteNode(BiTree &T,KeyType e);
status PreOrderTraverse(BiTree T,void (*visit)(BiTree));
status InOrderTraverse(BiTree T,void (*visit)(BiTree));
status PostOrderTraverse(BiTree T,void (*visit)(BiTree));
void visit(BiTree T);
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree));
void SaveBiTreeRec(BiTree T, FILE *f);
status SaveBiTree(BiTree T, char FileName[]);
BiTree LoadBiTreeRec(FILE *f);
status LoadBiTree(BiTree &T,  char FileName[]);
BiTree LowestCommonAncestor(BiTree T,BiTree e1, BiTree e2);
int MaxPathLength(BiTree T);
int MaxPathSum(BiTree T);
KeyType dfs(BiTree T, KeyType & Solution);
status InverseBiTree(BiTree &T);
BiTree TestAncestor(BiTree T1, int h1, BiTree T2, int h2,BiTree T,int ht);
//多个二叉树管理
status Add_BiTree_to_Forest(BiForest &F,char FileName[],TElemType definition[]);
status Remove_BiTree_from_Forest(BiForest &F, char FileName[]);
status Locate_And_Modify_a_Tree_in_Forest(BiForest F,char FileName[],BiTree &T);
status Auto_Add_a_BiTree(BiForest &F,BiTree T);
status Traverse_Forest_Names(BiForest F);
int Index_of_Tree(BiForest F,char FileName[]);