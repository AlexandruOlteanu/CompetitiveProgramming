/*
    Programmer : Alexandru Olteanu
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// GCC Optimizations
// #pragma GCC optimize("Ofast");
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

// ifstream in("input.txt");
// ofstream out("output.txt");
// #define cin in
// #define cout out

const ll infll = 9e18;
const int inf = 2e9;
const ll maxn = 3e5 + 5;

int is[maxn];
vector<int> v[maxn];

bool ok = true;
int par = 0, imp = 0;

void dfs(int x, int val) {
    if (!ok) return;
    is[x] = val;
    if (val < 0) ++par;
    else ++imp;
    for (auto u : v[x]) {
        if (is[u] == val) {
            ok = false;
            return;
        }
        if (is[u] == -val) continue;
        dfs(u, -val);
    }
}

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    cin>>test;
    for (int tt = 1; tt <= test; ++tt) {

        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) {
            is[i] = 0;
            v[i].clear();
        }
        ok = true;
        for (int i = 1; i <= m; ++i) {
            int x, y;
            cin >> x >> y;
            v[x].pb(y);
            v[y].pb(x);
        }

        ll ans = 1;
        for (int i = 1; i <= n; ++i) {
            if (is[i] == 0) {
                dfs(i, 1);
                ans *= mypowr(2, par, md) + mypowr(2, imp, md);
                ans %= md;
                par = imp = 0;
            }
        }
        if (!ok) {
            cout << "0\n";
            continue;
        }
        cout << ans << '\n';

        
    }

    return 0;
} 
