/*
    Programmer : Alexandru Olteanu
    Problem : https://www.pbinfo.ro/probleme/4564/douadrumuri
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

ifstream in("douadrumuri.in");
ofstream out("douadrumuri.out");
#define cin in
#define cout out

const ll infll = 9e18;
const int inf = 2e9;
const ll maxn = 3e2 + 5;

short dp[2 * maxn][maxn][maxn];

vector<pii> v[2 * maxn]; 
string s[maxn];
int n;


int check(int diag, int x1, int y1, int x2, int y2) {
    if (x1 == x2 && y1 == y2 && x1 == 1) return 1;
    if (x1 == x2 && y1 == y2) return -inf;
    if (x1 < 1 || y1 < 1 || x2 < 1 || y2 < 1) return -inf;
    return dp[diag][x1][x2];
}

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin>>test;
    for (int tt = 1; tt <= test; ++tt) {

        cin >> n;
        for (int i = 1; i <= n; ++i) {
            cin >> s[i];
        }
        if (n == 1) {
            cout << "1\n";
            return 0;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                int d = i - 1 + j - 1;
                v[d].pb({i, j});
            }
        }

        dp[0][1][1] = 1;
        for (int i = 1; i <= 2 * n - 3; ++i) {
            int sz = v[i].size();
            for (int j = 0; j < sz; ++j) {
                for (int t = j + 1; t < sz; ++t) {
                    int x1 = v[i][j].first, y1 = v[i][j].second;
                    int x2 = v[i][t].first, y2 = v[i][t].second;
                    int mx = -inf;
                    mx = max(mx, check(i - 1, x1, y1 - 1, x2, y2 - 1));
                    mx = max(mx, check(i - 1, x1, y1 - 1, x2 - 1, y2));
                    mx = max(mx, check(i - 1, x1 - 1, y1, x2, y2 - 1));
                    mx = max(mx, check(i - 1, x1 - 1, y1, x2 - 1, y2));
                    mx += (s[x1][y1 - 1] == s[x2][y2 - 1]);
                    dp[i][x1][x2] = mx;
                    dp[i][x2][x1] = mx;
                }
            }
        }

        cout << dp[2 * n - 3][n][n - 1] + 1 << '\n';
        
    }

    return 0;
}
