#include "SQList.h"

status SortList(SQList &L){
  if(L.elem==NULL) return INFEASIBLE;
  ElemType min;
  for (int i = 0; i < L.length-1; i++) {
	min = i;
  	for(int j = i+1 ; j<L.length ; j++){
	  if(L.elem[min]>L.elem[j]) min = j;
	}
	if(i != min)
	  swap(L.elem[i],L.elem[min]);
  }
  return OK;
}
