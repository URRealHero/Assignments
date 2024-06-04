#include "SQList.h"
#include <unordered_map>

int SubArrayNum(SQList L,ElemType k){
  int index = 0;
  ElemType sum = 0;
  if(L.elem == 0) return INFEASIBLE;
  //So elem[a...b] == k <==> hash_sum[b] - hash_sum[a-1] == k
  //hash_sum[b] - k == hash_sum[a-1]
  std::unordered_map <ElemType,ElemType> mp;
  mp[0] = 1;
  for(int i = 0 ; i < L.length ; i++){
	sum += L.elem[i];
	if (mp.find(sum - k) != mp.end()) {
                index += mp[sum - k];
    }
	//Mapping the sum to mp 
	//If sum-k once appeared index can add it on
	mp[sum]++;
  }

  return index;
}
//Using Hash => maping the sum to the existence of sum
