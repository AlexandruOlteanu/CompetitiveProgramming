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

map<char, int> ap, have;

int main()
{
    FastEverything
    HighPrecision
    int test = 1;
    cin>>test;
    for(int tt = 1; tt <= test; ++tt){

        string s;
        cin >> s;
        ap.clear();
        have.clear();
        int dim = 0;
        for (auto c : s) {
            ++ap[c];
            if (ap[c] == 1) ++dim;
        }
        int n = s.size();
        string order = "";
        bool ok = true;
        for (int i = n - 1; i >= 0; --i) {
            if (ap[s[i]] > 0) {
                order = s[i] + order;
                if (ap[s[i]] % dim != 0) {
                    ok = false;
                    break;
                }
                have[s[i]] = ap[s[i]] / dim;
                ap[s[i]] = 0;
                --dim;
            }
        }
        if (!ok) {
            cout << "-1\n";
            continue;
        }

        string res = "";
        for (int i = 0; i < n; ++i) {
            if (have[s[i]]) {
                res += s[i];
                --have[s[i]];
            }
        }

        string f = res;
        string d = res;
        string d1 = "";
        for (auto c : order) {
            d1 = "";
            for (auto c1 : d) {
                if (c1 != c) {
                    d1 += c1;
                }
            }
            d = d1;
            f += d;
        }
        if (f != s) {
            cout << "-1\n";
            continue;
        }
        cout << res << " " << order << '\n';
        
    }

    return 0;
} 

