/*
    Programmer : Alexandru Olteanu
    Problem : https://codeforces.com/contest/1743/problem/D
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


int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin>>test;
    for (int tt = 1; tt <= test; ++tt) {

        int n;
        cin >> n;
        string s;
        cin >> s;
        reverse(all(s));
        while (!s.empty() && s.back() == '0') s.pop_back();
        if (s.empty()) {
            cout << "0\n";
            return 0;
        }
        reverse(all(s));
        n = s.size();
        int pos = -1;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '0') {
                pos = i;
                break;
            }
        }
        if (pos < 0) {
            cout << s << '\n';
            return 0;
        }

        deque<char> c;
        for (int i = pos; i < n; ++i) {
            c.pb(s[i]);
        }
        string ans = s;
        for (int i = pos - 1; i >= 0; --i) {
            c.pop_back();
            c.push_front(s[i]);
            string cur = s;
            int k = 0;
            for (int j = pos; j < n; ++j) {
                if (cur[j] == '0' && c[k] == '1') {
                    cur[j] = '1';
                } 
                ++k;
            }
            ans = max(ans, cur);
        }

        cout << ans << '\n';
    }

    return 0;
} 