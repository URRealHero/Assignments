#include <iostream>
using namespace std;
struct Branch;
typedef struct Branch Branch;

struct Branch{
    int childs[10];// 可能更多
    int parent;
    int Apple;
    int totalApple;
    int childNum;
    static Branch AppleTree[100000];
    Branch(){parent=-1;Apple=1;totalApple=(-1);childNum=0; };
    int getApple();
    void changeApple();
    void Update();
    void AddBranch(int branch,int child);
};

Branch Branch::AppleTree[100000];

int Branch::getApple(){
    if(totalApple!= -1) return totalApple;
    int sum = Apple;
    for (int i = 0 ; i < childNum ; i++){
        sum += Branch::AppleTree[childs[i]].getApple();
    }
    totalApple = sum;
    return totalApple;
}

void Branch::changeApple(){
    if(totalApple == -1) getApple();
    totalApple = (Apple==0) ? totalApple+1 : totalApple-1;
    Apple = (Apple==0) ? 1 : 0;
    AppleTree[parent].Update();
}

void Branch::Update(){
    int sum = Apple;
    for (int i = 0 ; i < childNum ; i++){
        sum += Branch::AppleTree[childs[i]].getApple();
    }
    totalApple = sum;
    if(parent != -1) AppleTree[parent].Update();
}

void Branch::AddBranch(int branch,int child){
    childs[childNum] = child;
    AppleTree[child].parent = branch; 
    childNum++;
}

int main(){
    int N;
    scanf("%d", &N);
    for(int i = 1 ; i < N ; i++){
        int parent;
        int child;
        scanf("%d %d", &parent, &child);
        Branch::AppleTree[parent].AddBranch(parent,child);
    }
    int M;
    scanf("%d\n", &M);
    char command;
    for (int i = 0 ; i < M ; i++){
        scanf("%c", &command);
        if(command == 'Q'){
            int branch;
            scanf("%d", &branch);
            printf("%d\n", Branch::AppleTree[branch].getApple());
        }
        else if(command == 'C'){
            int branch;
            scanf("%d", &branch);
            Branch::AppleTree[branch].changeApple();
        }
        else{
            printf("Error\n");
        }
        getchar();
    }
    

    return 0;
}