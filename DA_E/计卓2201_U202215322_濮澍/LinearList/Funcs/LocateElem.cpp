#include "SQList.h"
int LocateElem(SQList L,ElemType e){
  if (L.elem == NULL) return INFEASIBLE;
    int i;
    for(i = 0; L.elem[i] != e && i<L.length ; i++);
    if(i == L.length) return ERROR;
    return i+1;
}

