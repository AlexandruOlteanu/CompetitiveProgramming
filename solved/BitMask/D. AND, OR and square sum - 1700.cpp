/*
    Programmer : Alexandru Olteanu
    Problem : https://codeforces.com/contest/1368/problem/D
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

ll a[maxn];

int have[25], need[25];

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin>>test;
    for (int tt = 1; tt <= test; ++tt) {

        int n;
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }

        sort(a + 1, a + n + 1);

        for (int i = n; i >= 1; --i) {
            for (int j = 21; j >= 0; --j) {
                if ((a[i] & (1 << j)) > 0) {

                } 
                else {
                    ++need[j];
                }
            }
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = 21; j >= 0; --j) {
                if ((a[i] & (1 << j)) > 0) {
                    if (have[j] < need[j]) {
                        ++have[j];
                        a[i] ^= (1 << j);              
                    }
                }
                else {
                    if (have[j]) {
                        --have[j];
                        --need[j];
                        a[i] ^= (1 << j);
                        if (have[j] < need[j]) {
                            ++have[j];
                            a[i] ^= (1 << j);
                        }
                    }
                    else {
                        --need[j];
                    }
                }
            }
        }


        ll ans = 0;
        for (int i = 1; i <= n; ++i) {
            ans += a[i] * a[i];
        }

        cout << ans << '\n';
        
    }

    return 0;
} 