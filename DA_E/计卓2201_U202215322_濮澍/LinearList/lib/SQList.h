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
#define MAXLEN 30

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

typedef struct SQList{
  int length;
  int size;
  ElemType * elem = NULL;
}SQList;//顺序结构定义

//用线性表管理顺序表
typedef struct LISTS{
  struct { char name[30];
               SQList L;    
     } elem[10];
     int length;
}LISTS;

status InitList(SQList &L);
status DestroyList(SQList &L);
status ClearList(SQList &L);
status isEmpty(SQList L); 
status ListLength(SQList L);
status GetElem(SQList L,int i,ElemType &e);
int LocateElem(SQList L,ElemType e);
status PriorElem(SQList L,ElemType e,ElemType &pre);
status NextElem(SQList L,ElemType e,ElemType &next);
status ListInsert(SQList &L,int i,ElemType e);
status ListDelete(SQList &L,int i,ElemType &e);
status ListTraverse(SQList L);
status  SaveList(SQList L,char FileName[]);
status LoadList(SQList &L,char FileName[]);
status InitLISTS(LISTS &Lists);
status AddList(LISTS &Lists,char ListName[]);
status RemoveList(LISTS &Lists,char ListName[]);
int LocateList(LISTS Lists,char ListName[],SQList &L);
ElemType MaxSubArray(SQList L);
int SubArrayNum(SQList L, ElemType k);
status SortList(SQList &L);
void swap(ElemType & x,ElemType & y);
status TraverseLISTS(LISTS Lists);
status InitLISTS(LISTS &L);
