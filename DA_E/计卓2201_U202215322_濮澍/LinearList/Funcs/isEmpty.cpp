#include "SQList.h"

status isEmpty(SQList L){
  if (L.elem == NULL) return INFEASIBLE;
    if(L.length == 0) return TRUE;
    return FALSE;
}
