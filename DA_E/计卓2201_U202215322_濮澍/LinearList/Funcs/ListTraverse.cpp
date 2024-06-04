#include "SQList.h"


status ListTraverse(SQList L){
  if(L.elem == NULL) return INFEASIBLE;
    for ( int i = 0 ; i < L.length ; i++){
        printf("%d",L.elem[i]);
        printf((i == L.length - 1)?"" : " ");
    }
    return OK;
}
