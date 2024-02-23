/*
    Programmer : Alexandru Olteanu
    Problem : https://codeforces.com/contest/1543/problem/C
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// GCC Optimizations
// #pragma GCC optimize("Ofast");
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


double bkt(double c, double m, double p, double v, double taken, double pr) {
    double res = 0;
    double dif = c - v;
    if (fabs(dif) > 1e-6 && dif > 0) {
        double m1 = m, p1 = p;
        if (m1 != 0) m1 += v / 2, p1 += v / 2;
        else p1 += v;
        res += bkt(c - v, m1, p1, v, taken + 1, pr * c);
    }
    else {
        if (c != 0) {
            double m1 = m, p1 = p;
            if (m1 != 0) m1 += c / 2, p1 += c / 2;
            else p1 += c;
            res += bkt(0, m1, p1, v, taken + 1, pr * c);
        }
    }
    dif = m - v;
    if (fabs(dif) > 1e-6 && dif > 0) {
        double c1 = c, p1 = p;
        if (c1 != 0) c1 += v / 2, p1 += v / 2;
        else p1 += v;
        res += bkt(c1, m - v, p1, v, taken + 1, pr * m);
    }
    else {
        if (m != 0) {
            double c1 = c, p1 = p;
            if (c1 != 0) c1 += m / 2, p1 += m / 2;
            else p1 += m;
            res += bkt(c1, 0, p1, v, taken + 1, pr * m);
        }
    }
    res += pr * p * (taken + 1);
    return res;
}

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    cin>>test;
    for (int tt = 1; tt <= test; ++tt) {

        double c, m, p, v;
        cin >> c >> m >> p >> v;
        double ans = bkt(c, m, p, v, 0, 1);
        cout << ans << '\n';

    }

    return 0;
} 