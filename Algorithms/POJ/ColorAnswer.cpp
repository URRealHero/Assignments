#include <iostream>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <stdlib.h>

using namespace std;
#define MAX 100000
int cover[MAX*4+5];
int n;
int t;
int m;
char a;
int x,y,z;
int tag[31];
void PushDown(int node)
{
    if(cover[node]!=-1)
    {
        cover[node<<1|1]=cover[node];
        cover[node<<1]=cover[node];
        cover[node]=-1;
    }
}
void Update(int node,int begin,int end,int left,int right,int num)
{
    if(left<=begin&&end<=right)
    {
        cover[node]=num;
        return;
    }
    PushDown(node);
    int m=(begin+end)>>1;
    if(left<=m)
        Update(node<<1,begin,m,left,right,num);
    if(right>m)
        Update(node<<1|1,m+1,end,left,right,num);
}
void Query(int node,int begin,int end,int left,int right,int &ans)
{
    if(cover[node]!=-1)
    {
        if(!tag[cover[node]])
        {
             ans++;
             tag[cover[node]]=1;
        }
        return;
    }
    PushDown(node);
    if(begin==end)
        return;
    int m=(begin+end)>>1;
    if(left<=m)
       Query(node<<1,begin,m,left,right,ans);
    if(right>m)
        Query(node<<1|1,m+1,end,left,right,ans);
}
int main()
{


    while(scanf("%d%d%d",&n,&t,&m)!=EOF)
    {
        memset(cover,0,sizeof(cover));
    for(int i=1;i<=m;i++)
    { 
        getchar();
        scanf("%c",&a);
        if(a=='C')
        {
            scanf("%d%d%d",&x,&y,&z);
            Update(1,1,n,x,y,z-1);
        }

        else
        {
            memset(tag,0,sizeof(tag));
            scanf("%d%d",&x,&y);
            int ans=0;
            Query(1,1,n,x,y,ans);
            printf("%d\n",ans);
        }

    }
    }
    return 0;
}