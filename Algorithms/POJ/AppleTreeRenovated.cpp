#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
using namespace std;
 
const int maxn=100010;
//存储边:
struct Edge{
    int next;
    int from;
    int to;
}edge[maxn];
int head[maxn];
int cur,cnt;//cur-用于存储边，cnt-用于转变为线性结构
int n,m;
//记录线性结构+记录子树：
struct Apple{
    int left;
    int right;//apple[x].right实际上是结点x从树结构转变为线性结构的一个映射
}apple[maxn];
 
//树状数组存储结构：
int sum[maxn];//前缀和，sum[x,y]=sum[y]-sum[x-1];
int a[maxn];//结点的权值
 
void Ini(){
    cur=0;
    cnt=1;
    memset(head,-1,sizeof(head[0])*(n+1));
    memset(sum,0,sizeof(sum[0])*(n+1));
    memset(apple,0,sizeof(apple[0])*(n+1));
}
void Add(int from,int to){
    edge[cur].next=head[from];
    edge[cur].from=from;
    edge[cur].to=to;
    head[from]=cur++;
}
void Dfs(int u){
    apple[u].left=cnt;
    for(int i=head[u];i!=-1;i=edge[i].next){
        Dfs(edge[i].to);
    }
    apple[u].right=cnt++;
}
int lowbit(int x){
    return x&(-x);//x的二进制表示中，从最右边数第一个不为0的位数，返回2^x
}
void Change(int x,int value){
    for(int i=x;i<cnt;i+=lowbit(i)){
        sum[i]+=value;
    }
}
int Sum(int x){
    int res=0;
    for(int i=x;i>0;i-=lowbit(i)){
        res+=sum[i];
    }
    return res;
}
void Build(int value){
    for(int i=1;i<=n;i++){
        a[i]=1;
        Change(i,1);
    }
}
int main()
{
    int num1,num2;
    char str[3];
    while(~scanf("%d",&n)){
        Ini();
        for(int i=1;i<n;i++){
            scanf("%d%d",&num1,&num2);
            Add(num1,num2);
        }
        Dfs(1);
        Build(1);
        scanf("%d",&m);
        for(int i=1;i<=m;i++){
            scanf("%s%d",str,&num1);
            if(str[0]=='Q'){
                cout<<Sum(apple[num1].right)-Sum(apple[num1].left-1)<<endl;
            }
            else if(str[0]=='C'){
                if(1==a[apple[num1].right]){
                    a[apple[num1].right]=0;
                    Change(apple[num1].right,-1);
                }
                else if(0==a[apple[num1].right]){
                    a[apple[num1].right]=1;
                    Change(apple[num1].right,1);
                }
            }
        }
    }
    return 0;
}