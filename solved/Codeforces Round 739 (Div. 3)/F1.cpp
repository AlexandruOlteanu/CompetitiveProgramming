/*
    Programmer : Alexandru Olteanu
*/
#include<bits/stdc++.h>
using namespace std;
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


vector<int> v;

int n, k;

void bkt(ll nr) {
    if (nr > inf) {
        return;
    }
    if (nr == 0 && !v.empty()) {
        return;
    }
    v.pb(nr);
    for (int i = 0; i <= 9; ++i) {
        int dif = 0;
        int x = nr;
        bool ap[10] = {0};
        while (x) {
            if (!ap[x % 10] && x % 10 != i) ++dif;
            ap[x % 10] = true;
            x /= 10;
        }
        if (dif <= 1) {
            bkt(nr * 10 + i);
        }
    }
}

int main()
{
    FastEverything
    HighPrecision
    int test = 1;
    cin>>test;
    bkt(0);
    sort(all(v));
    vector<int> v1;
    for (auto x : v) {
        int y = x;
        int u = y % 10;
        bool ok = true;
        while (y) {
            if (y % 10 != u) ok = false;
            y /= 10;
        }
        if (ok) v1.pb(x);
    }
    for(int tt = 1; tt <= test; ++tt){

        cin >> n >> k;
        if (k == 1) {
            for (auto x : v1) {
                if (x >= n) {
                    cout << x << '\n';
                    break;
                }
            }
            continue;
        }        
        int lo = 0, hi = v.size() - 1;
        int x = inf;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (v[mid] >= n) {
                x = v[mid];
                hi = mid - 1;
            }
            else {
                lo = mid + 1;
            }
        }

        cout << x << '\n';
        
    }

    return 0;
} 

