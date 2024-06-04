//booleans为文字计数器，labels为标签计数器
//子句用链表
#include <cmath>
#include <algorithm>
typedef struct literal Literal;
typedef struct clauses_h Clauses_h;
typedef struct clauseSet_h ClauseSet_h;

typedef enum{Exist,Mid}State;
Literal **positives;//建立每个文字的头指针数组
Literal **negatives;


ClauseSet_h **posSet;
ClauseSet_h **negSet;

Clauses_h ** posClause;
Clauses_h ** negClause;

typedef struct clauses{
    int value;
    struct clauses *next;
}Clauses;



typedef struct clauseSet{
    Clauses *head;
    struct clauseSet *next;
}ClauseSet;

struct literal{
    int value;
    ClauseSet_h * numnext; // For Same number and anti number(--)
    Clauses_h * antinumnext; // For deletion
};


typedef struct clauses_h{
    Literal * l;
    State state;
    struct clauses_h *next;
}Clauses_h;


struct clauseSet_h{
    Clauses_h *head;
    struct clauseSet_h *next;
};


// typedef struct KV{
//     int index;
//     int value;
// }KV;



bool DPLL(ClauseSet *S); //DPLL整体框架算法
bool DPLLUpdation(ClauseSet_h *Sh,int n,int ist = 0,State *bak1 = NULL,int *bak2 = NULL);//优化后的DPLL算法（未实现）
bool DPLLHaniddoku(ClauseSet *S);//蜂窝数独DPLL算法
void Copy(ClauseSet *S, ClauseSet *TempS);//回溯用的复制整句函数
void Recover(ClauseSet_h *Sh, int ist,State *bak1,int *bak2);//优化用的回溯函数（未实现）
// void deletion(ClauseSet *S); //删除子句 被优化掉了
bool SVS(ClauseSet *S, int tag); //单子句传播
bool SVS(ClauseSet_h *Sh, int tag); //优化后的单子句传播（未实现）

void PrintHaniddoku(int Hani[61]); //打印数独
ClauseSet *Encoding(int Hani[61]); //数独编码
void AddCellConstriant(ClauseSet *Han); //添加单元格约束
void AddRowConstriant(ClauseSet *Han); //添加行约束
void AddLDiagConstriant(ClauseSet *Han); //添加左下右上斜线约束
void AddRDiagConstriant(ClauseSet *Han); //添加右下左上斜线约束
ClauseSet * Add_must_fill(int r,int num); //重载行必填
ClauseSet * Add_must_fill(int r,int num,int flag); //重载对角线必填

//三元表示变元
//方向 ：行线， 左下右上斜线，右下左上斜线
//必含5 : 155V265V375V485V595
//5种选填方案 (1234)(2346)(3467)(4678)(6789) 转化为CNF (4^5)个子句

class Stack{
    public:
        Stack(int size){
            this->size = size;
            this->top = -1;
            this->data = new int[size];
        }
        ~Stack(){
            delete []data;
        }
        bool push(int x){
            if(top == size - 1) return false;
            else data[++top] = x;
        }
        bool pop(int &x){
            if(top == -1) return false;
            x = data[top--];
            return true;
        }
        
        bool isEmpty(){
            return top == -1;
        }

        bool isFull(){
            return top == size - 1;
        }
        bool notinStack(int x){
            for(int i = 0; i < top; i++){
                if(data[i] == x) return false;
            }
            return true;
        }
    private:
            int size;
            int top;
            int *data;
};
class Stack_C{
    public:
        Stack_C(int size){
            this->size = size;
            this->top = -1;
            this->data = new ClauseSet *[size];
        }
        ~Stack_C(){
            delete[] data;
        }
        bool push(ClauseSet *pS){
            if(top == size - 1) return false;
            else data[top++] = pS;
        }
        bool pop(ClauseSet *pS){
            if(top == -1) return false;
            pS = data[top--];
            return true;
        }
        
        bool isEmpty(){
            return top == -1;
        }

        bool isFull(){
            return top == size - 1;
        }
    private:
        int size;
        int top;
        ClauseSet **data;
};
void Transition(int Hani[61],Stack stack);
typedef void (* Add_choose)(ClauseSet *S);

void Add_choose_row1(ClauseSet *S);
void Add_choose_row2(ClauseSet *S);
void Add_choose_row3(ClauseSet *S);
void Add_choose_row4(ClauseSet *S);
void Add_choose_row5(ClauseSet *S);
void Add_choose_row6(ClauseSet *S);
void Add_choose_row7(ClauseSet *S);
void Add_choose_row8(ClauseSet *S);
void Add_choose_row9(ClauseSet *S);
void Add_choose_ldiag1(ClauseSet *S);
void Add_choose_ldiag2(ClauseSet *S);
void Add_choose_ldiag3(ClauseSet *S);
void Add_choose_ldiag4(ClauseSet *S);
void Add_choose_ldiag5(ClauseSet *S);
void Add_choose_ldiag6(ClauseSet *S);
void Add_choose_ldiag7(ClauseSet *S);
void Add_choose_ldiag8(ClauseSet *S);
void Add_choose_ldiag9(ClauseSet *S);
void Add_choose_rdiag1(ClauseSet *S);
void Add_choose_rdiag2(ClauseSet *S);
void Add_choose_rdiag3(ClauseSet *S);
void Add_choose_rdiag4(ClauseSet *S);
void Add_choose_rdiag5(ClauseSet *S);
void Add_choose_rdiag6(ClauseSet *S);
void Add_choose_rdiag7(ClauseSet *S);
void Add_choose_rdiag8(ClauseSet *S);
void Add_choose_rdiag9(ClauseSet *S);


Add_choose ch_row[10] = {
    NULL,
    Add_choose_row1,
    Add_choose_row2,
    Add_choose_row3,
    Add_choose_row4,
    Add_choose_row5,
    Add_choose_row6,
    Add_choose_row7,
    Add_choose_row8,
    Add_choose_row9
};
Add_choose ch_ldiag[10] = {
    NULL,
    Add_choose_ldiag1,
    Add_choose_ldiag2,
    Add_choose_ldiag3,
    Add_choose_ldiag4,
    Add_choose_ldiag5,
    Add_choose_ldiag6,
    Add_choose_ldiag7,
    Add_choose_ldiag8,
    Add_choose_ldiag9
};
Add_choose ch_rdiag[10] = {
    NULL,
    Add_choose_rdiag1,
    Add_choose_rdiag2,
    Add_choose_rdiag3,
    Add_choose_rdiag4,
    Add_choose_rdiag5,
    Add_choose_rdiag6,
    Add_choose_rdiag7,
    Add_choose_rdiag8,
    Add_choose_rdiag9
};



// 文字线索
// 分支策略
// 变元
// 用栈存储扫描时的单子句 在SVS中将新的单子句存入栈中