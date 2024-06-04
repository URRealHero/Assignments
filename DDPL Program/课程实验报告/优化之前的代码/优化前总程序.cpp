#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <ctime>
#include "DDPL.hpp"

using namespace std;
ClauseSet *S;
char USELESS[10000];
int *ans;
int tag = 0;
int booleans[10000];
KV labels[10000];


int main(){
    //文件读取
    clock_t start_t,finish_t;
    int n,m;//n为变元数，m为子句数
    string Line;
    
    string FileName;
    ifstream fpin;
    ofstream fpout;

    int op = 1;
    while(op){
        system("clear");
        cout << endl;
        cout << endl;
        cout << "		功能菜单 "<< endl;
		cout << "-------------------------------------------------" << endl;
		cout << "1.DPLL判断cnf文件"<< endl;
		cout << "2.求解蜂窝数独" << endl;
		cout << "0.退出"<< endl;
		cout << "-------------------------------------------------" << endl;
		cout << "	请选择你的操作[0~2]:" << endl;
        cin >> op;

        switch(op){
            case 0:
                return 0;
            case 1:{
                
                cout << "Please input the file name: ";
                cin >> FileName;
                string Fin = FileName + ".cnf";
                fpin.open(Fin,ios::in);
                start_t = clock();
                if(!fpin.is_open()){
                    std::cerr<<"cannot open the file"<<endl;
                    return 0;
                }
                char c;
                while((c = fpin.get()) == 'c'){
                    fpin.getline(USELESS,10000); // 需要建立Useless数组，否则会报错
                }
                if(c == 'p'){
                    fpin >> Line >> n >> m;
                }
                //读取子句
                ans = new int[n+1];
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
                    if(fpin.eof()) break;
                    while((fpin >> p->value) && p->value != 0){
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
                fpin.close();
                string Fout = "out/" + FileName + ".out"; 
                fpout.open(Fout,ios::out);
                if(!fpout.is_open()){
                    std::cerr<<"cannot open the file"<<endl;
                    return 0;
                }
                if(DPLL(S,n)){
                    fpout << "s 1" << endl;
                    for(int i = 1 ; i < n+1 ; i++){
                        if(ans[i] == 1)
                            fpout << i << ' ';
                        else if(ans[i] == -1)
                            fpout << -i << ' ';
                        else fpout << "error" << endl;
                        if(i % 10 == 0) fpout << endl;
                    }
                    cout << endl;
                }
                else{
                    fpout << "s 0" << endl;
                }
                finish_t = clock();
                fpout << (double)(finish_t-start_t) / CLOCKS_PER_SEC << endl;
                fpout.close();
                cout << "Done" << endl;
                delete []ans;
                getchar();
                getchar();
                
            }
                break;
        }
    }
}

bool DPLL(ClauseSet *S,int n){
    //找单子句
    ClauseSet *pS = S->next , *preS = S;
    Clauses *pC, *preC;
    
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
            // if(pS->next == NULL) preS->next = NULL;
            // else preS->next = pS->next;
            // delete pS->head->next;
            // delete pS->head;
            // delete pS;
            if(tag > 0) ans[tag] = 1;
            else ans[-tag] = -1;
            pS->head->value = 0;
            if(!SVS(S,tag)) {
                return false;//SingleValueSpread
            }
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
    int TempBool[10000] = {0};
    for(int i = 1; i <= n ; i++){
        TempBool[i] = booleans[i];
    }
    // 复制
    ClauseSet *TempS;
    TempS = new ClauseSet;
    TempS->head = NULL;
    ClauseSet *pp = new ClauseSet;
    Clauses *ppc;
    pp->head = new Clauses;
    ppc = pp->head;
    ppc->value = 1;
    ppc->next = new Clauses;
    ppc = ppc->next;
    ppc->next = NULL;
    ppc->value = v;
    pp->next = S->next;
    S->next = pp;
    // if(stack.push(v)){
    //     cout << "Stack Overflow" << endl;
    //     exit(EXIT_SUCCESS);
    // }
    Copy(S,TempS);
    TempS->next->head->next->value = -v;
    if(DPLL(S,n)) return true;
    //回溯 需要回溯booleans
    else{
        //  for(ClauseSet *delS = S->next ; delS ;){
        //      if(delS->next == NULL) S->next = NULL;
        //      else S->next = delS->next;
        //      deletion(delS);
        //      delS = S->next;
        // }
        // delete S;
         //此处未完成冗余删除！！！！
        S = TempS;
        for(int i = 1; i <= n ; i++){
        booleans[i] = TempBool[i];
    }
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
            // cout << "p1 :"<< p1->value<<endl;
            q1->next = new Clauses;
            q1 = q1->next;
            q1->value = p1->value;
            // cout << "q1:" << q1->value << endl;
            p1 = p1->next;
        }
        q1->next = NULL;
        p = p->next;
    }
    q->next = NULL;    
}


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
            // cout << "pS->head->value == 0" << endl;
            continue;
        }
        pC = preC->next;
        while(pC){
            if(pC->value == tag){
                pS->head->value = 0;
                for(preC = pS->head->next ; preC ; preC = preC->next){
                    if(tag != preC->value){
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
                pC = preC->next;
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

void SORT(int *booleans, KV *labels,int n){
    for(int i = 0 ; i <= n ; i++){
        labels[i].index = i;
        labels[i].value = booleans[i];
    }
    sort(labels, labels + n + 1, cmp);
}