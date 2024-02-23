/*
    Programmer : Alexandru Olteanu
    Problem : https://codeforces.com/contest/1884/problem/C
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
const ll maxn = 2e5 + 5;

int l[maxn], r[maxn];
vector<pii> v, v1, v2;

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    cin>>test;
    for (int tt = 1; tt <= test; ++tt) {

        int n, m;
        cin >> n >> m;
        v.clear();
        v1.clear();
        v2.clear();
        int left = inf, right = -inf;
        for (int i = 1; i <= n; ++i) {
            cin >> l[i] >> r[i];
            left = min(left, l[i]);
            right = max(right, r[i]);
            v.pb({l[i], 1});
            v.pb({r[i] + 1, -1});
            if (l[i] != 1) {
                v1.pb({l[i], 1});
                v1.pb({r[i] + 1, -1});
            }
            if (r[i] != m) {
                v2.pb({l[i], 1});
                v2.pb({r[i] + 1, -1});
            }
        }

        sort(all(v));
        sort(all(v1));
        sort(all(v2));
        
        if (left > 1 || right < m) {
            int mx = 0;
            int sum = 0;
            for (auto u : v) {
                sum += u.second;
                mx = max(mx, sum);
            }
            cout << mx << '\n';
            continue;
        }

        int mx = 0;
        int sum = 0;
        for (auto u : v1) {
            sum += u.second;
            mx = max(mx, sum);
        }
        int mx1 = 0;
        sum = 0;
        for (auto u : v2) {
            sum += u.second;
            mx1 = max(mx1, sum);
        }
        cout << max(mx, mx1) << '\n';
        
    }

    return 0;
}