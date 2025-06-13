/*
  ░█████╗░██╗░░░░░███████╗██╗░░██╗░█████╗░███╗░░██╗██████╗░██████╗░██╗░░░██╗██╗███╗░░██╗██╗░░░██╗
  ██╔══██╗██║░░░░░██╔════╝╚██╗██╔╝██╔══██╗████╗░██║██╔══██╗██╔══██╗██║░░░██║██║████╗░██║██║░░░██║
  ███████║██║░░░░░█████╗░░░╚███╔╝░███████║██╔██╗██║██║░░██║██████╔╝██║░░░██║██║██╔██╗██║╚██╗░██╔╝
  ██╔══██║██║░░░░░██╔══╝░░░██╔██╗░██╔══██║██║╚████║██║░░██║██╔══██╗██║░░░██║██║██║╚████║░╚████╔╝░
  ██║░░██║███████╗███████╗██╔╝╚██╗██║░░██║██║░╚███║██████╔╝██║░░██║╚██████╔╝██║██║░╚███║░░╚██╔╝░░
  ╚═╝░░╚═╝╚══════╝╚══════╝╚═╝░░╚═╝╚═╝░░╚═╝╚═╝░░╚══╝╚═════╝░╚═╝░░╚═╝░╚═════╝░╚═╝╚═╝░░╚══╝░░░╚═╝░░░
  They forged me in fire, they broke me in battle, yet here I rise, Invictus!
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

// Link: https://codeforces.com/contest/1625/problem/C
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
const int maxn = 5e2 + 5;

ll a[maxn], s[maxn];

struct {
    ll cost;
    ll speed;
}dp[maxn][maxn];

int main() {

    LightningFastReadWrite
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int n, l, k;
        cin >> n >> l >> k;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }
        for (int i = 1; i <= n; ++i) {
            cin >> s[i];
        }
        if (n == 1) {
            cout << 1LL * l * s[1] << '\n';
            return 0;
        }
        ++n;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= k; ++j) {
                dp[i][j].cost = inf;
            }
        }
        a[n] = l;
        s[n] = 0;
        dp[1][0].cost = 0;
        dp[2][0].cost = (a[2] - a[1]) * s[1];
        dp[2][0].speed = s[1];
        for (int i = 3; i <= n; ++i) {
            for (int j = 0; j <= k; ++j) {
                for (int t = 1; t < i; ++ t) {
                    int nr1 = i - t - 1;
                    int nr2 = j - nr1;
                    if (nr1 > k || nr2 < 0) {
                        continue;
                    }
                    ll c1 = dp[t][nr2].cost + (a[i] - a[t]) * s[t];
                    if (c1 == dp[i][j].cost) {
                        dp[i][j].speed = min(dp[i][j].speed, s[t]);
                    }
                    if (c1 < dp[i][j].cost) {
                        dp[i][j].cost = c1;
                        dp[i][j].speed = s[t];
                    }

                }
            }
        }

        ll ans = dp[n][0].cost;
        for (int i = 1; i <= k; ++i) {
            ans = min(ans, dp[n][i].cost);
        }

        cout << ans << '\n';

    }

    return 0;
}