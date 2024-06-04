/*
后缀数组+二分答案.
太难 压根不会
*/
#include<iostream>
#include<cstring>
#include<cstdio>
#define MAXN 110000
using namespace std;
int n,K,m=231,total,ans,belong[MAXN],pos[MAXN],p,tot,tmp[MAXN],sa[MAXN],rank1[MAXN],c[MAXN],ht[MAXN],t1[MAXN],t2[MAXN],s[MAXN];
char ch[MAXN];
bool vis[MAXN],f[MAXN];
bool cmp(int *y,int a,int b,int k)
{
    int a1=y[a],b1=y[b];
    int a2=a+k>=n?-1:y[a+k];
    int b2=b+k>=n?-1:y[b+k];
    return a1==b1&&a2==b2;
}
void slovesa()
{
    int *x=t1,*y=t2;
    for(int i=0;i<m;i++) c[i]=0;
    for(int i=0;i<n;i++) c[x[i]=s[i]]++;
    for(int i=1;i<m;i++) c[i]+=c[i-1];
    for(int i=n-1;i>=0;i--) sa[--c[x[i]]]=i;
    for(int k=1,p=0;k<=n;k<<=1,m=p,p=0)
    {
        for(int i=n-k;i<n;i++) y[p++]=i;
        for(int i=0;i<n;i++) if(sa[i]>=k) y[p++]=sa[i]-k;
        for(int i=0;i<m;i++) c[i]=0;
        for(int i=0;i<n;i++) c[x[y[i]]]++;
        for(int i=1;i<m;i++) c[i]+=c[i-1];
        for(int i=n-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];
        swap(x,y),p=1,x[sa[0]]=0;
        for(int i=1;i<n;i++)
        {
            if(cmp(y,sa[i-1],sa[i],k)) x[sa[i]]=p-1;
            else x[sa[i]]=p++;
        }
        if(p>=n) break;
    }
}
void sloveheight()
{
    int k=0;
    for(int i=0;i<n;i++) rank1[sa[i]]=i;
    for(int i=0;i<n;ht[rank1[i++]]=k)
    {
        int j=sa[rank1[i]-1];
        if(k) k--;
        while(j+k<n&&i+k<n&&s[i+k]==s[j+k]) k++;
    }
    ht[0]=0;
}
bool check(int x)
{
    bool ansflag=false;int tmpp=0,flag=0,ok=0;
    for(int i=1;i<n;i++)
    {
        if(ht[i]>=x)
        {
            vis[belong[sa[i-1]]]=true;
            vis[belong[sa[i]]]=true;
            if(f[sa[i]]) ok=sa[i];
        }
        else
        {
            for(int j=1;j<=tot;j++)
            {
                if(vis[j]) flag++;
                vis[j]=false;
            }
            if(flag>tot/2)
            {
                ansflag=true;
                if(ok) tmp[++tmpp]=ok;
            }
            flag=0;
        }
    }
    flag=0;
    for(int j=1;j<=tot;j++)
    {
        if(vis[j]) flag++;
        vis[j]=false;
    }
    if(flag>tot/2) 
    {
        ansflag=true;
        if(f[sa[n-1]]) tmp[++tmpp]=sa[n-1];
    }
    if(ansflag)
    {
        for(int i=1;i<=tmpp;i++) pos[i]=tmp[i];
        p=tmpp;return true;
    }
    return false;
}
void erfen(int l,int r)
{
    int mid;
    while(l<=r)
    {
        mid=(l+r)>>1;
        if(check(mid)) ans=mid,l=mid+1;
        else r=mid-1;
    }
}
void Clear()
{
    total=0,p=0,ans=0,m=231;
    memset(sa,0,sizeof sa);
}
void slove()
{
    if(!ans||!p) printf("?\n");
    else for(int i=1;i<=p;i++)
    {
        for(int j=pos[i];j<=pos[i]+ans-1;j++)
        printf("%c",char(s[j]));
        printf("\n");
    }
    printf("\n");
}
int main()
{
    while(scanf("%d",&tot))
    {
        if(!tot) break;Clear();
        for(int i=1;i<=tot;i++)
        {
            scanf("%s",ch);
            for(int j=0;j<strlen(ch);j++) s[total]=ch[j],belong[total]=i,f[total++]=true;
            if(i!=tot) s[total++]=130+i;
            //for(int j=strlen(ch)-1;j>=0;j--) s[total]=ch[j],belong[total]=i,f[total++]=false;
            //if(i!=tot) s[total++]=130+i;
        }
        s[total++]=0;n=total;
        slovesa(),sloveheight(),erfen(1,n/tot+1),slove();
    }
    return 0;
}