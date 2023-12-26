/*
    Programmer : Alexandru Olteanu
*/
#include<bits/stdc++.h>
using namespace std;
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
const ll maxn = 2e5 + 5;


vector<int> v[maxn];
int deg[maxn];
bool vis[maxn];
bool vis2[maxn];

void keep_cycle(int x) {
    if (vis[x]) return;
    --deg[x];
    vis[x] = true;
    for (auto u : v[x]) {
        if (deg[u] > 0) {
            --deg[u];
        }
        if (deg[u] == 1) {
            keep_cycle(u);
        }
    }
}

int dist;
int entry_point;
void dfs(int x, int d) {
    if (vis2[x]) return;
    vis2[x] = true;
    if (!vis[x]) {
        if (d < dist) {
            dist = d;
            entry_point = x;
        }
        dist = min(dist, d);
        return;
    }
    for (auto u : v[x]) {
        dfs(u, d + 1);
    }
}

int d2[maxn];
void dfs2(int x) {
    for (auto u : v[x]) {
        if (d2[u] > d2[x] + 1) {
            d2[u] = d2[x] + 1;
            dfs2(u);
        }
    }
}


int main()
{
    FastEverything
    HighPrecision
    int test = 1;
    cin>>test;
    for(int tt = 1; tt <= test; ++tt){

        int n, a, b;
        cin >> n >> a >> b;
        for (int i = 1; i <= n; ++i) {
            v[i].clear();
            deg[i] = 0;
            vis[i] = 0;
            vis2[i] = 0;
        }
        for (int i = 1; i <= n; ++i) {
            int x, y;
            cin >> x >> y;
            v[x].pb(y);
            ++deg[x], ++deg[y];
            v[y].pb(x);
        }
        if (a == b) {
            cout << "NO\n";
            continue;
        }

        for (int i = 1; i <= n; ++i) {
            if (deg[i] == 1) {
                keep_cycle(i);
            }
        }
        if (!vis[b]) {
            cout << "YES\n";
            continue;
        }

        dist = inf;
        dfs(b, 0);
        for (int i = 1; i <= n; ++i) {
            vis2[i] = false;
            d2[i] = inf;
        }
        d2[a] = 0;
        dfs2(a);
        if (dist < d2[entry_point]) {
            cout << "YES\n";
            continue;
        }

        cout << "NO\n";
        
    }

    return 0;
} 
