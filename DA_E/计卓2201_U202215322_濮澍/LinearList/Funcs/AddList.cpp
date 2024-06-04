#include "SQList.h"


status AddList(LISTS &Lists,char ListName[]){
  if(Lists.length>=10) return ERROR;
    strcpy(Lists.elem[Lists.length].name,ListName);
    Lists.elem[Lists.length].L.elem = NULL;
    InitList(Lists.elem[Lists.length].L);
    Lists.length++;
    return OK;
}
