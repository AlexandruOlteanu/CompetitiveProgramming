/*
    Programmer : Alexandru Olteanu
    Problem Link : https://codeforces.com/contest/1920/problem/D
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

vector<ll> v;
vector<ll> r;


int main() {

    FastEverything
    HighPrecision
    int test = 1;
    cin>>test;
    for (int tt = 1; tt <= test; ++tt) {

        int n, q;
        cin >> n >> q;
        v.clear();
        r.clear();
        v.pb(-1);
        r.pb(-1);
        for (int i = 1; i <= n; ++i) {
            int p, x;
            cin >> p >> x;
            if (p == 1) {
                v.pb(x);
                if (r.size() == 1) {
                    r.pb(1);
                }
                else {
                    if (r.back() < 1e18 + 4) {
                        r.pb(r.back() + 1);
                    }
                }
            }
            else {
                v.pb(-x);
                ll mx = 1e18 + 5 - r.back();
                if (r.back() <= mx / x) {
                    ll t = r.back() + r.back() * x;
                    if (t >= 1e18 + 5) {
                        t = 1e18 + 5;
                    }
                    if (t != r.back())
                    r.pb(t);
                }
                else {
                    if (1e18 + 5 != r.back())
                    r.push_back(1e18 + 5);
                }
            }
        }

        while (q--) {
            ll x;
            cin >> x;
            bool ok = false;
            while (!ok) {
                int lo = 1, hi = n;
                if (hi > r.size() - 1) {
                    hi = r.size() - 1;
                }
                int ans = 0;
                while (lo <= hi) {
                    int mid = lo + (hi - lo) / 2;
                    if (r[mid] == x) {
                        ans = mid;
                        break;
                    }
                    if (r[mid] < x) {
                        ans = mid;
                        lo = mid + 1;
                        continue;
                    }
                    hi = mid - 1; 
                }
                if (r[ans] == x && v[ans] > 0) {
                    cout << v[ans] << " ";
                    ok = true;
                }
                else {
                    if (v[ans] < 0) {
                        --ans;
                    }
                    x %= r[ans];
                    if (x == 0) x = r[ans];
                }
            }

        }

        cout << '\n';
        
    }

    return 0;
}
