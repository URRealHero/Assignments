#include "SQList.h"

status TraverseLISTS(LISTS Lists){
  if(!Lists.length) return INFEASIBLE;
    int i;
    for(i=0;i<Lists.length;i++)
    {
        printf("%s\n",Lists.elem[i].name);
    }
    return OK;
}
