#include "SQList.h"

status InitLISTS(LISTS &L){
  int i;
  L.length = 0;
  for(int i = 0; i<10 ; i++)
	L.elem[i].name[i] = '\0';
  return OK;
}
