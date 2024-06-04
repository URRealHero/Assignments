// 回答yes就将二人连接
// 回答no,二人就不在一个集合中

#include <iostream>
using namespace std;
//引入库中的快速排序
#include <algorithm>
#include <cstring>

// 诚实的人p1个 撒谎的人p2个 给出N个问题 每个格式为 xi,yi,ai 对应xi回答yi是否为诚实的人(yes 为是 no 为否)
// 结果 按升序输出所有诚实的人的编号 若条件不够 输出no 在每个输出结束后输出end

// 若回答为yes 则 xi和yi是一类人， 回答为no, xi和yi异类
int dp[300][300];
int GetDevil[300];

class People{
    int *fa;
    int *rank;
public:
    People(int n):fa(new int[n+1]),rank(new int[n+1]){
        for(int i = 0; i <= n; i++){
            fa[i] = i;
            rank[i] = 1;
        }
    }
    ~People(){
        delete fa;
        delete rank;
        // cout << "Delete Success" << endl;
    }
    int find(int x);
    void join(int x, int y, int d);
    int getRank(int x){return rank[x];}
};

int People::find(int x){
    if(x == fa[x]) return x;
    else {
        int tmp = fa[x];
        fa[x] = find(fa[x]);
        rank[x] = (rank[x] + rank[tmp] + 1) % 2;
        return fa[x];
        }
}

void People::join(int x, int y, int d){
    int fx = this->find(x);
    int fy = this->find(y);
    if(fx == fy) return ;
    else{
        fa[fy] = fx;
        rank[fy] = (rank[x] + rank[y] + d) % 2;
    }
}

void init(){
    memset(dp,0,sizeof(dp));
    memset(GetDevil,0,sizeof(GetDevil));
} // dp GetDevil

int cmp(const void *a, const void *b){
    return *(int *)a - *(int *)b;
}

int main(){
    
    int n,p1,p2;
    while((scanf("%d %d %d",&n,&p1,&p2)==3)){
        if (n==0 && p1 == 0 && p2 == 0) break;
        init();
        int ind = 0;

        People p(p1+p2);
        for(int i = 0 ; i < n ; i++){
            int x,y;
        char ans[5];
        scanf("%d %d %s",&x,&y,ans);
        if(ans[0] == 'y') p.join(x,y,1);
        else p.join(x,y,0);
        }
        //这些集合使得有且仅有一种情况满足有p1个诚实的人和p2个撒谎的人
        int cnt = 0;
        int *set = new int[p1+p2+1];
        int (*C_set)[2] = new int[p1+p2+1][2];
        for(int i = 1 ; i<=p1+p1 ; i++){
            if(p.find(i) == i){
                set[++cnt] = i;
                for(int j = 1 ; j <= p1+p2 ; j++){
                    if(p.find(j) == i){
                        C_set[cnt][p.getRank(j)]++;
                    }
                }
            }
        }
        // 构造商品完成，下面进行背包问题
        dp[0][0] = 1;
        for(int i = 1; i <= cnt ; i++){
            for(int j = p1 ; j >= C_set[i][0] ; j--){
                dp[i][j] += dp[i-1][j-C_set[i][0]]; // 加异类
            }
            for(int k = p1; k >= C_set[i][1] ; k--){
                dp[i][k] += dp[i-1][k-C_set[i][1]]; // 加同类
            }
        }
        if(dp[cnt][p1] != 1){
            for(int i = 1 ; i <= p1+p2 ; i++){
                cout << "no" << endl;
            }
        }
        else{
            // 升序输出诚实的人的编号
            // cout << "Haven't done" << endl;
            // 回溯寻找dp[cnt][p1]的路径
            int Ret = p1;
            
            for (int i = cnt ; i >= 1 ; i--){
                if(dp[i-1][Ret-C_set[i][0]] == 1){
                    for(int j = 1 ; j <= p1+p2 ; j++){
                        if(p.find(j) == set[i] && p.getRank(j) == 0){
                            GetDevil[ind++] = j;
                        }
                    }
                    Ret -= C_set[i][0];
                }
                else{
                    for(int j = 1 ; j <= p1+p2 ; j++){
                        if(p.find(j) == set[i] && p.getRank(j) == 1){
                            GetDevil[ind++] = j;
                        }
                    }
                    Ret -= C_set[i][1]; 
            }
        }
        qsort(GetDevil,ind,sizeof(int),cmp);
        
        for(int i = 0 ; i < ind ; i++){
            cout << GetDevil[i] << endl;
        }
        }
        delete set;
        delete C_set;
    }

    cout << "end" << endl;
    return 0;
}

