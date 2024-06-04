#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
#define maxn 100005
typedef long long ll;
string A, B;
int n, k, na, limit, rnk[maxn << 1], tmp[maxn << 1], sa[maxn << 1], lcp[maxn << 1];

bool cmp_sa(int i, int j)
{
    if (rnk[i] != rnk[j])
        return rnk[i] < rnk[j];
    int ri = i + k <= n ? rnk[i + k] : -1;
    int rj = j + k <= n ? rnk[j + k] : -1;
    return ri < rj;
}

void construct_sa(string &s, int *sa)
{
    for (int i = 0; i <= n; ++i)
    {
        sa[i] = i;
        rnk[i] = i < n ? s[i] : -1;
    }
    for (k = 1; k < n; k <<= 1)
    {
        sort(sa, sa + n + 1, cmp_sa);
        tmp[sa[0]] = 0;
        for (int i = 1; i <= n; ++i)
            tmp[sa[i]] = tmp[sa[i - 1]] + (cmp_sa(sa[i - 1], sa[i]) ? 1 : 0);
        memcpy(rnk, tmp, sizeof(int) * (n + 1));
    }
}

void construct_lcp(string &s, int *sa, int *lcp)
{
    for (int i = 0; i <= n; ++i)
        rnk[sa[i]] = i;
    int h = 0;
    for (int i = 0; i < n; ++i)
    {
        int j = sa[rnk[i] - 1];
        if (h > 0)
            --h;
        for (; i + h < n && j + h < n; ++h)
            if (s[i + h] != s[j + h])
                break;
        lcp[rnk[i] - 1] = h;
    }
}

struct node
{
    int sz[2], h;
} st[maxn << 1];

ll solve()
{
    ll res = 0, cnt[2];
    int top;
    for (int i = 0; i < n; ++i)
    {
        if (lcp[i] < limit)
            top = 0, cnt[0] = cnt[1] = 0;
        else
        {
            int id = sa[i] < na, sz[2] = {0}, h = lcp[i] - limit + 1;
            ++sz[id];
            while (top > 0 && h <= st[top - 1].h)
            {
                --top;
                for (int j = 0; j < 2; ++j)
                {
                    cnt[j] -= (ll)st[top].sz[j] * st[top].h;
                    sz[j] += st[top].sz[j];
                }
            }
            st[top].sz[0] = sz[0], st[top].sz[1] = sz[1], st[top].h = h;
            ++top;
            for (int j = 0; j < 2; ++j)
                cnt[j] += (ll)sz[j] * h;
            int id2 = sa[i + 1] < na;
            res += cnt[id2 ^ 1];
        }
    }
    return res;
}

int main()
{
    while (cin >> limit && limit)
    {
        cin >> A >> B;
        na = A.length();
        A += '$' + B;
        n = A.length();
        construct_sa(A, sa);
        construct_lcp(A, sa, lcp);
        cout << solve() << endl;
    }
    return 0;
}
