/*
    Programmer : Alexandru Olteanu
    Problem Link : https://codeforces.com/contest/1705/problem/D
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

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 2e5 + 5;



int main() {

    FastEverything
    HighPrecision
    int test = 1;
    cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int n;
        cin >> n;
        string a, b;
        cin >> a >> b;
        vector<int> g1, g2, l1, l2;
        g1.push_back(a[0] % 2);
        g2.push_back(b[0] % 2);
        int p1 = 1, p2 = 1;
        for (int i = 1; i < n; ++i) {
            if (a[i] != a[i - 1]) {
                l1.push_back(p1);
                p1 = 1;
                g1.push_back(a[i] % 2);
            }
            else {
                ++p1;
            }
            if (b[i] != b[i - 1]) {
                l2.push_back(p2);
                p2 = 1;
                g2.push_back(b[i] % 2);
            }
            else {
                ++p2;
            }
        }
        l1.push_back(p1), l2.push_back(p2);

        if (g1 != g2) {
            cout << "-1\n";
            continue;
        }

        ll ans = 0;
        int sz = g1.size();
        vector<pair<ll, ll>> have, need;
        for (int i = 0; i < sz; ++i) {
            int x = l1[i], y = l2[i];
            if (x == y) continue;
            if (x > y) {
                int dif = x - y;
                while (!need.empty() && dif) {
                    auto u = need.back();
                    need.pop_back();
                    if (u.fi <= dif) {
                        dif -= u.fi;
                        ans += (i - u.se) * u.fi;
                    }
                    else {
                        u.fi -= dif;
                        ans += (i - u.se) * dif;
                        dif = 0;
                        need.push_back(u);
                    }
                }
                if (dif > 0) have.push_back({dif, i});
                continue;
            }
            int dif = y - x;
            while (!have.empty() && dif) {
                auto u = have.back();
                have.pop_back();
                if (u.fi <= dif) {
                    dif -= u.fi;
                    ans += (i - u.se) * u.fi;
                }
                else {
                    u.fi -= dif;
                    ans += (i - u.se) * dif;
                    dif = 0;
                    have.push_back(u);
                }
            }
            if (dif > 0) need.push_back({dif, i});
        }

        cout << ans << '\n';
        
    }

    return 0;
}