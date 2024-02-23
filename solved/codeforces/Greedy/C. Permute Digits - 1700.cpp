/*
    Programmer : Alexandru Olteanu
    Problem : https://codeforces.com/contest/915/problem/C
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



int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin>>test;
    for (int tt = 1; tt <= test; ++tt) {

        vector<int> v;
        string a, b;
        cin >> a >> b;
        int n = a.size();
        int m = b.size();
        for (int i = 0; i < n; ++i) {
            v.pb(a[i] - '0');
        }
        sort(rall(v));
        if (n < m) {
            for (auto u : v) {
                cout << u;
            }
            return 0;
        }
        string res = "";
        for (int i = 0; i < n; ++i) {
            int sz = v.size();
            bool ok = false;
            for (int j = 0; j < sz; ++j) {
                if (v[j] <= b[i] - '0') {
                    res += (v[j] + '0');
                    ok = true;
                    v.erase(v.begin() + j);
                    break;
                }
            }
            if (v.empty()) {
                break;
            }
            if (ok) {
                if (res[i] < b[i]) {
                    for (auto u : v) {
                        res += u + '0';
                    }
                    break;
                }
            }
            else {
                for (int j = i - 1; j >= 0; --j) {
                    v.pb(res[j] - '0');
                    sort(rall(v));
                    for (int t = 0; t < (int) v.size(); ++t) {
                        if (v[t] < b[j] - '0') {
                            res[j] = v[t] + '0';
                            v.erase(v.begin() + t);
                            for (auto u : v) {
                                res += u + '0';
                            }
                            t = v.size() + 1;
                            j = -1;
                        }
                    }
                    if (j == -1) continue;
                    res.pop_back();
                }
                break;
            }

        }

        cout << res << '\n';
        
    }

    return 0;
}