#include "SQList.h"


status ListDelete(SQList &L,int i,ElemType &e){
  if(L.elem == NULL) return INFEASIBLE;
    if(i < 1 || i>L.length) return ERROR;
    e = L.elem[i-1];
    for (int j = i-1 ; j<L.length; j++){
        L.elem[j] = L.elem[j+1];
    }
    L.length--;
    return OK;
}
