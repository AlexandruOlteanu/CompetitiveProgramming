/*
    Programmer : Alexandru Olteanu
    Problem : https://codeforces.com/contest/732/problem/D
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


int d[maxn], a[maxn];

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin>>test;
    for (int tt = 1; tt <= test; ++tt) {

        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) {
            cin >> d[i];
        }

        for (int i = 1; i <= m; ++i) {
            cin >> a[i];
        }


        int lo = 1, hi = n, ans = -1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            vector<int> d1(mid + 1);
            for (int i = 1; i <= mid; ++i) {
                d1[i] = d[i];
            }
            set<int> s;
            for (int i = mid; i >= 1; --i) {
                if (!d1[i]) continue;
                    if (s.count(d1[i])) {
                        d1[i] = 0;
                        continue;
                    }
                s.insert(d1[i]);
            }

            if (s.size() != m) {
                lo = mid + 1;
                continue;
            }

            int cnt = 0;
            bool ok = true;
            for (int i = 1; i <= mid; ++i) {
                if (d1[i] == 0) {
                    ++cnt;
                    continue;
                }
                cnt -= a[d1[i]];
                if (cnt < 0) { 
                    ok = false;
                    break;
                }
            }
            if (!ok) {
                lo = mid + 1;
                continue;
            }
            ans = mid;
            hi = mid - 1;

        }

        

        cout << ans << '\n';
        
    }

    return 0;
}