#include "SQList.h"


int LocateList(LISTS Lists,char ListName[],SQList &L){
	int i;
    for(i = 0 ; i<Lists.length ; i++){
        if(strcmp(ListName,Lists.elem[i].name) == 0){
		  L=Lists.elem[i].L;   
		  break;
	  }
    }
    if(i!=Lists.length){
        return i+1;
    }
    return 0;
}
