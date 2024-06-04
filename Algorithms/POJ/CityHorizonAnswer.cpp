#include <algorithm>
#include <cstdio>
#include <cstring>

#define ll long long

const int N = 40005;

struct Node{
    ll x1, x2;  //起始  
    ll y2;  //高度
    ll sum;     //这一块矩形的净大小
} T[N];

ll n;

bool cmp(Node a, Node b){
    if (a.y2 != b.y2)
        return a.y2 < b.y2;
    else{
        if (a.x2 != b.x2)
            return a.x2 < b.x2;
        else
            return a.x1 > b.x1;
    }
}

void Cover(ll x1, ll y1, ll x2, ll y2, ll k, ll c){ // 当前矩形 横坐标，高度，所在下标c，遍历开始下标
    while (k < n && (x1 >= T[k].x2 || x2 <= T[k].x1))   //和上一块是否有重叠
        k++;
    if (k == n){
        T[c].sum += (x2 - x1) * (y2 - y1);  //比较完最后一块，直接算净面积
        return;
    }
    if (x1 < T[k].x1)
        Cover(x1, y1, T[k].x1, y2, k + 1, c); // 递归探索 x1到T[k].x1的部分，需先完成k+1的遍历
    if (x2 > T[k].x2)
        Cover(T[k].x2, y1, x2, y2, k + 1, c);
}

int main(){
    ll a, b, c;
    scanf("%lld", &n);
    for (ll i = 0; i < n; i++){
        scanf("%lld%lld%lld", &a, &b, &c);
        T[i].x1 = a;
        T[i].x2 = b;
        T[i].y2 = c;
        T[i].sum = 0;
    }
    std::sort(T, T + n, cmp);
    for (ll i = n - 1; i >= 0; i--)
        Cover(T[i].x1, 0, T[i].x2, T[i].y2, i + 1, i);
    ll ans = 0;
    for (ll i = 0; i < n; i++)
        ans += T[i].sum;
    printf("%lld\n", ans);
    return 0;
}