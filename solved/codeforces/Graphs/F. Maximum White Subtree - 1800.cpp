/*
    Programmer : Alexandru Olteanu
    Problem Link : https://codeforces.com/problemset/problem/1324/F
*/
#include <bits/stdc++.h>
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
#define HighPrecision cout << fixed << setprecision(17);
typedef long long ll;
typedef pair<int, int> pii;
const int mod = 1000000007LL;
const int mod2 = 100000000LL;
const int md = 998244353LL;
ll mypowr(ll a, ll b, ll mod1) {ll res = 1; if(b < 0)b = 0; a %= mod1; assert(b >= 0);
for(; b; b >>= 1){if (b & 1) res = res * a % mod1;a = a * a % mod1;} return res;}
ll mypow(ll a, ll b) {ll res = 1; if(b < 0)b = 0;assert(b >= 0);
for(; b; b >>= 1){if(b & 1) res = res * a;a = a * a;} return res;}
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

// ifstream fin("input.txt");
// ofstream fout("output.txt");
// #define cin fin
// #define cout fout

const ll infll = 0x7fffffffffffffff;
const int inf = 0x7fffffff;
const int maxn = 2e5 + 5;

int a[maxn];
vector<int> v[maxn];
int d[maxn];

void dfs(int x, int p) {
    d[x] = a[x];
    for (auto nx : v[x]) {
        if (nx == p) continue;
        dfs(nx, x);
        if (d[nx] > 0) d[x] += d[nx];
    }
}

void dfs2(int x, int p) {
    if (d[p] > d[x]) {
        if (d[x] >= 0) {
            d[x] = d[p];
        }
        else {
            d[x] += d[p];
        }
    }
    for (auto nx : v[x]) {
        if (nx == p) continue;
        dfs2(nx, x);
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
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            if (a[i] == 0) --a[i];
            d[i] = -inf;
        }

        for (int i = 1; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            v[x].push_back(y);
            v[y].push_back(x);
        }

        dfs(1, -1);
        dfs2(1, 1);
        for (int i = 1; i <= n; ++i) {
            cout << d[i] << " ";
        }

        cout << '\n';

        
    }

    return 0;
}