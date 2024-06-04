#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
#define maxn 20005
#define lowbit(x) (x&(-x))
struct cow{
    ll v,x;
    bool operator < (const cow &a)const{
        return v < a.v || v == a.v && x < a.x;
    }
}a[maxn];

int t[maxn];
int id_num[maxn];// x 小于第 i 头牛的牛的数量
void add(int x,int d,int tree[]){
    for(int i = x ; i < maxn ; i += lowbit(i)){
        tree[i] += d;
    }
}// 更新树状数组当前枝干

ll sum(int x, int tree[]){
    int sum = 0;
    for (int i = x ; i > 0 ; i -= lowbit(i)){
        sum += tree[i];
    }
    return sum;
} // 求x之前的前缀和

int main(){
    int N;
    scanf("%d", &N);
    for(int i = 0 ; i < N ; i++){
        scanf("%lld %lld", &a[i].v, &a[i].x);
    }
    sort(a, a+N); // 按嗓门从小到大排序，若嗓门相同，按位置x从小到大排序 
    // 因此，在后续交流时 因为计算公式为 max(v[i],v[j]) * dist 所以任意一对牛产生的声音只需在遇到两者较大嗓门一方时计算
    memset(id_num, 0, sizeof(id_num));
    ll num, tot, ans=0;
    for(ll i = 0 ; i < N ; i++){
        num = sum(a[i].x, id_num);  // x 小于第 i 头牛的牛的数量
        tot = sum(a[i].x, t); // x 小于第 i 头牛的牛的位置的和
        ans += (num * a[i].x - tot) * a[i].v;
        //cout<<num<<" - "<<tot<<" + "<<ans<<endl;
        num = i - num; // x 大于第 i 头牛的牛的数量
        tot = sum(20000, t) - tot; // x 大于第 i 头牛的牛的位置的数量和
        ans += (tot - num * a[i].x) * a[i].v;
        //cout<<num<<" - "<<tot<<" - "<<ans<<endl;
        add(a[i].x, a[i].x, t); // 往树状数组t的第a[i].x个位置加上a[i].x
        add(a[i].x, 1, id_num); // 往树状数组id_num的第a[i].x个位置加上1 表示有一头牛的x值为a[i].x
    } // 每一次循环都更新了第i头牛对已经遍历过的牛的贡献 因为排序过v，所以i之前的牛不能对i交流，但i可以与i之前的牛进行交流
    cout << ans << endl;
    return 0;
}

