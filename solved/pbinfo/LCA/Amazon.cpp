/*
    Programmer : Alexandru Olteanu
    Problem : https://www.pbinfo.ro/probleme/4565/amazon
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
ll const mod = 666013;
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

ifstream in("amazon.in");
ofstream out("amazon.out");
#define cin in
#define cout out

const ll infll = 9e18;
const int inf = 2e9;
const ll maxn = 2e5 + 5;

/*
    Template created by Alexandru Olteanu (Source: Topcoder)

    How to use: 
        1. populate parrent, level
        2. Call lca.build()
        3. Call lca.query(a, b) whenever needed
*/
template<typename A>
struct LCA {

    vector<A> parrent;
    vector<A> level;
    vector<vector<A>> V;
    int n;
    LCA(int length){
        parrent.resize(length + 1);
        level.resize(length + 1);
        V.resize(length + 1);
        n = length;
        int logMax = 0;
        int p = 1;
        while (p <= n) ++logMax, p *= 2;
        for (int i = 1; i <= n; ++i) {
            V[i].resize(logMax + 1, -1);
        }
    }

    void buildLCA() {
        for (int i = 1; i <= n; ++i) {
            V[i][0] = parrent[i];
        }
        for (int j = 1; 1 << j <= n; j++) {
            for (int i = 1; i <= n; i++) {
                if (V[i][j - 1] != -1) {
                    V[i][j] = V[V[i][j - 1]][j - 1];
                }
            }
        }
    }

    int query(int a, int b) {
        int log, i;

        //if a is situated on a higher level than b then we swap them
        if (level[a] < level[b])
            swap(a, b);

        //we compute the value of [log(level[a)]
        for (log = 1; 1 << log <= level[a]; ++log);
        --log;

        //we find the ancestor of node a situated on the same level
        //with b using the values in V
        for (i = log; i >= 0; --i) {
            if (level[a] - (1 << i) >= level[b]) {
                a = V[a][i];
            }
        }

        if (a == b)
            return a;

        //we compute LCA(a, b) using the values in V
        for (i = log; i >= 0; --i) {
            if (V[a][i] != -1 && V[a][i] != V[b][i]) {
                a = V[a][i], b = V[b][i];
            }
        }

        return parrent[a];
    }
};

vector<pii> v[maxn];
int p[maxn], lvl[maxn];


void dfs(int x, int par, int l) {
    p[x] = par, lvl[x] = l;
    for (auto u : v[x]) {
        if (u.first == par) continue;
        dfs(u.first, x, l + 1);
    }
}

vector<pii> val;

void build_values(int x, int par) {
    for (auto u : v[x]) {
        if (u.first == par) continue;
        build_values(u.first, x);
        val.pb({p[u.first], u.second});
        p[x] += p[u.first];
    }
}


int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin>>test;
    for (int tt = 1; tt <= test; ++tt) {

        int n;
        cin >> n;
        for (int i = 1; i < n; ++i) {
            int x, y, w;
            cin >> x >> y >> w;
            ++x, ++y;
            v[x].pb({y, w});
            v[y].pb({x, w});
        }
        dfs(1, 1, 0);
        LCA<int> lca(n);
        for (int i = 1; i <= n; ++i) {
            lca.level[i] = lvl[i];
            lca.parrent[i] = p[i];
            p[i] = 0;
        }

        lca.buildLCA();

        int m, k;
        cin >> m >> k;
        for (int i = 1; i <= m; ++i) {
            int x, y;
            cin >> x >> y;
            ++x, ++y;
            int res = lca.query(x, y);
            if (res != x && res != y) {
                p[res] -= 2;
                ++p[x], ++p[y];
                continue;
            }
            if (res == x) {
                --p[res];
                ++p[y];
                continue;
            }
            --p[res];
            ++p[x];
        }

        build_values(1, 1);
        sort(rall(val));
        ll ans = 0;
        for (auto u : val) {
            if (k >= u.second) {
                k -= u.second;
                continue;
            }
            ll ap = u.first;
            ll cost = u.second - k;
            ans += ap * cost % mod;
            ans %= mod;
            k = 0;
        }
        
        cout << ans << '\n';
    }

    return 0;
}