/*
    Programmer : Alexandru Olteanu
    Problem : https://www.pbinfo.ro/probleme/4475/livada3
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// GCC Optimizations
// #pragma GCC optimize("Ofast")
// #pragma GCC target("fma,sse,sse2,sse3,ssse3,sse4,popcnt")
// #pragma GCC target("abm,mmx,avx,avx2,tune=native")
// #pragma GCC optimize(3)
// #pragma GCC optimize("inline")
// #pragma GCC optimize("-fgcse")
// #pragma GCC optimize("-fgcse-lm")
// #pragma GCC optimize("-fipa-sra")
// #pragma GCC optimize("-ftree-pre")
// #pragma GCC optimize("-ftree-vrp")
// #pragma GCC optimize("-fpeephole2")
// #pragma GCC optimize("-ffast-math")
// #pragma GCC optimize("-fsched-spec")
// #pragma GCC optimize("unroll-loops")
// Useful
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
#define FastEverything  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define HighPrecision cout<<fixed<<setprecision(17);
typedef long long ll;
typedef pair<int,int> pii;
ll const mod=1000000007LL;
ll const mod2 = 100000000LL;
ll const md=998244353LL;
ll mypowr(ll a,ll b, ll mod1) {ll res=1;if(b<0)b=0;a%=mod1; assert(b>=0);
for(;b;b>>=1){if(b&1)res=res*a%mod1;a=a*a%mod1;}return res;}
ll mypow(ll a,ll b) {ll res=1;if(b<0)b=0;assert(b>=0);
for(;b;b>>=1){if(b&1)res=res*a;a=a*a;}return res;}
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(), x.rend()

ifstream in("livada.in");
ofstream out("livada.out");
#define cin in
#define cout out

const ll infll = 9e18;
const int inf = 2e9;
const ll maxn = 5e2 + 5;

int a[maxn][maxn];
int sum[50][maxn][maxn];

vector<pii> p;
struct cord {
    int x1, y1, h, l;
} f;

bool check(int x1, int y1, int x2, int y2) {
    if (x1 < 1 || y1 < 1) return 0;
    int x = -1;
    for (int i = 1; i <= 26; ++i) {
        int cur = sum[i][x2][y2] - sum[i][x2][y1 - 1] - sum[i][x1 - 1][y2] + sum[i][x1 - 1][y1 - 1];
        if (cur == 0) continue;
        if (x == -1) x = cur;
        if (cur != x) return false;
    }
    int h = x2 - x1 + 1;
    int l = y2 - y1 + 1;
    if (x1 < f.x1) {
        f = {x1, y1, h, l};
    }
    else if (x1 == f.x1) {
        if (y1 < f.y1) {
            f = {x1, y1, h, l};
        }
        else if (y1 == f.y1) {
            if (h < f.h) {
                f = {x1, y1, h, l};
            }
        }
    }
    return true;
}

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin>>test;
    for (int tt = 1; tt <= test; ++tt) {

        int n, m, s;
        cin >> n >> m >> s;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                char c;
                cin >> c;
                a[i][j] = c - 'A' + 1;
                for (int t = 1; t <= 26; ++t) {
                    sum[t][i][j] = sum[t][i][j - 1] + sum[t][i - 1][j] - sum[t][i - 1][j - 1];
                    sum[t][i][j] += a[i][j] == t;
                }
            }
        }

        for (int i = 1; i * i <= s; ++i) {
            if (s % i == 0) {
                p.pb({i, s / i});
            }
        }
        f = {inf, inf, inf, inf};
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                for (auto u : p) {
                    ans += check(i - u.fi + 1, j - u.se + 1, i, j);
                    if (u.fi != u.se) {
                        ans += check(i - u.se + 1, j - u.fi + 1, i, j);
                    }
                }
            }
        }

        if (ans != 0) {
            cout << f.x1 << " " << f.y1 << " " << f.h << " " << f.l << '\n';
        }

        cout << ans << '\n';

        
    }

    return 0;
}
