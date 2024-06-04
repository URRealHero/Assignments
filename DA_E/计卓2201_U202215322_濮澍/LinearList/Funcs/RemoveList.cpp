#include "SQList.h"


status RemoveList(LISTS &Lists,char ListName[]){
// Lists中删除一个名称为ListName的线性表

    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int flag = 0;
    int i;
    for(i = 0 ; i<Lists.length ; i++){
        if(strcmp(ListName,Lists.elem[i].name) == 0){
            DestroyList(Lists.elem[i].L);
            strcpy(Lists.elem[i].name,"\0");
            flag++;
            break;
        }
    }
    if(flag == 1){
        for(int j = i ; j<=Lists.length-1 ; j++){
            Lists.elem[j] = Lists.elem[j+1];
        }
		Lists.length--;
        return OK;
    }
    return ERROR;
    /********** End **********/
}






