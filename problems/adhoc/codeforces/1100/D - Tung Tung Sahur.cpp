/*
  ░█████╗░██╗░░░░░███████╗██╗░░██╗░█████╗░███╗░░██╗██████╗░██████╗░██╗░░░██╗██╗███╗░░██╗██╗░░░██╗
  ██╔══██╗██║░░░░░██╔════╝╚██╗██╔╝██╔══██╗████╗░██║██╔══██╗██╔══██╗██║░░░██║██║████╗░██║██║░░░██║
  ███████║██║░░░░░█████╗░░░╚███╔╝░███████║██╔██╗██║██║░░██║██████╔╝██║░░░██║██║██╔██╗██║╚██╗░██╔╝
  ██╔══██║██║░░░░░██╔══╝░░░██╔██╗░██╔══██║██║╚████║██║░░██║██╔══██╗██║░░░██║██║██║╚████║░╚████╔╝░
  ██║░░██║███████╗███████╗██╔╝╚██╗██║░░██║██║░╚███║██████╔╝██║░░██║╚██████╔╝██║██║░╚███║░░╚██╔╝░░
  ╚═╝░░╚═╝╚══════╝╚══════╝╚═╝░░╚═╝╚═╝░░╚═╝╚═╝░░╚══╝╚═════╝░╚═╝░░╚═╝░╚═════╝░╚═╝╚═╝░░╚══╝░░░╚═╝░░░
  They forged me in fire, they broke me in battle, yet here I rise, Invictus!
*/
// Link: https://codeforces.com/contest/2094/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// Useful
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
#define LightningFastReadWrite ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
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

// ifstream fin("input.in");
// ofstream fout("output.out");
// #define cin fin
// #define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 2e5 + 5;

vector<pii> v1, v2;

int main() {

    LightningFastReadWrite
    HighPrecision
    int test = 1;
    cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        v1.clear();
        v2.clear();
        string a, b;
        cin >> a >> b;
        int l = 1;
        int n = a.size();
        for (int i = 1; i < n; ++i) {
            if (a[i] == a[i - 1]) {
                ++l;
            } else {
                if (a[i - 1] == 'L') {
                    v1.pb({1, l});
                    l = 1;
                } else {
                    v1.pb({2, l});
                    l = 1;
                }
            }
        }

        if (a[n - 1] == 'L') {
            v1.pb({1, l});
            l = 1;
        } else {
            v1.pb({2, l});
            l = 1;
        }

        l = 1;
        n = b.size();
        for (int i = 1; i < n; ++i) {
            if (b[i] == b[i - 1]) {
                ++l;
            } else {
                if (b[i - 1] == 'L') {
                    v2.pb({1, l});
                    l = 1;
                } else {
                    v2.pb({2, l});
                    l = 1;
                }
            }
        }

        if (b[n - 1] == 'L') {
            v2.pb({1, l});
            l = 1;
        } else {
            v2.pb({2, l});
            l = 1;
        }
        if (v1.size() != v2.size() || v1[0].fi != v2[0].fi) {
            cout << "NO\n";
            continue;
        }
        bool ok = true;
        for (int i = 0; i < (int) v1.size(); ++i) {
            int x = v1[i].se;
            int y = v2[i].se;
            if (y < x || y > 2 * x) {
                ok = false;
                break;
            }
        }

        cout << (ok ? "YES\n" : "NO\n");
    }

    return 0;
}