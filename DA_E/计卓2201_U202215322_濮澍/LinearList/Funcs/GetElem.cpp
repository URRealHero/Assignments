#include "SQList.h"

status GetElem(SQList L,int i,ElemType &e){
 if(L.elem == NULL) return INFEASIBLE;
    if(i<1||i > L.length)  return ERROR;
    e = L.elem[i-1];
    return OK;
}
