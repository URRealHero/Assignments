#include "SQList.h"

status PriorElem(SQList L,ElemType e,ElemType &pre){
   if(L.elem == NULL) return INFEASIBLE;
    int i = 0;
    while(i<L.length){
        if(L.elem[i]==e) break;
        i++;
    }
    if (i==0 || i == L.length) return ERROR;
    pre = L.elem[i-1];
    return OK;
}
