/*
    Programmer : Alexandru Olteanu
    Problem Link : https://codeforces.com/contest/1721/problem/D
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// Useful
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
#define FastEverything  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define HighPrecision cout << fixed << setprecision(17);
typedef long long ll;
typedef pair<int, int> pii;
const int mod = 1000000007;
const int mod1 = 998244353;
ll mypowr(ll a, ll b, ll mod1) {ll res = 1; if(b < 0)b = 0; a %= mod1; assert(b >= 0);
for(; b; b >>= 1){if (b & 1) res = res * a % mod1;a = a * a % mod1;} return res;}
ll mypow(ll a, ll b) {ll res = 1; if(b < 0)b = 0;assert(b >= 0);
for(; b; b >>= 1){if(b & 1) res = res * a;a = a * a;} return res;}
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

// ifstream fin("input.txt");
// ofstream fout("output.txt");
// #define cin fin
// #define cout fout

const ll infll = 0x7fffffffffffffff;
const int inf = 0x7fffffff;
const int maxn = 2e5 + 5;

vector<vector<int>> a, b, a1, b1;

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    cin >> test;
    for (int tt = 1; tt <= test; ++tt) {
        
        a.clear();
        b.clear();
        int n;
        cin >> n;
        vector<int> f;
        for (int i = 1; i <= n; ++i) {
            int x;
            cin >> x;
            f.push_back(x);
        }
        vector<int> s;
        for (int i = 1; i <= n; ++i) {
            int x;
            cin >> x;
            s.push_back(x);
        }
        a.push_back(f);
        b.push_back(s);

        int ans = 0;
        for (int i = 30; i >= 0; --i) {
            int p = (1 << i);
            bool ok = true;
            a1.clear();
            b1.clear();
            int sz = a.size();
            for (int j = 0; j < sz; ++j) {
                int sz1 = a[j].size();
                vector<int> z0, z1, u0, u1;
                for (auto x : a[j]) {
                    if ((x & p) > 0) {
                        u0.push_back(x);
                    }
                    else {
                        z0.push_back(x);
                    }
                }
                for (auto x : b[j]) {
                    if ((x & p) > 0) {
                        u1.push_back(x);
                    }
                    else {
                        z1.push_back(x);
                    }
                }
                if (z0.size() != u1.size() || z1.size() != u0.size()) {
                    ok = false;
                    break;
                }
                if (!z0.empty()) {
                    a1.push_back(z0);
                    b1.push_back(u1);
                }
                if (!z1.empty()) {
                    a1.push_back(u0);
                    b1.push_back(z1);
                }
            }
            if (!ok) continue;
            ans += p;
            a = a1, b = b1;
        }

        cout << ans << '\n';

        
    }

    return 0;
}