/*
    Programmer : Alexandru Olteanu
    Problem Link : https://atcoder.jp/contests/abc339/tasks/abc339_b
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
const int mod = 1000000007;
const int mod2 = 100000000;
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
const int maxn = 1e2 + 5;

char c[maxn][maxn];
int dx[] = {0, 0, -1, 0, 1};
int dy[] = {0, -1, 0, 1, 0};

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int n, m, k;
        cin >> n >> m >> k;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                c[i][j] = '.';
            }
        }
        int d = 2;
        int x = 1, y = 1;
        while (k--) {
            if (c[x][y] == '.') {
                c[x][y] = '#';
                ++d;
                if (d > 4) d = 1;
            }
            else {
                c[x][y] = '.';
                --d;
                if (d < 1) d = 4;
            }
            x += dx[d];
            y += dy[d];
            if (x > n) x = 1;
            if (x < 1) x = n;
            if (y < 1) y = m;
            if (y > m) y = 1;
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                cout << c[i][j];
            }
            cout << '\n';
        }
        
    }

    return 0;
}
