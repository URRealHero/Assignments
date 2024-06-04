//实现DPLL解决 SAT 问题
// Path: DDPL_Implementation.cpp

//booleans为文字计数器，labels为标签计数器
//子句用链表
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>

#include "DDPL_Implementation.h"

ClauseSet *S;
ClauseSet *TempS;

int booleans[10000] = {0};
int TempBool[10000] = {0};
KV labels[10000]; // 排序是重排labels


//定义句子ClauseSet由子句Clauses组成
//定义文字Clauses由文字value和下一文字next组成，头个文字为子句的文字数value
using namespace std;

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

bool DPLL(ClauseSet *S,int n){
    //搜索单子句
    //跳过空子句
    ClauseSet *pS = S->next , *preS = S;
    while(pS != NULL){
        Clauses *p = pS->head;
        if(p->value == 0){
            preS->next = pS->next;
            delete pS;
            pS = preS->next;
            continue;
        }
        if(p->value == 1){
            p->value = 0;
            int tag = p->next->value;
            booleans[abs(tag)] = 0;
            //单子句传播
            if(!SVS(S,tag)) return false;
            pS = S->next;
            preS = S;

            
        }
        else{
            preS = pS;
            pS = pS->next;
        }
    }
    if(S->next == NULL) return true;
    
    //若不存在单子句，进行排序，选取S中出现次数最多的文字，对S进行拷贝，对S进行单子句传播，再DPLL检查传播后的S
    //排序
    SORT(booleans,labels,n);
    //拷贝
    TempS = new ClauseSet;
    TempS->head = NULL;
    Copy(S,TempS);
    memcpy(TempBool,booleans,sizeof(booleans));
    int v = labels[0].index;
    booleans[v] = 0;
    //单子句传播
    SVS(S,v);
    if(DPLL(S,n)) return true;
    //反文字传播
    memcpy(booleans,TempBool,sizeof(booleans));
    booleans[v] = 0;
    SVS(TempS,-v);
    return DPLL(TempS,n);

    //若传播后的S为真，返回真，否则，对拷贝的S进行反文字传播，再DPLL检查传播后的S
}

void Copy(ClauseSet *S, ClauseSet *TempS){
    TempS->next = NULL;
    ClauseSet *pS = S->next;
    ClauseSet *pTempS = TempS;
    while(pS != NULL){
        pTempS->next = new ClauseSet;
        pTempS = pTempS->next;
        pTempS->head = new Clauses;
        Clauses *p = pS->head;
        Clauses *pTemp = pTempS->head;
        while(p != NULL){
            pTemp->value = p->value;
            pTemp->next = new Clauses;
            pTemp = pTemp->next;
            p = p->next;
        }
        pTemp->next = NULL;
        pS = pS->next;
    }
    pTempS->next = NULL;
}

void SORT(int *booleans, KV *labels,int n){
    for(int i = 0 ; i <= n ; i++){
        labels[i].index = i;
        labels[i].value = booleans[i];
    }
    sort(labels, labels + n + 1, cmp);
}

bool cmp(KV a, KV b){
    return a.value > b.value;
}

bool SVS(ClauseSet *S, int tag){
    //从头遍历句子，找到与单子句文字相同的文字，标记该文字所在的子句headvalue为0，将该子句内其他文字数量进行修改；删除文字的反文字
    //若删除反文字后，子句为空，返回假

    ClauseSet *pS = S->next;
    while(pS != NULL){
        Clauses *pre = pS->head;
        if(pre->value == 0){
            pS = pS->next;
            continue;
        }
        Clauses *p = pre->next;
        while(p != NULL){
            if(p->value == tag){
                pS->head->value = 0;
                p = pS->head->next;
                while(p != NULL){
                    p->value == tag ? : booleans[abs(p->value)]--;
                    p = p->next;
                }
                break;
            }
            else if(p->value == -tag){
                if(pS->head->value == 1) return false;
                pre->next = p->next;
                delete p;
                p = pre->next;
                pS->head->value--;
            }
            else{
                pre = p;
                p = p->next;
            }
        }
    }
    return true;

}
