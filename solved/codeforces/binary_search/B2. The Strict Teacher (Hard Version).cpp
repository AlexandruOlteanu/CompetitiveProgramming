/*
    Programmer : Alexandru Olteanu (OltAlexandru)
    Problem Link : https://codeforces.com/contest/2005/problem/B2
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

// ifstream fin("input.in");
// ofstream fout("output.out");
// #define cin fin
// #define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 2e5 + 5;

int b[maxn];

int main() {



    FastEverything
    HighPrecision
    int test = 1;
    cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int n, m, q;
        cin >> n >> m >> q;
        for (int i = 1; i <= m; ++i) {
            cin >> b[i];
        }
        sort(b + 1, b + m + 1);
        while (q--) {
            int x;
            cin >> x;
            int lo = 1, hi = m;
            int ans = -1;
            while (lo <= hi) {
                int mid = lo + (hi - lo) / 2;
                if (b[mid] < x) {
                    ans = b[mid];
                    lo = mid + 1;
                    continue;
                }
                hi = mid - 1;
            }
            int ans1 = -1;
            lo = 1, hi = m;
            while (lo <= hi) {
                int mid = lo + (hi - lo) / 2;
                if (b[mid] > x) {
                    ans1 = b[mid];
                    hi = mid - 1;
                    continue;
                }
                lo = mid + 1;
            }
            if (ans < 0) {
                cout << ans1 - 1 << '\n';
                continue;
            }
            if (ans1 < 0) {
                cout << n - ans << '\n';
                continue;
            }
            int pos = (ans + ans1) / 2;
            int res = pos - ans;
            if (ans1 - pos < res) {
                res = ans1 - pos;
            }
            cout << res << '\n';
        }

    }

    return 0;
}
