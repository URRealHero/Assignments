#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
using namespace std;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef int ElemType;
typedef struct LNode{  //单链表（链式结构）结点的定义
      ElemType data;
      struct LNode *next;
    }LNode,*LinkList;
typedef struct arrList{
	struct{
	  char Name[30];
	  LinkList L;
  }elem[20];
	int length;
}ArrList;
status InitList(LinkList &L,int ElemNum = 0);
status DestroyList(LinkList &L);
status ClearList(LinkList &L);
status ListEmpty(LinkList L);
int ListLength(LinkList L);
status GetElem(LinkList L,int i, ElemType &e);
status LocateElem(LinkList L,ElemType e);
status PriorElem(LinkList L,ElemType e,ElemType &pre);
status NextElem(LinkList L,ElemType e,ElemType &next);
status ListInsert(LinkList &L,int i,ElemType e);
status ListDelete(LinkList &L ,int i,ElemType &e);
status ListTraverse(LinkList L) ;
status SaveList(LinkList L,const char FileName[]);
status LoadList(LinkList &L,const char FileName[]);
status ReverseList(LinkList &L);
status RemoveNthFromEnd(LinkList &L,int n,ElemType &e);
status SortList(LinkList &L);
void Swap(LinkList &L1,LinkList &L2);
status AddList(ArrList &Lists,char ListName[]);
status RemoveList(ArrList &Lists,char ListName[],LinkList &L);
int LocateList(ArrList Lists,char ListName[],LinkList &L);
status Save2List(ArrList &Lists, char ListName[], LinkList L);
