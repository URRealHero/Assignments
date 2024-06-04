#include "SQList.h"


status  SaveList(SQList L,char FileName[]){
  if(L.elem == NULL) return INFEASIBLE;
    FILE *fp;
    fp = fopen(FileName,"w");
    for(int i = 0 ; i<L.length ; i++){
        fprintf(fp,"%d",L.elem[i]);
        fprintf(fp,(i==L.length-1)?"\n":" ");
    }
    fclose(fp);
    return OK;
}
