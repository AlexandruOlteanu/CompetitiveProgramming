/*
    Programmer : Alexandru Olteanu
    Problem : https://codeforces.com/problemset/problem/815/A
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

const ll infll = 9e18;
const int inf = 2e9;
const ll maxn = 2e2 + 5;

int b[maxn][maxn];
int col[maxn];

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin>>test;
    for (int tt = 1; tt <= test; ++tt) {

        int n, m;
        cin >> n >> m;
        int mn = inf;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                cin >> b[i][j];
                if (i == 1) mn = min(mn, b[i][j]);
            }
        }
        int res = inf, sum = 0;
        bool possible = false;
        vector<pair<int, int>> ans;
        vector<pair<int, int>> cur;
        
        for (int i = 0; i <= mn; ++i) {
            cur.clear();
            cur.pb({1, i});
            bool ok = true;
            sum = i;
            for (int j = 1; j <= m; ++j) {
                col[j] = b[1][j] - i;
                cur.pb({-j, col[j]});
                sum += col[j];
            }
            for (int i = 2; i <= n && ok; ++i) {
                int x = -1;
                for (int j = 1; j <= m && ok; ++j) {
                    if (b[i][j] < col[j]) {
                        ok = false;
                        continue;
                    }
                    if (x < 0) {
                        x = b[i][j] - col[j];
                        cur.pb({i, x});
                        sum += x;
                        continue;
                    }
                    if (b[i][j] - col[j] != x) {
                        ok = false;
                    }
                }
            }

            if (!ok) continue;
            possible = true;
            if (sum < res) {
                res = sum;
                ans = cur;
            }
        }


        if (!possible) {
            cout << "-1\n";
            return 0;
        }
        cout << res << '\n';
        for (auto u : ans) {
            for (int i = 1; i <= u.second; ++i) {
                if (u.first < 0) {
                    cout << "col ";
                }
                else {
                    cout << "row ";
                }
                cout << abs(u.first) << '\n';
            }
        }

    }

    return 0;
}