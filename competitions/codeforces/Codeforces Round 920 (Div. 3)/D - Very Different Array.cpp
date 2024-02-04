/*
    Programmer : Alexandru Olteanu
    Problem Link : https://codeforces.com/contest/1921/problem/D
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

deque<int> a, b;

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    cin>>test;
    for (int tt = 1; tt <= test; ++tt) {

        int n, m;
        cin >> n >> m;
        a.clear();
        b.clear();
        for (int i = 1; i <= n; ++i) {
            int x;cin >> x;
            a.pb(x);
        }
        for (int i = 1; i <= m; ++i) {
            int x; cin >> x;
            b.pb(x);
        }
        sort(all(a));
        sort(all(b));
        ll d = 0;
        while (!a.empty()) {
            int pos1 = 1, pos2 = 1;
            int x1 = a.front(), x2 = a.back();
            int y1 = b.front(), y2 = b.back();
            int mx = abs(x1 - y1);
            if (abs(x1 - y2) > mx) {
                mx = abs(x1 - y2);
                pos2 = 2;
            } 
            if (abs(x2 - y1) > mx) {
                mx = abs(x2 - y1);
                pos1 = 2;
                pos2 = 1;
            } 
            if (abs(x2 - y2) > mx) {
                mx = abs(x2 - y2);
                pos1 = 2;
                pos2 = 2;
            } 
            d += mx;
            if (pos1 == 1)a.pop_front();
            else a.pop_back();
            if (pos2 == 1)b.pop_front();
            else b.pop_back();
        }

        cout << d << '\n';




        
    }

    return 0;
}
