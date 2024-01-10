/*
    Programmer : Alexandru Olteanu
    Problem : https://codeforces.com/contest/1850/problem/H
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

vector<pair<int, int>> e[maxn];
map<pair<int, int>, int> v;
set<int> p;

int a1[maxn], b1[maxn], c1[maxn];

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    cin>>test;
    for (int tt = 1; tt <= test; ++tt) {

        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) {
            e[i].clear();
        }
        v.clear();
        bool ok = true;
        for (int i = 1; i <= m; ++i) {
            int x, y, c;
            cin >> x >> y >> c;
            a1[i] = x, b1[i] = y, c1[i] = c;
            if (v.count({x, y})) {
                if (v[{x, y}] != c) ok = false;
                continue;
            }
            v[{x, y}] = c;
            v[{y, x}] = -c;
            e[x].pb({y, c});
            e[y].pb({x, -c});
        }
        if (!ok) {
            cout << "NO\n";
            continue;
        }

        vector<ll> dist(n + 1, infll);
        queue<int> q;
        set<int> p;
        for (int i = 1; i <= n; ++i) {
            if (dist[i] != infll) continue;
            while (!q.empty()) q.pop();
            q.push(i);
            while (!q.empty()) {
                int top = q.front();
                q.pop();
                for (auto nxt : e[top]) {
                    if (dist[top] == infll && dist[nxt.first] != infll) {
                        dist[top] = dist[nxt.first] - nxt.second;
                    }
                    if (dist[top] != infll && dist[nxt.first] == infll) {
                        dist[nxt.first] = dist[top] + nxt.second;
                        q.push(nxt.first);
                    }
                }
                if (dist[top] == infll) {
                    dist[top] = 0;
                    for (auto nxt : e[top]) {
                        if (dist[top] == infll && dist[nxt.first] != infll) {
                            dist[top] = dist[nxt.first] - nxt.second;
                        }
                        if (dist[top] != infll && dist[nxt.first] == infll) {
                            dist[nxt.first] = dist[top] + nxt.second;
                            q.push(nxt.first);
                        }
                    }
                }
            }
        }

        for (int i = 1; i <= m; ++i) {
            if (dist[a1[i]] + c1[i] != dist[b1[i]]) {
                ok = false;
                break;
            }
        }
        

        cout << (ok ? "YES\n" : "NO\n");
        
    }

    return 0;
}