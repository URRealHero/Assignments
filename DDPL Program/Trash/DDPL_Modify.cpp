#include <iostream>
#include <cstring>
#include <fstream>

#include "DDPL_Implementation.h"
ClauseSet *S;
ClauseSet *TempS;

int booleans[10000] = {0};
int TempBool[10000] = {0};
KV labels[10000]; // 排序是重排labels
using namespace std;
//本程序对较大文件用时过长！！！
int main(){
    //文件读取
    int n,m;//n为变元数，m为子句数
    string Line;
    char USELESS[500];
    ifstream fp;
    fp.open("/home/pu/PuFiles/Experiment/DDPL Program/基准算例/功能测试/sat-20.cnf",ios::in);
    if(!fp.is_open()){
        std::cerr<<"cannot open the file"<<endl;
    }
    char c;
    while((c = fp.get()) == 'c'){
        fp.getline(USELESS,500); // 需要建立Useless数组，否则会报错
    }
    if(c == 'p'){
        fp >> Line >> n >> m;
    }
    //读取子句
    S = new ClauseSet;
    S->next = new ClauseSet;
    ClauseSet *pS = S->next;
    S->head = NULL;
    for(int i = 0 ; i < m ; i++){
        pS->head = new Clauses;
        Clauses *p = pS->head;
        Clauses *pre = p;
        p->value = 0;
        p->next = new Clauses;
        p = p->next;
        if(fp.eof()) break;
        while((fp >> p->value) && p->value != 0){
            pS->head->value++;
            booleans[abs(p->value)]++;
            p->next = new Clauses;
            p = p->next;
            pre = pre->next;
        }
        pre->next = NULL;
        delete p;
        if(i != m-1){
            pS->next = new ClauseSet;
            pS = pS->next;
        }
        else pS->next = NULL;
    }
    fp.close();
    if(DPLL(S,n)){
        cout << "SATISFIED" << endl;
    }
    else{
        cout << "UNSATISFIED" << endl;
    }
    
    return 0;
}

bool DPLL(ClauseSet *S, int n){
    //找单子句
    ClauseSet *pS = S->next , *preS = S;
    Clauses *pC, *preC;
    int tag = 0;
    while(pS){
        pC = pS->head;
        if(pC->value == 0){
            if(pS->next == NULL) preS->next = NULL;
            else preS->next = pS->next;
            deletion(pS);
            pS = preS->next;
            continue;
        }
        if(pC->value == 1){
            //单子句传播
            tag = pC->next->value;
            booleans[abs(tag)] = 0;
			pC->value = 0;	
            if(SVS(S,tag) == false) return false;//SingleValueSpread
            preS = S;
            pS = S->next;
        }
        else{
            preS = pS;
            pS = pS->next;
        }
    }
    if(S->next == NULL) return true;
    //找到单子句 进行单子句传播 (用value = 0做标记为删除)
    //如果传播后有空子句(即删除了-tag后为空) 返回false
    //每次找到单子句并处理后都要从头扫描单子句 若headvalue = 0 则删除该子句（注意更新数组）
    //若从头扫描到尾都没有单子句 进行下一步
    //排序
    SORT(booleans,labels,n);
    //添加新的变元 （数量最多）
    int v = labels[0].index;
    for(int i = 1; i <= n ; i++){
        TempBool[i] = booleans[i];
    }
    // ClauseSet * pp = new ClauseSet;
    // pp->head = new Clauses;
    // pp->head->value = 1;
    // pp->head->next = new Clauses;
    // pp->head->next->value = v;
    // pp->head->next->next = NULL;
    // pp->next = S->next;
    // S->next = pp;
    //复制
    TempS = new ClauseSet;
    TempS->head = NULL;
    Copy(S,TempS);
    SVS(S,v);
    if(DPLL(S,n)) return true;
    //回溯 需要回溯booleans
    else{
          for(ClauseSet *delS = S->next ; delS ;){
              if(delS->next == NULL) S->next = NULL;
              else S->next = delS->next;
              deletion(delS);
              delS = S->next;
          }
        delete S;
        //此处未完成冗余删除！！！！
        S = TempS;
        for(int i = 1; i <= n ; i++){
        booleans[i] = TempBool[i];
    }
    SVS(S,-v);
    return(DPLL(S,n));
    }

}


void Copy(ClauseSet *S, ClauseSet *TempS){
    ClauseSet *p = S->next,*q;
    Clauses *p1, *q1;
    q = TempS;
    while(p){
        q->next = new ClauseSet;
        q = q->next;    
        p1 = p->head;
        q->head = new Clauses;
        q1 = q->head;
        q1->value = p1->value;
        p1 = p1->next;
        while(p1){
            q1->next = new Clauses;
            q1 = q1->next;
            q1->value = p1->value;
            p1 = p1->next;
        }
        q1->next = NULL;
        p = p->next;
    }
    q->next = NULL;    
}

void SORT(int *booleans, KV *labels,int n){
    for(int i = 0 ; i <= n ; i++){
        labels[i].index = i;
        labels[i].value = booleans[i];
    }
    sort(labels, labels + n + 1, cmp);
}
//指针未赋值？
void deletion(ClauseSet *S){
    Clauses *pre = S->head;
    if(pre == NULL){
        delete S;
        return;
    }
    Clauses *p = pre->next;
    while(p){
        if(p->next == NULL) pre->next = NULL;
        else pre->next = p->next;
        delete p;
        p = pre->next;
    }
    delete pre;
    delete S;
}

bool SVS(ClauseSet *S,int tag){
    ClauseSet *pS = S->next;
    Clauses *pC, *preC;
    while(pS){
        preC = pS->head;
        
        if(preC->value == 0){
            pS = pS->next;
            continue;
        }
        pC = preC->next;
        while(pC){
            if(pC->value == tag){
                pS->head->value = 0;
                for(preC = pS->head->next ; preC ; preC = preC->next){
                    if(abs(tag) != abs(preC->value)){
                        booleans[abs(preC->value)]--;
                    }
                }
                break;
            }
            else if(pC->value == -tag){
                pS->head->value--;
                if(pS->head->value == 0) 
                    return false;
                if(pC->next == NULL) preC->next = NULL;
                else preC->next = pC->next;
                delete pC;
                break;
            }
            else{
                pC=pC->next;
                preC = preC->next;
            }
        }
        pS=pS->next;
    }
    return true;
}

bool cmp(KV a, KV b){
    return a.value > b.value;
}