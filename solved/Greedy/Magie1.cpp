/*
    Programmer : Alexandru Olteanu
    Problem : https://www.pbinfo.ro/probleme/4474/magie1
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

// ifstream in("magie.in");
// ofstream out("magie.out");
// #define cin in
// #define cout out

const ll infll = 9e18;
const int inf = 2e9;
const ll maxn = 2e5 + 5;

int a[maxn];

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin>>test;
    for (int tt = 1; tt <= test; ++tt) {

        int c, n;
        cin >> c >> n;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }

        if (c == 1) {
            map<int, int> m;
            int mx = 0;
            for (int i = 1; i <= n; ++i) {
                ++m[a[i]];
                mx = max(mx, m[a[i]]);
            }

            cout << mx << '\n';
            return 0;
        }
        if (c == 2) {

            int l = 0;
            int lmax = 0;
            for (int j = 1; j <= 10000; ++j) {
                l = 0;
                for (int i = 1; i <= n; ++i) {
                    if (a[i] > j) {
                        l = 0;
                        continue;
                    }
                    if (a[i] == j) {
                        ++l, lmax = max(lmax, l);
                        continue;
                    }
                    if (a[i] % (j - a[i]) == 0) {
                        ++l, lmax = max(lmax, l);
                        continue;
                    }
                    l = 0;
                }
            }
            cout << lmax << '\n';
            return 0;
        }

        map<int, int> m;
        for (int i = 1; i <= n; ++i) {
            ++m[a[i]];
            for (int j = 1; j * j <= a[i]; ++j) {
                if (a[i] % j == 0) {
                    ++m[a[i] + j];
                    if (j != a[i] / j) {
                        ++m[a[i] + a[i] / j];
                    }
                }
            }
        }

        int mx = 0;
        for (int i = 1; i <= 10000; ++i) {
            mx = max(mx, m[i]);
        }

        cout << mx << '\n';


    }

    return 0;
}