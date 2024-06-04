#include "SQList.h"

status NextElem(SQList L,ElemType e,ElemType &next){
   if(L.elem == NULL) return INFEASIBLE;
    int i;
    for (i = 0 ; i<L.length ; i++){
        if(L.elem[i] == e) break;
    }
    if(i == L.length-1 || i == L.length) return ERROR;
    next = L.elem[i+1];
    return OK;
}
