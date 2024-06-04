//booleans为文字计数器，labels为标签计数器
//子句用链表
#include <cmath>
#include <algorithm>


typedef struct clauses{
    int value;

    struct clauses *next;
}Clauses;

typedef struct clauseSet{
    Clauses *head;
    struct clauseSet *next;
}ClauseSet;

typedef struct KV{
    int index;
    int value;
}KV;


bool DPLL(ClauseSet *S,int n);
void Copy(ClauseSet *S, ClauseSet *TempS);
bool cmp(KV a, KV b);
void SORT(int *booleans, KV * labels, int n);
void deletion(ClauseSet *S);
bool SVS(ClauseSet *S, int tag);
