#include "LinkList.h"
#include <cstddef>
#include <string>
#include <cstring>

status InitList(LinkList &L,int ElemNum)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(L) return INFEASIBLE;
    L = new LNode;
	L->next = NULL;
	LinkList tail = L;
	int cnt = 1 ;
	
	while (cnt <= ElemNum){
	  LinkList P = new LNode;
	  cin >> P->data;
	  P->next = tail->next;
	  tail->next = P;
	  cnt++;
	  tail = tail->next;
  }
    return OK;

    /********** End **********/
}

status DestroyList(LinkList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L) return INFEASIBLE;
    LinkList P = L->next;
    while (P) {
        L->next = P->next;
        delete P;
        P = L->next;
    }
    delete L;
    L=NULL;
    return OK;

    /********** End **********/
}


status ClearList(LinkList &L)
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L) return INFEASIBLE;
    LinkList P = L->next;
    while(P){
        L->next = P->next;
        delete P;
        P = L->next;
    }
    L->next = NULL;
    return OK;

    /********** End **********/
}

status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L) return INFEASIBLE;
    if(L->next) return FALSE;
    return TRUE;

    /********** End **********/
}

int ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L) return INFEASIBLE;
    int count = 0 ;
    LinkList P = L->next;
    while(P){
        P = P->next;
        count ++;
    }
    return count;
    /********** End **********/
}


status GetElem(LinkList L,int i,ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L) return INFEASIBLE;
    if(i<1 || i > ListLength(L)) return ERROR;
    int cnt = 1;
    LinkList P = L->next;
    while(cnt < i){
        P = P->next;
        cnt++;
    }
    e = P->data;
    return OK;

    /********** End **********/
}

status LocateElem(LinkList L,ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L) return INFEASIBLE;
    LinkList P = L->next;
    int cnt = 1;
    while(P){
        if(e == P->data) return cnt;
        cnt++;
        P = P->next;
    }
    return ERROR;

    /********** End **********/
}

status PriorElem(LinkList L,ElemType e,ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L) return INFEASIBLE;
    LinkList Pre = L,P = L->next;
    while(P){
        if(P->data == e) break;
        Pre = P;
        P = P->next;
    }

    if(Pre == L || P == NULL)
        return ERROR;
    pre = Pre->data;
    return OK;
    /********** End **********/
}

status NextElem(LinkList L,ElemType e,ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L) return INFEASIBLE;
    LinkList Next,P = L->next;
    while(P){
        Next = P->next;
        if(P->data == e) break;
        P = Next;
    }

    if(Next == NULL || P == NULL)
        return ERROR;
    next = Next->data;
    return OK;

    /********** End **********/
}

status ListInsert(LinkList &L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L) return INFEASIBLE;
    if(i<1) return ERROR;
    int cnt = 1;
    LinkList P = L->next,Pre = L;
    while(P && cnt < i){
        Pre = P;
        P = P->next;
        cnt++;
    }
    if(P == NULL && i != cnt) return ERROR;
    LinkList Q = new LNode;
    Q->data = e;
    Q->next = P;
    Pre->next  = Q;
    return OK;
    /********** End **********/
}

status ListDelete(LinkList &L,int i,ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L) return INFEASIBLE;
    if(i<1) return ERROR;
    LinkList P = L->next;
    LinkList Pre = L;
    int cnt = 1;
    while(P && cnt < i){
        Pre = P;
        P = P->next;
        cnt++;
    }
    if(P == NULL){
        return ERROR;
    }
    Pre -> next = P->next;
    e = P->data;
    delete P; 
    return OK;
    /********** End **********/
}

status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(!L) return INFEASIBLE;
    LinkList P = L->next;
    while(P){
        printf("%d",P->data);
        putchar((P->next == NULL) ? '\n':' ');
        P=P->next;
    }
    return OK;
    /********** End **********/
}

status SaveList(LinkList L,const char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    if(!L) return INFEASIBLE;
    FILE *fp;
    fp = fopen(FileName,"w");
    LinkList P = L->next;
    while(P){
        fprintf(fp,"%d",P->data);
        fputc((P->next == NULL)?'\n':' ',fp);
        P=P->next;
    }
    fclose(fp);
    return OK;

    /********** End 1 **********/
}

status LoadList(LinkList &L,const char FileName[]){
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。 { 请在这里补充代码，完成本关任务 ********* Begin 2 *********/
    if(L) return INFEASIBLE;
    InitList(L);   
    LinkList P ,Pre = L;
	FILE *fp;	
    fp= fopen(FileName,"r");
    while(!feof(fp)){
        P = new LNode;
        fscanf(fp,"%d",&P->data);
        Pre->next = P;
        Pre = Pre->next;
    }
    Pre->next = NULL;

    return OK;

    /********** End 2 **********/
}

status ReverseList(LinkList &L){
  if(!L) return INFEASIBLE;
  LinkList Pre = NULL;
  LinkList P = L->next;
  LinkList Next;
  while (P)
  {
  	Next = P->next;
	P->next = Pre;
	Pre = P;
	P = Next;
  }
  L->next = Pre;
  return OK;
}
status RemoveNthFromEnd(LinkList &L,int n,ElemType &e){
  int cnt = 0;
  if(!L)return INFEASIBLE;
  if(ListLength(L) < n ) return FALSE;
  LinkList P = L->next,Pn = L->next,Pre = L;
  while(cnt < n){
	Pn = Pn->next;
	cnt++;
  }
  while(Pn){
	Pn = Pn->next;
	P = P->next;
	Pre = Pre->next;
  }
  Pre->next = P->next;
  e = P->data;
  delete P;
  return OK;
}
status SortList(LinkList &L){//升序
  if(!L) return INFEASIBLE;
  LinkList P=L->next,Q;
  for(;P->next;P = P->next){
	LinkList Min = P;
	for(Q = P->next;Q;Q = Q->next){
	  if(Min->data > Q->data)
		Min = Q;
	}
	Swap(P,Min);
  }
  return OK;
}

void Swap(LinkList &L1,LinkList &L2){
  ElemType e = L1->data;
  L1->data = L2->data;
  L2->data = e;
}


status AddList(ArrList &Lists,char ListName[]){
  if(Lists.length>=20) return ERROR;
    strcpy(Lists.elem[Lists.length].Name,ListName);
    Lists.elem[Lists.length].L = NULL;
	int ElemNum;
	cout << "Please Input the ElemNum you wan't to have in this List, 0 means a nil List!\n" << endl;
	cin >> ElemNum;
	cout << "Now input the num you want to insert." << endl;
    InitList(Lists.elem[Lists.length].L,ElemNum);
	ListTraverse(Lists.elem[Lists.length].L);
    Lists.length++;
    return OK;
}


status RemoveList(ArrList &Lists,char ListName[],LinkList &L){
// Lists中删除一个名称为ListName的线性表

    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int flag = 0;
    int i;
    for(i = 0 ; i<Lists.length ; i++){
        if(strcmp(ListName,Lists.elem[i].Name) == 0){
            DestroyList(Lists.elem[i].L);
            strcpy(Lists.elem[i].Name,"\0");
            flag++;
            break;
        }
    }
    if(flag == 1){
        for(int j = i ; j<=Lists.length-1 ; j++){
            Lists.elem[j] = Lists.elem[j+1];
        }
		Lists.length--;
		L = NULL;
        return OK;
    }
    return ERROR;
    /********** End **********/
}


int LocateList(ArrList Lists,char ListName[],LinkList &L){
	int i;
    for(i = 0 ; i<Lists.length ; i++){
        if(strcmp(ListName,Lists.elem[i].Name) == 0){
		  L=Lists.elem[i].L;   
		  break;
	  }
    }
    if(i!=Lists.length){
        return i+1;
    }
    return 0;
}

status Save2List(ArrList &Lists, char ListName[], LinkList L){
	
    strcpy(Lists.elem[Lists.length].Name,ListName);
    Lists.elem[Lists.length].L = L;
	Lists.length++;
	return OK;
}


