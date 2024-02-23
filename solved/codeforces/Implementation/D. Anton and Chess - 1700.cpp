/*
    Programmer : Alexandru Olteanu
    Problem : https://codeforces.com/problemset/problem/734/D
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

// ifstream in("input.txt");
// ofstream out("output.txt");
// #define cin in
// #define cout out

const ll infll = 0x7fffffffffffffff;
const int inf = 0x7fffffff;
const ll maxn = 2e5 + 5;

vector<pii> v;
int dir[5][2];
int diag[5][2];


void updateR(int dist, int c, int type) {
    if (dist < dir[c][1]) {
        dir[c][1] = dist;
        dir[c][2] = type;
    }
}

void updateD(int x1, int y1, int x2, int y2, int dg, int type) {
    if (dg == 1) {
        int d = x1 - x2;
        x2 += d;
        y2 += d;
        if (x2 != x1 || y2 != y1) {
            return;
        }
        if (d < diag[dg][1]) {
            diag[dg][1] = d;
            diag[dg][2] = type;
        }
    }
    if (dg == 2) {
        int d = x1 - x2;
        x2 += d;
        y2 -= d;
        if (x2 != x1 || y2 != y1) {
            return;
        }
        if (d < diag[dg][1]) {
            diag[dg][1] = d;
            diag[dg][2] = type;
        }
    }
    if (dg == 3) {
        int d = x2 - x1;
        x2 -= d;
        y2 += d;
        if (x2 != x1 || y2 != y1) {
            return;
        }
        if (d < diag[dg][1]) {
            diag[dg][1] = d;
            diag[dg][2] = type;
        }
    }
    if (dg == 4) {
        int d = x2 - x1;
        x2 -= d;
        y2 -= d;
        if (x2 != x1 || y2 != y1) {
            return;
        }
        if (d < diag[dg][1]) {
            diag[dg][1] = d;
            diag[dg][2] = type;
        }
    }
}


int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin>>test;
    for (int tt = 1; tt <= test; ++tt) {

        int n, x, y;
        cin >> n >> x >> y;
        for (int i = 1; i <= 4; ++i) {
            dir[i][1] = inf;
            diag[i][1] = inf;
        }
        for (int i = 1; i <= n; ++i) {
            char c;
            int x1, y1;
            cin >> c >> x1 >> y1;
            int type = 1;
            if (c == 'R') type = 2;
            if (c == 'Q') type = 3;
            if (x1 == x) {
                if (y1 > y) {
                    updateR(y1 - y, 3, type);
                }
                else {
                    updateR(y - y1, 1, type);
                }
            }
            if (y1 == y) {
                if (x1 < x) {
                    updateR(x - x1, 2, type);
                }
                else {
                    updateR(x1 - x, 4, type);
                }
            }
            if (x1 < x && y1 < y) {
                updateD(x, y, x1, y1, 1, type);
            }
            if (x1 < x && y1 > y) {
                updateD(x, y, x1, y1, 2, type);
            }
            if (x1 > x && y1 < y) {
                updateD(x, y, x1, y1, 3, type);
            }
            if (x1 > x && y1 > y) {
                updateD(x, y, x1, y1, 4, type);
            }   
        }

        bool ok = false;
        for (int i = 1; i <= 4; ++i) {
            if (dir[i][2] > 1) ok = true;
            if (diag[i][2] == 1 || diag[i][2] == 3) ok = true;
        }

        cout << (ok ? "YES\n" : "NO\n");

        
    }

    return 0;
}
