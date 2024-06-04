#include <iostream>
#include <vector>
# define MAXN 40005
# define MAXLOGN 16

using namespace std;

// 本题用RMQ求
// 用图表示农场
struct edge{
    int to;
    int weight;
    edge(int to,int weight):to(to),weight(weight){}
};

vector<edge> G[MAXN];
int visitorder[2*MAXN-1]; // Euler Tour
int Level[2*MAXN-1]; // Euler Tour中每个点的深度
int First[MAXN];
int Dist[MAXN];

// SparseTable
int st[2*MAXN-1][MAXLOGN];

void init_st(int n){
    for(int i = 0 ; i < n ; i++){
        st[i][0] = i;
    } 
    for(int j = 1 ; (1<<j) < n ; j++){
        for (int i = 0 ; i + (1<<j) - 1 < n ; i++){
            if(Level[st[i][j-1]] <= Level[st[i+(1<<(j-1))][j-1]]){
                st[i][j] = st[i][j-1];
            }
            else{
                st[i][j] = st[i+(1<<(j-1))][j-1];
            }
        }
    }
}

void dfs(int v,int l,int fa,int &k){ // v 是当前访问结点， k 是 当前visit下标
    First[v] = k;
    visitorder[k] = v;
    Level[k++] = l; // 第一次访问当前访问结点处理
    for(int i = 0 ; i < G[v].size(); i++){
        if(G[v][i].to != fa){
            Dist[G[v][i].to] = Dist[v]+G[v][i].weight;
            dfs(G[v][i].to,l+1,v,k);
            visitorder[k] = v;
            Level[k++] = l;
        }
    }
}
void init(int n){
    int k = 0;
    dfs(0,0,-1,k);
    init_st(2*n-1);
}

int query(int l, int r){
    int k = 0;
    while(r-l+1 > (1<<(k+1))) k++; // k = [log(r-l+1)] -> 2^(k+1) > r-l+1
    if(Level[st[l][k]] <= Level[st[r-(1<<k)][k]]) return st[l][k];
    else return st[r - (1 << k)][k];
}


int lca(int u, int v){
    return visitorder[query(min(First[u],First[v]),max(First[u],First[v])+1)];
}

void add_edge(int from,int to , int weight){
    G[from].push_back(edge(to, weight));
}

int main(){
    int N,M;
    while(~scanf("%d %d",&N,&M)){
        int u,v,w;
        char D;
        for(int i = 0 ; i < M ; i++){
            scanf("%d %d %d %c",&u,&v,&w,&D);
            u--;
            v--;
            add_edge(u,v,w);
            add_edge(v,u,w);
        }
        init(N);
        int K;
        scanf("%d",&K);
        for (int i = 0; i < K; ++i)
        {
            int a, b;
            scanf("%d%d", &a, &b);
            a--;
            b--;
            int t = lca(a, b);
            int ans = Dist[a] - Dist[t] + Dist[b] - Dist[t];
            printf("%d\n", ans);
        }
    }
}