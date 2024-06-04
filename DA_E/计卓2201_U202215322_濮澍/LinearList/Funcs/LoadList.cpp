#include "SQList.h"


status LoadList(SQList &L,char FileName[]){
	if(L.elem) return INFEASIBLE;
    L.elem = (ElemType *) malloc(LISTINCREMENT * sizeof(ElemType));
    L.length = 0;
    L.size=LISTINCREMENT;
    FILE *fp;
    ElemType e;
    int i = 0;
    if((fp = fopen(FileName,"r")) == NULL) return INFEASIBLE;
	
    while(!feof(fp)){
        if(L.length >= L.size) {
            L.elem = (ElemType *)realloc(L.elem,(L.size+LISTINCREMENT) * sizeof(ElemType));
            L.size+=LISTINCREMENT;
        }
        fscanf(fp,"%d",&e);
        L.elem[L.length++] = e;
    }
	if(L.length == 0) return ERROR;
    L.length--;
    return OK;

}
