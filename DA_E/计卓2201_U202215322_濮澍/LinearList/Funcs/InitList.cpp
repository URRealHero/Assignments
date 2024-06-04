#include "SQList.h"
#include <cstdio>
#include <iostream>

status InitList(SQList &L){
	if (L.elem != NULL)
        return INFEASIBLE;
	int i = 0;
    L.length = 0;
    L.size = LIST_INIT_SIZE;
    L.elem = (ElemType *)malloc(L.size * sizeof(ElemType));
	ElemType e;
	std::cout << "请输入初始化的线性表，以0结束。";
	scanf("%d",&e);
	while(e && i<L.size){
	L.elem[i++] = e;
	L.length++;
	scanf("%d",&e);
  }
	return OK;
}

