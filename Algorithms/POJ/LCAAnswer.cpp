// Tarjan离线算法求LCA
#include<stdio.h>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int maxn = 1000;
int ask[maxn][maxn];// ask[i][j]表示询问中有i和j的公共祖先 用询问次数初始化
int ans[maxn];//保存祖先i出现过的次数
int n,m;
vector<int> g[maxn];//保存儿子
int root;//树的根
bool visit[maxn];
bool isroot[maxn]; // 从输入获得根节点
int father[maxn];
int Find(int x)
{
    if(father[x] == x) return x;
    else return father[x] = Find(father[x]);
}
/*void dfs(int u){
	for (int i = 1 ; i<=n ; i++){
		if(visit[i]&&ask[u][i]){ // 遍历整个数组
			LCA[u][i] = Find(i); // 在访问过i的前提下，LCA(u,i)是Find(i) 
		}
	}
	visit[u] = true;
	for(int i = 1 ; i <= g[u].size() ; i++){
		int son = g[u][i];
		dfs(son);
		father[son] = u;
	}
}*/
// 根据dfs的性质，当当前结点的子树还未访问完全时， father[u] = u 不变
// 而求LCA 1. v是u的子树中的结点 则当dfs(u的子树)的时候 访问到v 发现u已经被访问过了，此时LCA(v,u) = Find(u) = u
// 2. u和v无父子关系 则当访问到v时，Find(u)找的是u的已经被访问的最高层祖先的父节点，即还未访问完全的某个结点，又因为v是正在访问的结点
// 即当前结点v是还未访问完全的某个结点的子树中的结点，所以LCA(u,v) = Find(u) = father[u]
void init()
{
    memset(ans,0,sizeof(ans));
    memset(visit,false,sizeof(visit));
    memset(isroot,true,sizeof(isroot));
    memset(ask,0,sizeof(ask));
    for(int i = 1; i <= n; i++)
    {
        g[i].clear();
        father[i] = i;
    }
}// 用并查集，初始化时每个点的父亲都是自己
void LCA(int root)
{
    for(int i = 1; i <= n; i++)
    {
        if(visit[i]&&ask[root][i])
        {
            ans[Find(i)] += ask[root][i]; // 因为题目需求是当前节点作为祖先结点出现的次数，所以直接对ans[Find(i)]
        }
    }
    visit[root] = true;
    for(int i = 0; i < g[root].size(); i++)
    {
        int term = g[root][i]; // 遍历root的儿子
        LCA(term);
        father[term] = root;
    }
}// dfs 变体
int main()
{
    while(~scanf("%d",&n))
    {
        init();
        int f,s,num;
        for(int i = 1; i <= n; i++)
        {
            scanf("%d:(%d)",&f,&num);
            for(int j = 1; j <= num; j++)
            {
                scanf(" %d",&s);
                isroot[s] = false; // 从输入中获得唯一一个不是儿子的结点
                g[f].push_back(s); // 获得s的儿子结点
            }
        }
        for(int i = 1; i <= n; i++)
        {
            if(isroot[i])
            {
                root = i;
                break;
            }
        }
        scanf("%d",&m);
        int u,v;
        for(int i = 1; i <= m; i++)
        {
            scanf(" (%d %d)",&u,&v);
            ask[u][v]++;
            ask[v][u]++; // 对称
        }
        LCA(root);
        for(int i = 1; i <= n; i++)
        {
            if(ans[i])
            {
                printf("%d:%d\n",i,ans[i]);
            }
        }
    }
    return 0;
}

