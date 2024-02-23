/*
    Programmer : Alexandru Olteanu
    Problem : https://codeforces.com/contest/1185/problem/D
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

pii a[maxn];
bool l[maxn], r[maxn];

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin>>test;
    for (int tt = 1; tt <= test; ++tt) {

        int n;
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i].first;
            a[i].second = i;
        }

        sort(a + 1, a + n + 1);

        int ratio = a[2].first - a[1].first;
        l[0] = l[1] = true;
        for (int i = 2; i <= n; ++i) {
            l[i] = l[i - 1];
            if (!l[i]) break;
            if (a[i].first - a[i - 1].first != ratio) l[i] = false;
        }
        if (l[n - 1]) {
            cout << a[n].second << '\n';
            return 0;
        }

        r[n + 1] = r[n] = true;
        ratio = a[n].first - a[n - 1].first;
        for (int i = n - 1; i >= 1; --i) {
            r[i] = r[i + 1];
            if (!r[i]) break;
            if (a[i + 1].first - a[i].first != ratio) r[i] = false;
        }
        if (r[2]) {
            cout << a[1].second << '\n';
            return 0;
        }

        if ((a[n].first - a[1].first) % (n - 2) != 0) {
            cout << "-1\n";
            return 0;
        }  
        ratio = (a[n].first - a[1].first) / (n - 2);
        int have = 0, pos = -1;
        int cur = a[1].first + ratio;
        for (int i = 2; i < n; ++i) {
            if (a[i].first != cur) {
                ++have;
                pos = i;
                continue;
            }
            cur += ratio;
        }

        if (have > 1) {
            cout << "-1\n";
            return 0;
        }

        cout << a[pos].second << '\n';
        
    }

    return 0;
}