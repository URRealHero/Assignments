#include "SQList.h"

status ClearList(SQList &L){
  if(L.elem == NULL)
        return INFEASIBLE;
    L.length = 0;
    free(L.elem);
    return OK;
}
