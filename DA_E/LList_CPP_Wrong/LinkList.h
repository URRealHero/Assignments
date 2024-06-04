#include <iostream>
#include <cstdlib>
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
class LElement{
private:
  ElemType data;
  LElement * next;
public:
  LElement();
};
class LList{
private:
  LList L;
  ElemType elem;
  ElemType Pre , Next;
public: 
  LList();
  LList(int ElemNum);
  ~LList();
  status DestroyList();
  status ClearList();
  status ListEmpty();
  int ListLength();
  status LocateElem(ElemType e);
  status PriorElem(ElemType e);
  status NextElem(ElemType e);
  status ListInsert(int i,ElemType e);
  status ListDelete(int i,ElemType &e);
  status ListTraverse() const;
  status SaveList(const std::string &FileName);
  status LoadList(const std::string &FileName);
  status ReverseList();
  status RemoveNthFromEnd(int n,ElemType &e);
  status SortList();
  //多链式表操作
  //
};
