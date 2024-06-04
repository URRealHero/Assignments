#include "SQList.h"
status DestroyList(SQList &L){
  if(L.elem == NULL)
        return INFEASIBLE;
    L.length = 0;
    L.size = 0;
    free(L.elem);
    L.elem = NULL;
    return OK;
}
