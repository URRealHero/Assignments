#include "SQList.h"

ElemType MaxSubArray(SQList L){
  if(L.elem==NULL || L.length == 0) return INFEASIBLE;
  ElemType ThisSum = 0,MaxSum = 0;
  int index;
  for(index = 0 ; index < L.length ; index++){
	ThisSum+=L.elem[index];
	if(ThisSum < 0) ThisSum = 0;
	if(ThisSum > MaxSum) MaxSum = ThisSum;
  }
  return MaxSum;
}
