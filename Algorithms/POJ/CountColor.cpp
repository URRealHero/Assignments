#include <iostream>
#include <cstring>
#include <vector>

#define MAXN 200005
#define MAXT 35
#define MAXO 100005
using namespace std;

struct Color{
    int colors[MAXT];
    int colornum;
    int colorId[MAXT];
};
vector<Color>ST(MAXN);


void Coloring(int node,int b,int e , int T,int i, int j);


void Coloring(int node,int b,int e , int T,int i, int j){
    if(b>j || e < i) return;
    if(b<=i && e >= j) {
        for(int i = 1; i <= ST[node].colornum ; i++){
            ST[node].colors[ST[node].colorId[i]] = 0;
        }
        ST[node].colornum = 1;
        ST[node].colors[T] = 1;
        ST[node].colorId[1] = T;
        if(b==e) return;
        Coloring(2*node,b,e,T,i,(i+j)>>1);
        Coloring(2*node+1,b,e,T,((i+j)>>1)+1,j);
        return;
    }
    Coloring(2*node,b,e,T,i,(i+j)>>1);
    Coloring(2*node+1,b,e,T,((i+j)>>1)+1,j);
    ST[node].colornum = ST[2*node].colornum+ST[2*node+1].colornum;
    int res1 = ST[2*node].colornum;
    for(int k = 1 ; k <= res1 ; k++){
        ST[node].colors[ST[2*node].colorId[k]] = 1;
        ST[node].colorId[k] = ST[2*node].colorId[k];
    }
    int res2 = ST[2*node+1].colornum;
    for(int k = 1 ; k <= res2 ; k++){
        if(ST[node].colors[ST[2*node+1].colorId[k]] == 1) ST[node].colornum--; // C 4 4 4 出现--
        else{
            ST[node].colors[ST[2*node+1].colorId[k]] = 1;
            ST[node].colorId[k+res1] = ST[2*node+1].colorId[k];
        }
    }
    
}

int query(int node,int b,int e,int i,int j){
    if(b>j || e < i) return 0;
    if(b<=i && e >= j) return ST[node].colornum;
    return query(2*node,b,e,i,(i+j)>>1) + query(2*node+1,b,e,((i+j)>>1)+1,j);
}

int main(){
    int L,T,O;
    scanf("%d %d %d",&L,&T,&O);
    getchar();
    for(int i = 0 ; i < O ; i++){
        char ch;
        ch = getchar();
        if (ch == 'C') {
            int b,e,t;
            scanf("%d %d %d",&b,&e,&t);
            Coloring(1,b,e,t,1,L);
        }
        else if (ch == 'P') {
            int b,e;
            scanf("%d %d",&b,&e);
            cout << query(1,b,e,1,L) << endl;
        }
        getchar();
    }
    return 0;
}