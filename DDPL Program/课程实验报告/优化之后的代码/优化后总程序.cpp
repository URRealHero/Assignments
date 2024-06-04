#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <ctime>
#include <unordered_map>

#include "DDPL_Implementation.h"

using namespace std;
ClauseSet *S;
const int sz = 10000;
char USELESS[10000];
Stack stack(sz);
Stack SingleValueStack(sz);
Stack RecoveryStack(sz);
int HaniMat[960] = {0};
int *ans;
int ClauseNum = 0;
int cpr[10] = {0,5,6,7,8,9,8,7,6,5};
int numust[10] = {0,1,3,5,7,9,7,5,3,1};
int rowbegin[10] = {0,0,5,11,18,26,35,43,50,56};
int cnt = 0;

//把0-61转化为蜂窝数独坐标 蜂窝数独每行分别有 5,6,7,8,9,8,7,6,5个格子
unordered_map<int , int> Hash = {
    {0,110},{1,120},{2,130},{3,140},{4,150},{5,210},{6,220},{7,230},{8,240},{9,250},{10,260},{11,310},
    {12,320},{13,330},{14,340},{15,350},{16,360},{17,370},{18,410},{19,420},{20,430},{21,440},{22,450},{23,460},
    {24,470},{25,480},{26,510},{27,520},{28,530},{29,540},{30,550},{31,560},{32,570},{33,580},{34,590},{35,610},
    {36,620},{37,630},{38,640},{39,650},{40,660},{41,670},{42,680},{43,710},{44,720},{45,730},{46,740},{47,750},
    {48,760},{49,770},{50,810},{51,820},{52,830},{53,840},{54,850},{55,860},{56,910},{57,920},{58,930},{59,940},
    {60,950}
};
int numMat1[5][4] = {
    {
        1,2,3,4
    },
    {
        2,3,4,6
    },
    {
        3,4,6,7
    },
    {
        4,6,7,8
    },
    {
        6,7,8,9
    }
};
int numMat2[4][3] = {
    {1,2,3},{2,3,7},{3,7,8},{7,8,9}
};

int numMat3[3][2] = {
    {1,2} , {2,8} , {8,9}
};

int numMat4[2][1] = {
    {1},{9}
};

int LDiag[10] = {0,15,14,13,12,11,21,31,41,51};
int RDiag[10] = {0,11,12,13,14,15,26,37,48,59};


int tag = 0;
//本程序对较大文件用时过长！！！
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
        cout << "3.DPLL优化后大改cnf文件" << endl;
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
                        // booleans[abs(p->value)]++;
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
                if(DPLL(S)){
                    fpout << "SATISFIED" << endl;
                    for(int i = 1 ; i < n+1 ; i++){
                        if(ans[i] == 1)
                            fpout << i << ' ';
                        else if(ans[i] == -1)
                            fpout << -i << ' ';
                        else fpout << "error" << endl;
                        if(i % 10 == 0) fpout << endl;
                    }
                }
                else{
                    fpout << "UNSATISFIED" << endl;
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
            case 2:
                {
                // S = GenerateHaniddoku();
                // cout << "Sudoku print" << endl;
                // PrintHaniddoku(S);
                // if(!SolveHaniddoku(S)) cout << "UNSATISFIED" << endl;
                // else{
                //     cout << "SATISFIED" << endl;
                //     PrintHaniddoku(S);
                // }
                srand(time(NULL));
                int offset = rand()%100;
                char *HaniChar;
                HaniChar = new char[64];
                FILE *fp;
                fp = fopen("easy_hanidoku.txt","r");
                fseek(fp,offset*63,SEEK_SET);
                fgets(HaniChar,63,fp);
                int Hani[61];
                for(int i = 0 ; i < 61 ; i++) {
                    Hani[i] = HaniChar[i] - '0';
                }
                int _answerH[61] = {0};
                // cout << "Please input the Haniddoku: ";
                // for(int i = 0 ; i < 60 ; i++){
                //     cin >> Hani[i];
                // }
                start_t = clock();
                PrintHaniddoku(Hani);
                S = Encoding(Hani);
                ans = new int[960];
                if(DPLL(S)){ //61 * 9 = 
                    
                    string FileName = "Hani";
                    fpout.open("out/" + FileName + ".out");
                    int i,j;
                    fpout << "s 0" << endl;
                    for(i = 111, j = 0; i <= 959 ; i++){
                        if(ans[i] > 0){
                            fpout << i << ' ';
                            _answerH[j++] = i%10;
                        }
                        if (ans[i] < 0)
                            fpout << -i << ' ';
                        if(i%10 == 0)
                            fpout << endl;
                    }
                    
                    PrintHaniddoku(_answerH);
                    // Transition(_answerH,stack);
                    // PrintHaniddoku(_answerH);
                }
                else{
                    fpout << "s 0" << endl;
                }
                fpout << endl;
                finish_t = clock();
                fpout << (double)(finish_t-start_t) / CLOCKS_PER_SEC << endl;
                fpout.close();
                cout << (double)(finish_t-start_t) / CLOCKS_PER_SEC << endl;
                delete []ans;
                delete []HaniChar;
                getchar();
                getchar();
                }
                break;
            case 3:{
                ClauseSet_h *Sh;
                cout << "Please input the file name: ";
                cin >> FileName;
                string Fin = FileName + ".cnf";
                fpin.open(Fin,ios::in);
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
                positives = new Literal *[n+1];
                negatives = new Literal *[n+1]; // 初始化
                posClause = new Clauses_h *[n+1];
                negClause = new Clauses_h *[n+1];
                posSet = new ClauseSet_h *[n+1];
                negSet = new ClauseSet_h *[n+1];//不一定指向NULL
                //用new给指针数组分配空间，每个指针指向什么
                for(int i = 0 ; i < n+1 ; i++){
                    positives[i] = NULL;
                    negatives[i] = NULL;
                    posClause[i] = NULL;
                    negClause[i] = NULL;
                    posSet[i] = NULL;
                    negSet[i] = NULL;
                }
                ans = new int[n+1];
                Sh = new ClauseSet_h;
                Sh->next = new ClauseSet_h;
                ClauseSet_h *pS = Sh->next;
                Sh->head = NULL;
                for(int i = 0 ; i < m ; i++){
                    pS->head = new Clauses_h;
                    Clauses_h *p = pS->head;
                    Clauses_h *pre = p;
                    p->l = new Literal;
                    p->l->value = 0;
                    p->state = Exist;
                    p->next = new Clauses_h;
                    p = p->next;
                    p->l = new Literal;
                    if(fpin.eof()) break;
                    while((fpin >> p->l->value) && p->l->value != 0){
                        //添加线索
                        p->state = Exist;
                        if(p->l->value > 0){
                            if(posClause[p->l->value] == NULL){
                                positives[p->l->value] = p->l;
                                posClause[p->l->value] = p;
                                posSet[p->l->value] = pS;
                                p->l->numnext = nullptr;
                                p->l->antinumnext = nullptr;
                            }
                            else{
                                positives[p->l->value] = p->l;
                                p->l->numnext = posSet[p->l->value];
                                posSet[p->l->value] = pS;
                                p->l->antinumnext = posClause[p->l->value];
                                posClause[p->l->value] = p;
                            }
                        }
                        else{
                            if(negClause[-(p->l->value)] == NULL){
                                negatives[-p->l->value] = p->l;
                                negClause[-p->l->value] = p;
                                negSet[-p->l->value] = pS;
                                p->l->numnext = nullptr;
                                p->l->antinumnext = nullptr;
                            }
                            else{
                                negatives[-p->l->value] = p->l;
                                p->l->numnext = negSet[-p->l->value];
                                negSet[-p->l->value] = pS;
                                p->l->antinumnext = negClause[-p->l->value];
                                negClause[-p->l->value] = p;
                            }
                        }
                        pS->head->l->value++;
                        p->next = new Clauses_h;
                        p = p->next;
                        p->l = new Literal;
                        pre = pre->next;
                    }
                    pre->next = NULL;
                    delete p->l;
                    delete p;
                    if(i != m-1){
                        pS->next = new ClauseSet_h;
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
                start_t = clock();
                if(DPLLUpdation(Sh,n)){
                    fpout << "SATISFIED" << endl;
                    for(int i = 1 ; i < n+1 ; i++){
                        if(ans[i] == 1)
                            fpout << i << ' ';
                        else if(ans[i] == -1)
                            fpout << -i << ' ';
                        else fpout << "error" << endl;
                        if(i % 10 == 0) fpout << endl;
                    }
                }
                else{
                    fpout << "UNSATISFIED" << endl;
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
    
    return 0;
}

bool DPLL(ClauseSet *S){
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
            // booleans[abs(tag)] = 0;
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
    // SORT(booleans,labels,n);
    //添加新的变元 （数量最多）
    int v = S->next->head->next->value;
    // int TempBool[10000] = {0};
    // for(int i = 1; i <= n ; i++){
    //     TempBool[i] = booleans[i];
    // }
    //复制
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
    if(DPLL(S)) return true;
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
    //     for(int i = 1; i <= n ; i++){
    //     booleans[i] = TempBool[i];
    // }
        return(DPLL(S));
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

// void SORT(int *booleans, KV *labels,int n){
//     for(int i = 0 ; i <= n ; i++){
//         labels[i].index = i;
//         labels[i].value = booleans[i];
//     }
//     sort(labels, labels + n + 1, cmp);
// }
//指针未赋值？
void deletion(ClauseSet *S){
    
    if(S->head == NULL){
        delete S;
        return;
    }
    Clauses *pre = S->head;
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
                // for(preC = pS->head->next ; preC ; preC = preC->next){
                //     if(tag != preC->value){
                //         booleans[abs(preC->value)]--;
                //     }
                // }
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


//优化方向 递归和复制（假删除）


//蜂窝数独
//Constraints 
// 1: 1-9
// 2: Row and diagnol must be filled with consecutive numbers(it's not ok to fill in 34568 in size 5 row)即无洞性
//      2.1 Size 5: 12345 23456 34567 45678 56789
// 3. 只有5是必选

void PrintHaniddoku(int Hani[61]){
    cout << "The Haniddoku is: " << endl;
    int i;
    cout << "        |";
    for(i = 0 ; i < 5 ; i++){
        cout << ' '<< Hani[i] << " |";
    }
    cout << endl;
    cout << "      |";
    for(; i < 11 ; i++){
        cout << ' '<< Hani[i] << " |";
    }
    cout << endl;
    cout << "    |";
    for(; i < 18 ; i++){
        cout << ' '<< Hani[i] << " |";
    }
    cout << endl;
    cout << "  |";
    for(; i < 26 ; i++){
        cout << ' '<< Hani[i] << " |";
    }
    cout << endl;
    cout << "|";
    for(; i < 35 ; i++){
        cout << ' '<< Hani[i] << " |";
    }
    cout << endl;
    cout << "  |";
    for(; i < 43 ; i++){
        cout << ' '<< Hani[i] << " |";
    }
    cout << endl;
    cout << "    |";
    for(; i < 50 ; i++){
        cout << ' '<< Hani[i] << " |";
    }
    cout << endl;
    cout << "      |";
    for(; i < 56 ; i++){
        cout << ' '<< Hani[i] << " |";
    }
    cout << endl;
    cout << "        |";
    for(; i < 61 ; i++){
        cout << ' '<< Hani[i] << " |";
    }
    cout << endl;
    return;
}

void Transition(int _answerH[61], Stack stack){
    int temp;
    while(!stack.isEmpty()){
        stack.pop(temp);
        int row = temp / 100;
        int col = (temp % 100) / 10;
        int num = temp % 10;
        _answerH[rowbegin[row]+col-1] = num;
    }
    return;
}



bool DPLLHaniddoku(ClauseSet *S){
    //找单子句
    ClauseSet *pS = S->next , *preS = S;
    Clauses *pC, *preC;
    int index = 0;
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
            // booleans[abs(tag)] = 0;
            // if(pS->next == NULL) preS->next = NULL;
            // else preS->next = pS->next;
            // delete pS->head->next;
            // delete pS->head;
            // delete pS;

            pS->head->value = 0;
            if(!SVS(S,tag)) {
                return false;
            }//SingleValueSpread
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
    // SORT(booleans,labels,n);
    //添加新的变元 （数量最多）
    int v = S->next->head->next->value;
    // int TempBool[10000] = {0};
    // for(int i = 1; i <= n ; i++){
    //     TempBool[i] = booleans[i];
    // }
    //复制


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
    Copy(S,TempS);
    TempS->next->head->next->value = -v;
    if(DPLLHaniddoku(S)) return true;
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
    //     for(int i = 1; i <= n ; i++){
    //     booleans[i] = TempBool[i];
    // }
        return(DPLLHaniddoku(S));
    }

}

ClauseSet *Encoding(int Hani[61]){
    //Initializing
    ClauseSet *Han = new ClauseSet;
    Han->head = NULL;
    Han->next = NULL;
    AddCellConstriant(Han);
    AddRowConstriant(Han);
    AddLDiagConstriant(Han);
    AddRDiagConstriant(Han);
    int i = 0;
    while(i < 61){
        if(Hani[i] == 0){
            i++;
            continue;
        }
        ClauseSet *pS = new ClauseSet;
        pS->next = Han->next;
        pS->head = new Clauses;
        pS->head->value = 1;
        pS->head->next = new Clauses;
        pS->head->next->value = Hash[i]+Hani[i];
        pS->head->next->next = NULL;
        Han->next = pS;
        i++;
        ClauseNum++;
    }
    return Han; 
}
// Check 1

void AddCellConstriant(ClauseSet *Han){
    int r = 1;
    
    while(r <= 9){
        for(int c = 1 ; c <= cpr[r]; c++){
            for(int i = 1 ; i <= 8 ; i++){
                for(int j = i + 1 ; j <= 9 ; j++){
                    //先放负值
                    ClauseSet *pS;
                    pS = new ClauseSet;
                    pS->next = Han->next;
                    Clauses *pC = new Clauses;
                    int show = -(100 * r +10 * c);
                    pC->value = 2;
                    pC->next = new Clauses;
                    pC->next->value = show - i;
                    pC->next->next = new Clauses;
                    pC->next->next->value = show - j;
                    pC->next->next->next = NULL;
                    ClauseNum++;
                    pS->head = pC;
                    Han->next = pS;
                }
            }
            //再放正值
            ClauseSet *pS;
            pS = new ClauseSet;
            pS->next = Han->next;
            Clauses *pC = new Clauses;
            int show = 100 * r +10 * c;
            pC->value = 9;
            pS->head = pC;
            for(int i = 1; i <= 9 ; i++ ){
                pC->next = new Clauses;
                pC = pC->next;
                pC->value = show + i;
            }
            pC->next = NULL;
            Han->next = pS; 
            ClauseNum++;
        }
        r++;
    }
}
// Check 2


void AddRowConstriant(ClauseSet *Han){
    int r = 1;
    ClauseSet *pS;
    while(r <= 9){
        //放入约束项
        for(int i = 1 ; i <= 9 ; i++){
            for(int c1 = 1 ; c1 <= cpr[r] - 1 ; c1++){
                for(int c2 = c1 + 1; c2 <= cpr[r] ; c2++ ){
                        pS = new ClauseSet;
                        pS->next = Han->next;
                        Clauses *pC = new Clauses;
                        pC->value = 2;
                        pC->next = new Clauses;
                        pC->next->value = -(100 * r + 10 * c1 + i);
                        pC->next->next = new Clauses;
                        pC->next->next->value = -(100 * r + 10 * c2 + i);
                        pC->next->next->next = NULL;
                        pS->head = pC;
                        Han->next = pS;
                        ClauseNum++;
                }
            }
        }
        //放入必填项 cpr[r] = 5 -> 5必填 / cpr[r] = 6-> 4,5,6必填 / cpr[r] = 7-> 3,4,5,6,7必填
        // cpr[r] = 8-> 2,3,4,5,6,7,8必填 / cpr[r] = 9-> 1,2,3,4,5,6,7,8,9必填
        int turn = numust[r];
        int num = 5;
        int flag = 1;

        while(turn){
                pS = Add_must_fill(r,num);
                pS->next = Han->next;
                Han->next = pS;
                ClauseNum++;
                if(turn%2){
                    num+=flag;
                } 
                else num-=flag;
                flag++;
                turn--;
        }
        //填入选择项
        // 1234 2346 3467 4678 6789
        ch_row[r](Han);
        // ClauseNum
        r++;
    }
    
}

void AddLDiagConstriant(ClauseSet *Han){
    int flag = 1;
    ClauseSet *pS;
    Clauses *pC;
    int rowj , rowl;
    int base;
    for(int d = 1; d <= 9 ; d++){
        base = LDiag[d] / 10;
        for(int i = 1 ; i <= 9 ; i++){
            for(int j = 0 ; j < cpr[d] - 1  ; j++){
                rowj = LDiag[d] / 10 + j;
                for(int l = j + 1 ; l < cpr[d] ; l++){
                    rowl = LDiag[d] / 10 + l;
                    
                    pS = new ClauseSet;
                    pS->next = Han->next;
                    pS->head = new Clauses;
                    pC = pS->head;
                    pC->value = 2;
                    pC->next = new Clauses;
                    pC = pC->next;
                    if(rowj <= 5)
                        pC->value = - (10*(LDiag[d]+ 11 * j) + i);
                    else
                        pC->value = - (10 * (LDiag[d] + 11 * (5 - base)  + 10 * (rowj - 5)) + i);
                    pC->next = new Clauses;
                    pC = pC->next;
                    pC->next = NULL;
                    if(rowl <= 5)
                        pC->value = - (10*(LDiag[d]+11 * l) + i);
                    else
                        pC->value = - (10 * (LDiag[d] + 11 * (5-base) + 10 * (rowl - 5)) + i);
                    Han->next = pS;
                    ClauseNum++;
                    }
                }
        }

        //放入必填项
        int turn = numust[d];
        int num = 5;
        int flagg = 1;
        while(turn){
            pS = Add_must_fill(d,num,flag);
            pS->next = Han->next;
            Han->next = pS;
            ClauseNum++;
            if(turn%2){
                num+=flagg;
            }
            else
                num-=flagg;
            flagg++;
            turn--;
        }

        //放入选填项
        ch_ldiag[d](Han);

    }
}

void AddRDiagConstriant(ClauseSet *Han){
    int flag = 2;
    ClauseSet *pS;
    Clauses *pC;
    int rowj , rowl;
    int base;
    for(int d = 1; d <= 9 ; d++){
        base = RDiag[d] / 10;
        for(int i = 1 ; i <= 9 ; i++){
            for(int j = 0 ; j < cpr[d] - 1  ; j++){
                rowj = RDiag[d] / 10 + j;
                for(int l = j + 1 ; l < cpr[d] ; l++){
                    rowl = RDiag[d] / 10 + l;
                    pS = new ClauseSet;
                    pS->next = Han->next;
                    pS->head = new Clauses;
                    pC = pS->head;
                    pC->value = 2;
                    pC->next = new Clauses;
                    pC = pC->next;
                    if(rowj <= 5)
                        pC->value = - (10*(RDiag[d]+ 10 * j) + i);
                    else
                        pC->value = - (10 * (RDiag[d] + 10*(5-base) + 9 * (rowj - 5)) + i);
                    pC->next = new Clauses;
                    pC = pC->next;
                    pC->next = NULL;
                    if(rowl <= 5)
                        pC->value = - (10*(RDiag[d]+ 10 * l) + i);
                    else
                        pC->value = - (10 * (RDiag[d] + 10*(5-base) + 9 * (rowl - 5)) + i);
                    Han->next = pS;
                    ClauseNum++;
                    }
                }
        }

        //放入必填项
        int turn = numust[d];
        int num = 5;
        int flagg = 1;
        while(turn){
            pS = Add_must_fill(d,num,flag);
            pS->next = Han->next;
            Han->next = pS;
            ClauseNum++;
            if(turn%2){
                num+=flagg;
            }
            else
                num-=flagg;
            flagg++;
            turn--;
        }

        //放入选填项
        ch_rdiag[d](Han);
    }
}


ClauseSet * Add_must_fill(int r,int num){

    int c = 1;
    ClauseSet *pS = new ClauseSet;
    pS->next = NULL;
    Clauses *pC = new Clauses;
    pC->value = cpr[r];
    pS->head = pC;
    while(c <= cpr[r]){
        pC->next = new Clauses;
        pC = pC->next;
        pC->value = 100 * r + 10 * c + num;
        c++;
    }
    pC->next = NULL;
    return pS;

}
ClauseSet * Add_must_fill(int d,int num, int flag){
    if(flag == 1){
        ClauseSet *pS = new ClauseSet;
        pS->next = NULL;
        Clauses *pC = new Clauses;
        pS->head = pC;
        pC->value = cpr[d];
        int base = LDiag[d] / 10;
        for(int j = 0 ; j < cpr[d] ; j++){
            int rowj = LDiag[d] / 10 + j;
            pC->next = new Clauses;
            pC = pC->next;
            if(rowj <= 5)
                pC->value = 10 * (LDiag[d] + 11 * j) + num;
            else
                pC->value = 10 * (LDiag[d] + 11 * (5-base) + 10 * (rowj - 5)) + num;
        }
        pC->next = NULL;
        return pS;
    }
    if(flag == 2){
        ClauseSet *pS = new ClauseSet;
        pS->next = NULL;
        Clauses *pC = new Clauses;
        pS->head = pC;
        pC->value = cpr[d];
        int base = RDiag[d] / 10;
        for(int j = 0 ; j < cpr[d] ; j++){
            int rowj = RDiag[d] / 10 + j;
            pC->next = new Clauses;
            pC = pC->next;
            if(rowj <= 5)
                pC->value = 10 * (RDiag[d] + 10 * j) + num;
            else
                pC->value = 10 * (RDiag[d] + 10*(5-base) + 9 * (rowj - 5)) + num;
        }
        pC->next = NULL;
        return pS;
    }
    else{
        exit(EXIT_SUCCESS);
    }
}

void Add_choose_row1(ClauseSet *Han){
    int r = 1;
    for(int i = 0 ; i < 4 ; i++){
        int num1 = numMat1[0][i];
        for(int j = 0 ; j < 4 ; j++){
            int num2 = numMat1[1][j];
            for(int k = 0; k < 4 ; k++){
                int num3 = numMat1[2][k];
                for (int l = 0 ; l < 4 ; l++){
                    int num4 = numMat1[3][l];
                    for(int m = 0 ; m < 4 ; m++){
                        int num5 = numMat1[4][m];
                        ClauseSet *pS;
                        pS= new ClauseSet;
                        pS->next = Han->next;
                        pS->head = new Clauses;
                        Clauses *pC = new Clauses;
                        Clauses *preC;
                        Clauses * phead = pS->head;
                        phead->next = pC;
                        phead->value = 0;
                        for(int c = 1; c <= 5 ; c++){
                            pC->value = 100 * r + 10 * c + num1;
                            pC->next = new Clauses;
                            pC = pC->next;
                            pC->value = 100 * r + 10 * c + num2;
                            pC->next = new Clauses;
                            pC = pC->next;
                            pC->value = 100 * r + 10 * c + num3;
                            pC->next = new Clauses;
                            pC = pC->next;
                            pC->value = 100 * r + 10 * c + num4;
                            pC->next = new Clauses;
                            pC = pC->next;
                            pC->value = 100 * r + 10 * c + num5;
                            preC = pC;
                            pC->next = new Clauses;
                            pC = pC->next;
                            phead->value += 5;
                        }
                        preC->next = NULL;
                        delete pC;
                        Han->next = pS;
                        ClauseNum++;
                    }
                }
            }
        }
    }
}
void Add_choose_row2(ClauseSet *Han){
    int r = 2;
    for(int i = 0 ; i < 3 ; i++){
        int num1 = numMat2[0][i];
        for(int j = 0 ; j < 3 ; j++){
            int num2 = numMat2[1][j];
            for(int k = 0; k < 3 ; k++){
                int num3 = numMat1[2][k];
                for (int l = 0 ; l < 3 ; l++){
                    int num4 = numMat1[3][l];
                    ClauseSet *pS;
                    pS = new ClauseSet;
                    pS->next = Han->next;
                    pS->head = new Clauses;
                    Clauses *pC = new Clauses;
                    Clauses *preC;
                    Clauses * phead = pS->head;
                    phead->next = pC;
                    phead->value = 0;
                        for(int c = 1; c <= 6 ; c++){
                            pC->value = 100 * r + 10 * c + num1;
                            pC->next = new Clauses;
                            pC = pC->next;
                            pC->value = 100 * r + 10 * c + num2;
                            pC->next = new Clauses;
                            pC = pC->next;
                            pC->value = 100 * r + 10 * c + num3;
                            pC->next = new Clauses;
                            pC = pC->next;
                            pC->value = 100 * r + 10 * c + num4;
                            preC =pC;
                            pC->next = new Clauses;
                            pC = pC->next;
                            phead->value += 4;
                        }
                        preC->next = NULL;
                        delete pC;
                        Han->next = pS;
                        ClauseNum++;
                    }
                }
            }
        }
    }
void Add_choose_row3(ClauseSet *Han){
    int r = 3;
    for(int i = 0 ; i < 2 ; i++){
        int num1 = numMat3[0][i];
        for(int j = 0 ; j < 2 ; j++){
            int num2 = numMat3[1][j];
            for(int k = 0; k < 2 ; k++){
                int num3 = numMat3[2][k];

                ClauseSet *pS;
                pS = new ClauseSet;
                pS->next = Han->next;
                pS->head = new Clauses;
                Clauses *pC = new Clauses;
                Clauses *preC;
                Clauses * phead = pS->head;
                phead->next = pC;
                phead->value = 0;
                    for(int c = 1; c <= 7 ; c++){
                        pC->value = 100 * r + 10 * c + num1;
                        pC->next = new Clauses;
                        pC = pC->next;
                        pC->value = 100 * r + 10 * c + num2;
                        pC->next = new Clauses;
                        pC = pC->next;
                        pC->value = 100 * r + 10 * c + num3;
                        preC =pC;
                        pC->next = new Clauses;
                        pC = pC->next;
                        phead->value += 3;
                    }
                    preC->next = NULL;
                    delete pC;
                    Han->next = pS;
                    ClauseNum++;
                    }
                }
            }
        }
void Add_choose_row4(ClauseSet *Han){
    int r = 4;
    for(int i = 0 ; i < 1 ; i++){
        int num1 = numMat4[0][i];
        for(int j = 0 ; j < 1 ; j++){
            int num2 = numMat4[1][j];
            ClauseSet *pS;
            pS = new ClauseSet;
            pS->next = Han->next;
            pS->head = new Clauses;
            Clauses *pC = new Clauses;
            Clauses *preC;
            Clauses * phead = pS->head;
            phead->next = pC;
            phead->value = 0;
                for(int c = 1; c <= 8 ; c++){
                    pC->value = 100 * r + 10 * c + num1;
                    pC->next = new Clauses;
                    pC = pC->next;
                    pC->value = 100 * r + 10 * c + num2;
                    preC =pC;
                    pC->next = new Clauses;
                    pC = pC->next;
                    phead->value += 2;
                }
                preC->next = NULL;
                delete pC;
                Han->next = pS;
                ClauseNum++;
                }
            }
        }
void Add_choose_row5(ClauseSet *Han){}
void Add_choose_row6(ClauseSet *Han){
    int r = 6;
    for(int i = 0 ; i < 1 ; i++){
        int num1 = numMat4[0][i];
        for(int j = 0 ; j < 1 ; j++){
            int num2 = numMat4[1][j];
            ClauseSet *pS;
            pS = new ClauseSet;
            pS->next = Han->next;
            pS->head = new Clauses;
            Clauses *pC = new Clauses;
            Clauses *preC;
            Clauses * phead = pS->head;
            phead->next = pC;
            phead->value = 0;
                for(int c = 1; c <= 8 ; c++){
                    pC->value = 100 * r + 10 * c + num1;
                    pC->next = new Clauses;
                    pC = pC->next;
                    pC->value = 100 * r + 10 * c + num2;
                    preC =pC;
                    pC->next = new Clauses;
                    pC = pC->next;
                    phead->value += 2;
                }
                preC->next = NULL;
                delete pC;
                Han->next = pS;
                ClauseNum++;
                }
            }
        }
void Add_choose_row7(ClauseSet *Han){
    int r = 7;
    for(int i = 0 ; i < 2 ; i++){
        int num1 = numMat3[0][i];
        for(int j = 0 ; j < 2 ; j++){
            int num2 = numMat3[1][j];
            for(int k = 0; k < 2 ; k++){
                int num3 = numMat3[2][k];

                ClauseSet *pS;
                pS = new ClauseSet;
                pS->next = Han->next;
                pS->head = new Clauses;
                Clauses *pC = new Clauses;
                Clauses *preC;
                Clauses * phead = pS->head;
                phead->next = pC;
                phead->value = 0;
                    for(int c = 1; c <= 7 ; c++){
                        pC->value = 100 * r + 10 * c + num1;
                        pC->next = new Clauses;
                        pC = pC->next;
                        pC->value = 100 * r + 10 * c + num2;
                        pC->next = new Clauses;
                        pC = pC->next;
                        pC->value = 100 * r + 10 * c + num3;
                        preC =pC;
                        pC->next = new Clauses;
                        pC = pC->next;
                        phead->value += 3;
                    }
                    preC->next = NULL;
                    delete pC;
                    Han->next = pS;
                    ClauseNum++;
                    }
                }
            }
        }
void Add_choose_row8(ClauseSet *Han){
    int r = 8;
    for(int i = 0 ; i < 3 ; i++){
        int num1 = numMat2[0][i];
        for(int j = 0 ; j < 3 ; j++){
            int num2 = numMat2[1][j];
            for(int k = 0; k < 3 ; k++){
                int num3 = numMat1[2][k];
                for (int l = 0 ; l < 3 ; l++){
                    int num4 = numMat1[3][l];
                    ClauseSet *pS;
                    pS = new ClauseSet;
                    pS->next = Han->next;
                    pS->head = new Clauses;
                    Clauses *pC = new Clauses;
                    Clauses *preC;
                    Clauses * phead = pS->head;
                    phead->next = pC;
                    phead->value = 0;
                        for(int c = 1; c <= 6 ; c++){
                            pC->value = 100 * r + 10 * c + num1;
                            pC->next = new Clauses;
                            pC = pC->next;
                            pC->value = 100 * r + 10 * c + num2;
                            pC->next = new Clauses;
                            pC = pC->next;
                            pC->value = 100 * r + 10 * c + num3;
                            pC->next = new Clauses;
                            pC = pC->next;
                            pC->value = 100 * r + 10 * c + num4;
                            preC =pC;
                            pC->next = new Clauses;
                            pC = pC->next;
                            phead->value += 4;
                        }
                        preC->next = NULL;
                        delete pC;
                        Han->next = pS;
                        ClauseNum++;
                    }
                }
            }
        }
    }
void Add_choose_row9(ClauseSet *Han){
    int r = 9;
    for(int i = 0 ; i < 4 ; i++){
        int num1 = numMat1[0][i];
        for(int j = 0 ; j < 4 ; j++){
            int num2 = numMat1[1][j];
            for(int k = 0; k < 4 ; k++){
                int num3 = numMat1[2][k];
                for (int l = 0 ; l < 4 ; l++){
                    int num4 = numMat1[3][l];
                    for(int m = 0 ; m < 4 ; m++){
                        int num5 = numMat1[4][m];
                        ClauseSet *pS;
                        pS = new ClauseSet;
                        pS->next = Han->next;
                        pS->head = new Clauses;
                        Clauses *pC = new Clauses;
                        Clauses *preC = new Clauses;
                        Clauses * phead = pS->head;
                        phead->next = pC;
                        phead->value = 0;
                        for(int c = 1; c <= 5 ; c++){
                            pC->value = 100 * r + 10 * c + num1;
                            pC->next = new Clauses;
                            pC = pC->next;
                            pC->value = 100 * r + 10 * c + num2;
                            pC->next = new Clauses;
                            pC = pC->next;
                            pC->value = 100 * r + 10 * c + num3;
                            pC->next = new Clauses;
                            pC = pC->next;
                            pC->value = 100 * r + 10 * c + num4;
                            pC->next = new Clauses;
                            pC = pC->next;
                            pC->value = 100 * r + 10 * c + num5;
                            preC = pC;
                            pC->next = new Clauses;
                            pC = pC->next;
                            phead->value += 5;
                        }
                        preC->next = NULL;
                        delete pC;
                        Han->next = pS;
                        ClauseNum++;
                    }
                }
            }
        }
    }
}
void Add_choose_ldiag1(ClauseSet *Han){
        int d = 1;   
        for(int i = 0 ; i < 4 ; i++){
            int num1 = numMat1[0][i];
            for(int j = 0 ; j < 4 ; j++){
                int num2 = numMat1[1][j];
                for(int k = 0; k < 4 ; k++){
                    int num3 = numMat1[2][k];
                    for (int l = 0 ; l < 4 ; l++){
                        int num4 = numMat1[3][l];
                        for(int m = 0 ; m < 4 ; m++){
                            int num5 = numMat1[4][m];
                            ClauseSet *pS;
                            pS = new ClauseSet;
                            pS->next = Han->next;
                            pS->head = new Clauses;
                            Clauses *pC = new Clauses;
                            Clauses *preC;
                            Clauses * phead = pS->head;
                            phead->next = pC;
                            phead->value = 0;
                            int db = LDiag[d] / 10;
                            for(int a = 0; a < cpr[d] ; a++){
                                int r = LDiag[d] / 10 + a;
                                int base;
                                if(r <= 5){
                                    base = LDiag[d] + 11 * a;
                                }
                                else{
                                    base = LDiag[d] + 11 * (5-db) + 10 * (r - 5);
                                }
                                pC->value = 10 * base + num1;
                                pC->next = new Clauses;
                                pC = pC->next;
                                pC->value = 10 * base + num2;
                                pC->next = new Clauses;
                                pC = pC->next;
                                pC->value = 10 * base + num3;
                                pC->next = new Clauses;
                                pC = pC->next;
                                pC->value = 10 * base + num4;
                                pC->next = new Clauses;
                                pC = pC->next;
                                pC->value = 10 * base + num5;
                                preC = pC;
                                pC->next = new Clauses;
                                pC = pC->next;
                                phead->value += 5;
                            }
                            preC->next = NULL;
                            delete pC;
                            Han->next = pS;
                            ClauseNum++;
                        }
                    }
                }
            }
        }
    
}
void Add_choose_ldiag2(ClauseSet *Han){
    int d = 2;    
        for(int i = 0 ; i < 3 ; i++){
            int num1 = numMat2[0][i];
            for(int j = 0 ; j < 3 ; j++){
                int num2 = numMat2[1][j];
                for(int k = 0; k < 3 ; k++){
                    int num3 = numMat2[2][k];
                    for (int l = 0 ; l < 3 ; l++){
                        int num4 = numMat2[3][l];
                            ClauseSet *pS;
                            pS = new ClauseSet;
                            pS->next = Han->next;
                            pS->head = new Clauses;
                            Clauses *pC = new Clauses;
                            Clauses *preC;
                            Clauses * phead = pS->head;
                            phead->next = pC;
                            phead->value = 0;
                            int db = LDiag[d] / 10;
                            for(int a = 0; a < cpr[d] ; a++){
                                int r = LDiag[d] / 10 + a;
                                int base;
                                if(r <= 5){
                                    base = LDiag[d] + 11 * a;
                                }
                                else{
                                    base = LDiag[d] + 11 * (5 - db) + 10 * (r - 5);
                                }
                                pC->value = 10 * base + num1;
                                pC->next = new Clauses;
                                pC = pC->next;
                                pC->value = 10 * base + num2;
                                pC->next = new Clauses;
                                pC = pC->next;
                                pC->value = 10 * base + num3;
                                pC->next = new Clauses;
                                pC = pC->next;
                                pC->value = 10 * base + num4;
                                preC = pC;
                                pC->next = new Clauses;
                                pC = pC->next;
                                phead->value += 4;
                            }
                            preC->next = NULL;
                            delete pC;
                            Han->next = pS;
                            ClauseNum++;
                        }
                    }
                }
            }
        
}
void Add_choose_ldiag3(ClauseSet *Han){
    int d = 3;    
        for(int i = 0 ; i < 2 ; i++){
            int num1 = numMat3[0][i];
            for(int j = 0 ; j < 2 ; j++){
                int num2 = numMat3[1][j];
                for(int k = 0; k < 2 ; k++){
                    int num3 = numMat3[2][k];
                            ClauseSet *pS;
                            pS = new ClauseSet;
                            pS->next = Han->next;
                            pS->head = new Clauses;
                            Clauses *pC = new Clauses;
                            Clauses *preC;
                            Clauses * phead = pS->head;
                            phead->next = pC;
                            phead->value = 0;
                            int db = LDiag[d] / 10;
                            for(int a = 0; a < cpr[d] ; a++){
                                int r = LDiag[d] / 10 + a;
                                int base;
                                if(r <= 5){
                                    base = LDiag[d] + 11 * a;
                                }
                                else{
                                    base = LDiag[d] + 11 * (5-db) + 10 * (r - 5);
                                }
                                pC->value = 10 * base + num1;
                                pC->next = new Clauses;
                                pC = pC->next;
                                pC->value = 10 * base + num2;
                                pC->next = new Clauses;
                                pC = pC->next;
                                pC->value = 10 * base + num3;
                                preC = pC;
                                pC->next = new Clauses;
                                pC = pC->next;
                                phead->value += 3;
                            }
                            preC->next = NULL;
                            delete pC;
                            Han->next = pS;
                            ClauseNum++;
                        }
                    }
                }
            }

void Add_choose_ldiag4(ClauseSet *Han){
    int d = 4;    
            for(int i = 0 ; i < 1 ; i++){
                int num1 = numMat4[0][i];
                for(int j = 0 ; j < 1 ; j++){
                    int num2 = numMat4[1][j];
                                ClauseSet *pS;
                                pS = new ClauseSet;
                                pS->next = Han->next;
                                pS->head = new Clauses;
                                Clauses *pC = new Clauses;
                                Clauses *preC;
                                Clauses * phead = pS->head;
                                phead->next = pC;
                                phead->value = 0;
                                int db = LDiag[d] / 10;
                                for(int a = 0; a < cpr[d] ; a++){
                                    int r = LDiag[d] / 10 + a;
                                    int base;
                                    if(r <= 5){
                                        base = LDiag[d] + 11 * a;
                                    }
                                    else{
                                        base = LDiag[d] + 11 * (5-db) + 10 * (r - 5);
                                    }
                                    pC->value = 10 * base + num1;
                                    pC->next = new Clauses;
                                    pC = pC->next;
                                    pC->value = 10 * base + num2;
                                    preC = pC;
                                    pC->next = new Clauses;
                                    pC = pC->next;
                                    phead->value += 2;
                                }
                                preC->next = NULL;
                                delete pC;
                                Han->next = pS;
                                ClauseNum++;
                            }
                        }
                }

void Add_choose_ldiag5(ClauseSet *Han){}
void Add_choose_ldiag6(ClauseSet *Han){
int d = 6;    
            for(int i = 0 ; i < 1 ; i++){
                int num1 = numMat4[0][i];
                for(int j = 0 ; j < 1 ; j++){
                    int num2 = numMat4[1][j];
                                ClauseSet *pS;
                                pS = new ClauseSet;
                                pS->next = Han->next;
                                pS->head = new Clauses;
                                Clauses *pC = new Clauses;
                                Clauses *preC;
                                Clauses * phead = pS->head;
                                phead->next = pC;
                                phead->value = 0;
                                int db = LDiag[d] / 10;
                                for(int a = 0; a < cpr[d] ; a++){
                                    int r = LDiag[d] / 10 + a;
                                    int base;
                                    if(r <= 5){
                                        base = LDiag[d] + 11 * a;
                                    }
                                    else{
                                        base = LDiag[d] + 11 * (5-db) + 10 * (r - 5);
                                    }
                                    pC->value = 10 * base + num1;
                                    pC->next = new Clauses;
                                    pC = pC->next;
                                    pC->value = 10 * base + num2;
                                    preC = pC;
                                    pC->next = new Clauses;
                                    pC = pC->next;
                                    phead->value += 2;
                                }
                                preC->next = NULL;
                                delete pC;
                                Han->next = pS;
                                ClauseNum++;
                            }
                        }
}
void Add_choose_ldiag7(ClauseSet *Han){
int d = 7;    
        for(int i = 0 ; i < 2 ; i++){
            int num1 = numMat3[0][i];
            for(int j = 0 ; j < 2 ; j++){
                int num2 = numMat3[1][j];
                for(int k = 0; k < 2 ; k++){
                    int num3 = numMat3[2][k];
                            ClauseSet *pS;
                            pS = new ClauseSet;
                            pS->next = Han->next;
                            pS->head = new Clauses;
                            Clauses *pC = new Clauses;
                            Clauses *preC;
                            Clauses * phead = pS->head;
                            phead->next = pC;
                            phead->value = 0;
                            int db = LDiag[d] / 10;
                            for(int a = 0; a < cpr[d] ; a++){
                                int r = LDiag[d] / 10 + a;
                                int base;
                                if(r <= 5){
                                    base = LDiag[d] + 11 * a;
                                }
                                else{
                                    base = LDiag[d] + 11 * (5-db) + 10 * (r - 5);
                                }
                                pC->value = 10 * base + num1;
                                pC->next = new Clauses;
                                pC = pC->next;
                                pC->value = 10 * base + num2;
                                pC->next = new Clauses;
                                pC = pC->next;
                                pC->value = 10 * base + num3;
                                preC = pC;
                                pC->next = new Clauses;
                                pC = pC->next;
                                phead->value += 3;
                            }
                            preC->next = NULL;
                            delete pC;
                            Han->next = pS;
                            ClauseNum++;
                        }
                    }
                }
}
void Add_choose_ldiag8(ClauseSet *Han){
    int d = 8;    
        for(int i = 0 ; i < 3 ; i++){
            int num1 = numMat2[0][i];
            for(int j = 0 ; j < 3 ; j++){
                int num2 = numMat2[1][j];
                for(int k = 0; k < 3 ; k++){
                    int num3 = numMat2[2][k];
                    for (int l = 0 ; l < 3 ; l++){
                        int num4 = numMat2[3][l];
                            ClauseSet *pS;
                            pS = new ClauseSet;
                            pS->next = Han->next;
                            pS->head = new Clauses;
                            Clauses *pC = new Clauses;
                            Clauses *preC;
                            Clauses * phead = pS->head;
                            phead->next = pC;
                            phead->value = 0;
                            int db = LDiag[d] / 10;
                            for(int a = 0; a < cpr[d] ; a++){
                                int r = LDiag[d] / 10 + a;
                                int base;
                                if(r <= 5){
                                    base = LDiag[d] + 11 * a;
                                }
                                else{
                                    base = LDiag[d] + 11 * (5-db) + 10 * (r - 5);
                                }
                                pC->value = 10 * base + num1;
                                pC->next = new Clauses;
                                pC = pC->next;
                                pC->value = 10 * base + num2;
                                pC->next = new Clauses;
                                pC = pC->next;
                                pC->value = 10 * base + num3;
                                pC->next = new Clauses;
                                pC = pC->next;
                                pC->value = 10 * base + num4;
                                preC = pC;
                                pC->next = new Clauses;
                                pC = pC->next;
                                phead->value += 4;
                            }
                            preC->next = NULL;
                            delete pC;
                            Han->next = pS;
                            ClauseNum++;
                        }
                    }
                }
            }
}
void Add_choose_ldiag9(ClauseSet *Han){
    int d = 9;    
        for(int i = 0 ; i < 4 ; i++){
            int num1 = numMat1[0][i];
            for(int j = 0 ; j < 4 ; j++){
                int num2 = numMat1[1][j];
                for(int k = 0; k < 4 ; k++){
                    int num3 = numMat1[2][k];
                    for (int l = 0 ; l < 4 ; l++){
                        int num4 = numMat1[3][l];
                        for(int m = 0 ; m < 4 ; m++){
                            int num5 = numMat1[4][m];
                            ClauseSet *pS;
                            pS = new ClauseSet;
                            pS->next = Han->next;
                            pS->head = new Clauses;
                            Clauses *pC = new Clauses;
                            Clauses *preC;
                            Clauses * phead = pS->head;
                            phead->next = pC;
                            phead->value = 0;
                            int db = LDiag[d] / 10;
                            for(int a = 0; a < cpr[d] ; a++){
                                int r = LDiag[d] / 10 + a;
                                int base;
                                if(r <= 5){
                                    base = LDiag[d] + 11 * a;
                                }
                                else{
                                    base = LDiag[d] + 11 * (5-db) + 10 * (r - 5);
                                }
                                pC->value = 10 * base + num1;
                                pC->next = new Clauses;
                                pC = pC->next;
                                pC->value = 10 * base + num2;
                                pC->next = new Clauses;
                                pC = pC->next;
                                pC->value = 10 * base + num3;
                                pC->next = new Clauses;
                                pC = pC->next;
                                pC->value = 10 * base + num4;
                                pC->next = new Clauses;
                                pC = pC->next;
                                pC->value = 10 * base + num5;
                                preC = pC;
                                pC->next = new Clauses;
                                pC = pC->next;
                                phead->value += 5;
                            }
                            preC->next = NULL;
                            delete pC;
                            Han->next = pS;
                            ClauseNum++;
                        }
                    }
                }
            }
        }
}
void Add_choose_rdiag1(ClauseSet *Han){
    int d = 1;    
    for(int i = 0 ; i < 4 ; i++){
        int num1 = numMat1[0][i];
        for(int j = 0 ; j < 4 ; j++){
            int num2 = numMat1[1][j];
            for(int k = 0; k < 4 ; k++){
                int num3 = numMat1[2][k];
                for (int l = 0 ; l < 4 ; l++){
                    int num4 = numMat1[3][l];
                    for(int m = 0 ; m < 4 ; m++){
                        int num5 = numMat1[4][m];
                        ClauseSet *pS;
                        pS = new ClauseSet;
                        pS->next = Han->next;
                        pS->head = new Clauses;
                        Clauses *pC = new Clauses;
                        Clauses *preC;
                        Clauses * phead = pS->head;
                        phead->next = pC;
                        phead->value = 0;
                        int db = RDiag[d] / 10;
                        for(int a = 0; a < cpr[d] ; a++){
                            int r = RDiag[d] / 10 + a;
                            int base;
                            if(r <= 5){
                                base = RDiag[d] + 10 * a;
                            }
                            else{
                                base = RDiag[d] + 10 * (5-db) + 9 * (r - 5);
                            }
                            pC->value = 10 * base + num1;
                            pC->next = new Clauses;
                            pC = pC->next;
                            pC->value = 10 * base + num2;
                            pC->next = new Clauses;
                            pC = pC->next;
                            pC->value = 10 * base + num3;
                            pC->next = new Clauses;
                            pC = pC->next;
                            pC->value = 10 * base + num4;
                            pC->next = new Clauses;
                            pC = pC->next;
                            pC->value = 10 * base + num5;
                            preC = pC;
                            pC->next = new Clauses;
                            pC = pC->next;
                            phead->value += 5;
                        }
                        preC->next = NULL;
                        delete pC;
                        Han->next = pS;
                        ClauseNum++;
                    }
                }
            }
        }
    }
}
void Add_choose_rdiag2(ClauseSet *Han){
    int d = 2;    
    for(int i = 0 ; i < 3 ; i++){
        int num1 = numMat2[0][i];
        for(int j = 0 ; j < 3 ; j++){
            int num2 = numMat2[1][j];
            for(int k = 0; k < 3 ; k++){
                int num3 = numMat2[2][k];
                for (int l = 0 ; l < 3 ; l++){
                    int num4 = numMat2[3][l];
                
                    ClauseSet *pS;
                    pS = new ClauseSet;
                    pS->next = Han->next;
                    pS->head = new Clauses;
                    Clauses *pC = new Clauses;
                    Clauses *preC;
                    Clauses * phead = pS->head;
                    phead->next = pC;
                    phead->value = 0;
                    int db = RDiag[d] / 10;
                    for(int a = 0; a < cpr[d] ; a++){
                        int r = RDiag[d] / 10 + a;
                        int base;
                        if(r <= 5){
                            base = RDiag[d] + 10 * a;
                        }
                        else{
                            base = RDiag[d] + 10 * (5-db) + 9 * (r - 5);
                        }
                        pC->value = 10 * base + num1;
                        pC->next = new Clauses;
                        pC = pC->next;
                        pC->value = 10 * base + num2;
                        pC->next = new Clauses;
                        pC = pC->next;
                        pC->value = 10 * base + num3;
                        pC->next = new Clauses;
                        pC = pC->next;
                        pC->value = 10 * base + num4;
                        preC = pC;
                        pC->next = new Clauses;
                        pC = pC->next;
                        phead->value += 4;
                    }
                    preC->next = NULL;
                    delete pC;
                    Han->next = pS;
                    ClauseNum++;
                
                }
            }
        }
    }
}
void Add_choose_rdiag3(ClauseSet *Han){
    int d = 3;    
    for(int i = 0 ; i < 2 ; i++){
        int num1 = numMat3[0][i];
        for(int j = 0 ; j < 2 ; j++){
            int num2 = numMat3[1][j];
            for(int k = 0; k < 2 ; k++){
                int num3 = numMat3[2][k];
                ClauseSet *pS;
                pS = new ClauseSet;
                pS->next = Han->next;
                pS->head = new Clauses;
                Clauses *pC = new Clauses;
                Clauses *preC;
                Clauses * phead = pS->head;
                phead->next = pC;
                phead->value = 0;
                int db = RDiag[d] / 10;
                for(int a = 0; a < cpr[d] ; a++){
                    int r = RDiag[d] / 10 + a;
                    int base;
                    if(r <= 5){
                        base = RDiag[d] + 10 * a;
                    }
                    else{
                        base = RDiag[d] + 10 * (5-db) + 9 * (r - 5);
                    }
                    pC->value = 10 * base + num1;
                    pC->next = new Clauses;
                    pC = pC->next;
                    pC->value = 10 * base + num2;
                    pC->next = new Clauses;
                    pC = pC->next;
                    pC->value = 10 * base + num3;
                    preC = pC;
                    pC->next = new Clauses;
                    pC = pC->next;
                    phead->value += 3;
                }
                preC->next = NULL;
                delete pC;
                Han->next = pS;
                ClauseNum++;
            
            }
        }
    }
}

void Add_choose_rdiag4(ClauseSet *Han){
    int d = 4;    
    for(int i = 0 ; i < 1 ; i++){
        int num1 = numMat4[0][i];
        for(int j = 0 ; j < 1 ; j++){
            int num2 = numMat4[1][j];
            ClauseSet *pS;
            pS = new ClauseSet;
            pS->next = Han->next;
            pS->head = new Clauses;
            Clauses *pC = new Clauses;
            Clauses *preC;
            Clauses * phead = pS->head;
            phead->next = pC;
            phead->value = 0;
            int db = RDiag[d] / 10;
            for(int a = 0; a < cpr[d] ; a++){
                int r = RDiag[d] / 10 + a;
                int base;
                if(r <= 5){
                    base = RDiag[d] + 10 * a;
                }
                else{
                    base = RDiag[d] + 10 * (5-db) + 9 * (r - 5);
                }
                pC->value = 10 * base + num1;
                pC->next = new Clauses;
                pC = pC->next;
                pC->value = 10 * base + num2;
                preC = pC;
                pC->next = new Clauses;
                pC = pC->next;
                phead->value += 2;
            }
            preC->next = NULL;
            delete pC;
            Han->next = pS;
            ClauseNum++;
        
        }
    }
}

void Add_choose_rdiag5(ClauseSet *Han){}
void Add_choose_rdiag6(ClauseSet *Han){
    int d = 6;    
    for(int i = 0 ; i < 1 ; i++){
        int num1 = numMat4[0][i];
        for(int j = 0 ; j < 1 ; j++){
            int num2 = numMat4[1][j];
            ClauseSet *pS;
            pS = new ClauseSet;
            pS->next = Han->next;
            pS->head = new Clauses;
            Clauses *pC = new Clauses;
            Clauses *preC;
            Clauses * phead = pS->head;
            phead->next = pC;
            phead->value = 0;
            int db = RDiag[d] / 10;
            for(int a = 0; a < cpr[d] ; a++){
                int r = RDiag[d] / 10 + a;
                int base;
                if(r <= 5){
                    base = RDiag[d] + 10 * a;
                }
                else{
                    base = RDiag[d] + 10 * (5-db) + 9 * (r - 5);
                }
                pC->value = 10 * base + num1;
                pC->next = new Clauses;
                pC = pC->next;
                pC->value = 10 * base + num2;
                preC = pC;
                pC->next = new Clauses;
                pC = pC->next;
                phead->value += 2;
            }
            preC->next = NULL;
            delete pC;
            Han->next = pS;
            ClauseNum++;
        
        }
    }
}
void Add_choose_rdiag7(ClauseSet *Han){
    int d = 7;    
    for(int i = 0 ; i < 2 ; i++){
        int num1 = numMat3[0][i];
        for(int j = 0 ; j < 2 ; j++){
            int num2 = numMat3[1][j];
            for(int k = 0; k < 2 ; k++){
                int num3 = numMat3[2][k];
                ClauseSet *pS;
                pS = new ClauseSet;
                pS->next = Han->next;
                pS->head = new Clauses;
                Clauses *pC = new Clauses;
                Clauses *preC;
                Clauses * phead = pS->head;
                phead->next = pC;
                phead->value = 0;
                int db = RDiag[d] / 10;
                for(int a = 0; a < cpr[d] ; a++){
                    int r = RDiag[d] / 10 + a;
                    int base;
                    if(r <= 5){
                        base = RDiag[d] + 10 * a;
                    }
                    else{
                        base = RDiag[d] + 10 * (5-db) + 9 * (r - 5);
                    }
                    pC->value = 10 * base + num1;
                    pC->next = new Clauses;
                    pC = pC->next;
                    pC->value = 10 * base + num2;
                    pC->next = new Clauses;
                    pC = pC->next;
                    pC->value = 10 * base + num3;
                    preC = pC;
                    pC->next = new Clauses;
                    pC = pC->next;
                    phead->value += 3;
                }
                preC->next = NULL;
                delete pC;
                Han->next = pS;
                ClauseNum++;
            
            }
        }
    }
}
void Add_choose_rdiag8(ClauseSet *Han){
    int d = 8;    
    for(int i = 0 ; i < 3 ; i++){
        int num1 = numMat2[0][i];
        for(int j = 0 ; j < 3 ; j++){
            int num2 = numMat2[1][j];
            for(int k = 0; k < 3 ; k++){
                int num3 = numMat2[2][k];
                for (int l = 0 ; l < 3 ; l++){
                    int num4 = numMat2[3][l];
                
                    ClauseSet *pS;
                    pS = new ClauseSet;
                    pS->next = Han->next;
                    pS->head = new Clauses;
                    Clauses *pC = new Clauses;
                    Clauses *preC;
                    Clauses * phead = pS->head;
                    phead->next = pC;
                    phead->value = 0;
                    int db = RDiag[d] / 10;
                    for(int a = 0; a < cpr[d] ; a++){
                        int r = RDiag[d] / 10 + a;
                        int base;
                        if(r <= 5){
                            base = RDiag[d] + 10 * a;
                        }
                        else{
                            base = RDiag[d] + 10 * (5-db) + 9 * (r - 5);
                        }
                        pC->value = 10 * base + num1;
                        pC->next = new Clauses;
                        pC = pC->next;
                        pC->value = 10 * base + num2;
                        pC->next = new Clauses;
                        pC = pC->next;
                        pC->value = 10 * base + num3;
                        pC->next = new Clauses;
                        pC = pC->next;
                        pC->value = 10 * base + num4;
                        preC = pC;
                        pC->next = new Clauses;
                        pC = pC->next;
                        phead->value += 4;
                    }
                    preC->next = NULL;
                    delete pC;
                    Han->next = pS;
                    ClauseNum++;
                
                }
            }
        }
    }
}
void Add_choose_rdiag9(ClauseSet *Han){
    int d = 9;    
    for(int i = 0 ; i < 4 ; i++){
        int num1 = numMat1[0][i];
        for(int j = 0 ; j < 4 ; j++){
            int num2 = numMat1[1][j];
            for(int k = 0; k < 4 ; k++){
                int num3 = numMat1[2][k];
                for (int l = 0 ; l < 4 ; l++){
                    int num4 = numMat1[3][l];
                    for(int m = 0 ; m < 4 ; m++){
                        int num5 = numMat1[4][m];
                        ClauseSet *pS;
                        pS = new ClauseSet;
                        pS->next = Han->next;
                        pS->head = new Clauses;
                        Clauses *pC = new Clauses;
                        Clauses *preC;
                        Clauses * phead = pS->head;
                        phead->next = pC;
                        phead->value = 0;
                        int db = RDiag[d] / 10;
                        for(int a = 0; a < cpr[d] ; a++){
                            int r = RDiag[d] / 10 + a;
                            int base;
                            if(r <= 5){
                                base = RDiag[d] + 10 * a;
                            }
                            else{
                                base = RDiag[d] + 10 * (5-db) + 9 * (r - 5);
                            }
                            pC->value = 10 * base + num1;
                            pC->next = new Clauses;
                            pC = pC->next;
                            pC->value = 10 * base + num2;
                            pC->next = new Clauses;
                            pC = pC->next;
                            pC->value = 10 * base + num3;
                            pC->next = new Clauses;
                            pC = pC->next;
                            pC->value = 10 * base + num4;
                            pC->next = new Clauses;
                            pC = pC->next;
                            pC->value = 10 * base + num5;
                            preC = pC;
                            pC->next = new Clauses;
                            pC = pC->next;
                            phead->value += 5;
                        }
                        preC->next = NULL;
                        delete pC;
                        Han->next = pS;
                        ClauseNum++;
                    }
                }
            }
        }
    }
}
// 问题：！！从1开始的符合此规则 但从2-5开始的不符合


bool DPLLUpdation(ClauseSet_h *Sh,int n,int ist,State bak1[],int bak2[]){
    //找单子句
    ClauseSet_h *pS = Sh->next , *preS = Sh;
    Clauses_h *pC, *preC;
    while(pS){
        pC = pS->head;
        if(pC->l->value == 1 && pC->state != Mid){
            //单子句传播
            tag = pC->next->l->value;
            // booleans[abs(tag)] = 0;
            // if(pS->next == NULL) preS->next = NULL;
            // else preS->next = pS->next;
            // delete pS->head->next;
            // delete pS->head;
            // delete pS;
            if(tag > 0) ans[tag] = 1;
            else ans[-tag] = -1;
            if(!SVS(Sh,tag)) {
                if(ist != 0){
                    Recover(Sh,ist,bak1,bak2);
                }
                return false;//SingleValueSpread
            }
            while(!SingleValueStack.isEmpty()){
                int v;
                SingleValueStack.pop(v);
                if(v > 0) ans[v] = 1;
                else ans[-v] = -1;
                if(!SVS(Sh,v)) {
                    if(ist != 0) Recover(Sh,ist,bak1,bak2);
                    return false;
                    }
            }
            preS = Sh;
            pS = Sh->next;//进行删除
        }
        else{
            preS = pS;
            pS = pS->next;
        }
    }
    for(pS = Sh->next ; pS; pS = pS->next){
        if(pS->head->state == Mid) continue;
        else break;
    }
    if(pS == NULL) return true;
    //可以改变分裂策略
    
    int v;
    pS = Sh->next;
    while(pS->head->state == Mid) pS = pS->next;
    v = pS->head->next->l->value;
    ClauseSet_h *pp = new ClauseSet_h;
    Clauses_h *ppc;
    pp->head = new Clauses_h;
    ppc = pp->head;
    ppc->l = new Literal;
    ppc->l->value = 1;
    ppc->next = new Clauses_h;
    ppc = ppc->next;
    ppc->next = NULL;
    ppc->l = new Literal;
    ppc->l->value = v;
    pp->next = Sh->next;
    Sh->next = pp;

    //备份
    State bakstate[100000];
    int bakint[100000];
    int count = 1;
    for(ClauseSet_h *p = Sh->next ; p ; p = p->next){
        bakstate[count] = p->head->state;
        bakint[count++] = p->head->l->value;
    }

    // if(stack.push(v)){
    //     cout << "Stack Overflow" << endl;
    //     exit(EXIT_SUCCESS);
    // }
    if(v > 0){
        Sh->next->head->next->l->numnext = posSet[v];
        Sh->next->head->next->l->antinumnext = posClause[v];
        posSet[v] = Sh->next;
        posClause[v] = Sh->next->head->next;
        positives[v] = Sh->next->head->next->l;
    }
    else{
        Sh->next->head->next->l->numnext = negSet[-v];
        Sh->next->head->next->l->antinumnext = negClause[-v];
        negSet[-v] = Sh->next;
        negClause[-v] = Sh->next->head->next;
        negatives[-v] = Sh->next->head->next->l;
    }
    //用栈
    if(DPLLUpdation(Sh,n,v,bakstate,bakint)) {
        return true;
    }
    //回溯 需要回溯booleans
    else{
        Recover(Sh,ist,bak1,bak2);   
        Sh->next->head->next->l->value = -v;
    if(-v > 0){
        Sh->next->head->next->l->numnext = posSet[-v];
        negSet[-v] = negatives[-v]->numnext;
        negClause[-v] = negatives[-v]->antinumnext;
        Sh->next->head->next->l->antinumnext = posClause[-v];
        posSet[-v] = Sh->next;
        posClause[-v] = Sh->next->head->next;
        positives[-v] = Sh->next->head->next->l;
    }
    else{
        Sh->next->head->next->l->numnext = negSet[v];
        Sh->next->head->next->l->antinumnext = negClause[v];
        posSet[v] = positives[v]->numnext;
        posClause[v] = positives[v]->antinumnext;
        negSet[v] = Sh->next;
        negClause[v] = Sh->next->head->next;
        negatives[v] = Sh->next->head->next->l;
    }
        return(DPLLUpdation(Sh,n,-v,bakstate,bakint));
    }
}

bool SVS(ClauseSet_h *Sh, int tag){
    if(tag > 0){
        ClauseSet_h *pS = posSet[tag];
        Clauses_h *pC;
        if(pS == NULL) return true;
        pS->head->state = Mid;
        pS = positives[tag]->numnext;
        pC = positives[tag]->antinumnext;
        while(pS){
            pS->head->state = Mid;
            pS = pC->l->numnext;
            pC = pC->l->antinumnext;
        }
        pS = negSet[tag];
        if(pS == NULL) return true;
        RecoveryStack.push(tag);
        if(pS->head->state != Mid)
            if(pS->head->l->value == 1) {
                //recover
                return false;
            }
            else {pS->head->l->value--;}//用BAK恢复
        pC = negClause[tag];
        pC->state = Mid;
        pS = pC->l->numnext;
        pC = pC->l->antinumnext;
        while(pC && pS){
            if(pS->head->state == Mid){
                pC->state = Mid;
                pS = pC->l->numnext;
                pC = pC->l->antinumnext;
                continue;
            }
            if(pS->head->l->value == 1) {
                //recover
                return false;
            }
            pS->head->l->value--;
            pC->state = Mid;
            if(pS->head->l->value == 1 && pS->head->state != Mid){
                for(Clauses_h *p = pS->head->next ; p ; p = p->next){
                    if(tag != p->l->value && p->state != Mid) {
                        SingleValueStack.push(p->l->value);
                        break;
                    }
                }
            }
            pS = pC->l->numnext;
            
            pC = pC->l->antinumnext;
            
        }
    }
    else{
        ClauseSet_h *pS = negSet[-tag];
        Clauses_h *pC;
        if(pS == NULL) return true;
        pS->head->state = Mid;
        pS = negatives[-tag]->numnext;
        pC = negatives[-tag]->antinumnext;
        while(pS){
            pS->head->state = Mid;
            pS = pC->l->numnext;
            pC = pC->l->antinumnext;
        }
        pS = posSet[-tag];
        if(pS == NULL) return true;
        RecoveryStack.push(tag);
        if(pS->head->state != Mid)
            if(pS->head->l->value == 1) {
                //recover
                pS->head->l->value = 0;
                return false;
            }
            else pS->head->l->value--;//用BAK恢复
        pC = posClause[-tag];
        pC->state = Mid;
        pS = pC->l->numnext;
        pC = pC->l->antinumnext;
        
        while(pC && pS){
            if(pS->head->state == Mid){
                pC->state = Mid;
                pS = pC->l->numnext;
                pC = pC->l->antinumnext;
                continue;
            }
            if(pS->head->l->value == 1) {
                //recover
                pS->head->l->value = 0;
                return false;
            }
            pS->head->l->value--;
            pC->state = Mid;
            if(pS->head->l->value == 1 && pS->head->state != Mid){
                for(Clauses_h *p = pS->head->next ; p ; p = p->next){
                    if(tag != p->l->value && p->state != Mid) {
                        SingleValueStack.push(p->l->value);//这句可能有问题
                        break;
                        }
                }
            }
            pS = pC->l->numnext;
            pC = pC->l->antinumnext;
        }
    }
    return true;
}

//RecoveryStack: 用于恢复删除的反文字，将其State恢复为Exists,将其头部value++
//BAK：用于恢复删除的整个句子，将其头的State恢复为Exists
//需要有一个变量记录DPLLUpdation递归进去时新增的变量值，用于恢复到此后停止

void Recover(ClauseSet_h *Sh, int ist, State *bak1, int *bak2){
    int tag;
    while(RecoveryStack.pop(tag) && tag != ist){
        if(tag > 0){
            Clauses_h *pC;
            pC = negClause[tag];
            pC->state = Exist;
            pC = pC->l->antinumnext;
            while(pC){
                pC->state = Exist;
                pC = pC->l->antinumnext;
            }
        }
        else{
            Clauses_h *pC;
            pC = posClause[-tag];
            pC->state = Exist;
            pC = pC->l->antinumnext;
            while(pC){
                pC->state = Exist;
                pC = pC->l->antinumnext;
            }
        }
    }
    if(tag > 0){
            Clauses_h *pC;
            pC = negClause[tag];
            pC->state = Exist;
            pC = pC->l->antinumnext;
            while(pC){
                pC->state = Exist;
                pC = pC->l->antinumnext;
            }
        }
    else{
        Clauses_h *pC;
        pC = posClause[-tag];
        pC->state = Exist;
        pC = pC->l->antinumnext;
        while(pC){
            pC->state = Exist;
            pC = pC->l->antinumnext;
        }
    }
    ClauseSet_h *pS = Sh->next;
    int count = 1;
    while(pS){
        pS->head->state = bak1[count];
        pS->head->l->value = bak2[count++];
        pS = pS->next;
    }
}