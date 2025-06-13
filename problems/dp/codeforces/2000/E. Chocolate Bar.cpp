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
// Link: https://codeforces.com/contest/598/problem/E

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// Useful
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
#define LightningFastReadWrite ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define RealValuesHighPrecision cout << fixed << setprecision(17);
typedef long long ll;
typedef pair<int, int> pii;
const int mod = 1000000007;
const int mod1 = 998244353;
ll mypowr(ll a, ll b, ll mod1) {ll res = 1; if(b < 0)b = 0; a %= mod1; assert(b >= 0);
for(; b; b >>= 1){if (b & 1) res = res * a % mod1;a = a * a % mod1;} return res;}
ll mypow(ll a, ll b) {ll res = 1; if(b < 0)b = 0;assert(b >= 0);
for(; b; b >>= 1){if(b & 1) res = res * a;a = a * a;} return res;}
#define YES cout << "YES\n";
#define NO cout << "NO\n";
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
const int maxn = 2e5 + 2;

ll dp[31][31][51];
bool solved[31][31][51];

ll bkt(int x, int y, int k) {
    if (solved[x][y][k]) return dp[x][y][k];
    if (solved[y][x][k]) return dp[y][x][k];
    // if (x * y - k > 0 && solved[x][y][x * y - k]) return dp[x][y][x * y - k];
    // if (x * y - k > 0 && solved[y][x][x * y - k]) return dp[y][x][x * y - k];
    if (x * y == k) {
        dp[x][y][k] = 0;
        solved[x][y][k] = true;
        return 0;
    }
    ll ans = infll;
    for (int i = 1; i < y; ++i) {
        if (k <= x * i) ans = min(ans, x * x + bkt(x, i, k));
        if (k <= x * (y - i)) ans = min(ans, x * x + bkt(x, y - i, k));
        for (int j = 1; j < k; ++j) {
            if (j > x * i) break;
            if (k - j <= x * (y - i)) {
                ans = min(ans, x * x + bkt(x, i, j) + bkt(x, y - i, k - j));
            }
        }
    }
    swap(x, y);
    for (int i = 1; i < y; ++i) {
        if (k <= x * i) ans = min(ans, x * x + bkt(x, i, k));
        if (k <= x * (y - i)) ans = min(ans, x * x + bkt(x, y - i, k));
        for (int j = 1; j < k; ++j) {
            if (j > x * i) break;
            if (k - j <= x * (y - i)) {
                ans = min(ans, x * x + bkt(x, i, j) + bkt(x, y - i, k - j));
            }
        }
    }
    dp[x][y][k] = ans;
    solved[x][y][k] = true;
    return ans;
}


void solveTask(int testNr) {

    int n, m, k;
    cin >> n >> m >> k;
    cout << bkt(n, m, k) << '\n';
}

void precompute() {}

int main() {

    LightningFastReadWrite
    RealValuesHighPrecision

    int totalNrOfTests = 1;
    cin >> totalNrOfTests;
    precompute();
    for (int testNr = 1; testNr <= totalNrOfTests; ++testNr) {
        solveTask(testNr);
    }

    return 0;
}