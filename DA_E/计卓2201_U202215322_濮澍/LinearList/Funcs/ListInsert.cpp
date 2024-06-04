#include "SQList.h"


status ListInsert(SQList &L,int i,ElemType e){
  if(L.elem == NULL)return INFEASIBLE;
    if(i<=0|| i>L.length+1){ 
        return ERROR;}
    if(L.length>=L.size){
        L.elem = (ElemType *)realloc(L.elem,(LISTINCREMENT+L.size)*sizeof(ElemType));
        L.size+=LISTINCREMENT;
    }
    
    for (int j = L.length-1; j >= i-1 ; j--){
        L.elem[j+1] = L.elem[j];
    }
    L.elem[i-1] = e;
    L.length++;
    return OK;

}
