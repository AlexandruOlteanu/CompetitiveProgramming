/*
    Programmer : Alexandru Olteanu
    Problem : https://codeforces.com/contest/1692/problem/H
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

int a[maxn];
map<int, int> m;
set<int> s;
vector<int> v[maxn];

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    cin>>test;
    for (int tt = 1; tt <= test; ++tt) {

        int n;
        cin >> n;
        int nr = 1;
        m.clear();
        s.clear();
        for (int i = 1; i <= n; ++i) {
            v[i].clear();
        }
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            if (!m[a[i]]) {
                m[a[i]] = nr;
                ++nr;
            }
            v[m[a[i]]].pb(i);
        }

        int ans = 0, l = 0, r = 0;
        nr = 0;
        for (int i = 1; i <= n; ++i) {
            if (s.count(a[i])) {
                continue;
            }
            s.insert(a[i]);

            int cur = m[a[i]];
            int sz = v[cur].size();
            int res = 1, l1 = v[cur][0], r1 = v[cur][0];
            for (int j = 1; j < sz; ++j) {
                int sm = res - (v[cur][j] - v[cur][j - 1] - 1) + 1;
                if (sm < 1) {
                    l1 = v[cur][j];
                    r1 = v[cur][j];
                    res = 1;
                }
                else {
                    res = sm;
                    r1 = v[cur][j];
                }
                if (res > ans) {
                    ans = res;
                    nr = a[i];
                    l = l1, r = r1;
                }
            }

            if (res > ans) {
                ans = res;
                nr = a[i];
                l = l1, r = r1;
            }
            
        }
        cout << nr << " " << l << " " << r << '\n';
    }

    return 0;
}