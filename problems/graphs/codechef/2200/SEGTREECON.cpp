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

// Link: https://www.codechef.com/problems/SEGTREECON
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
// #define LocalRun
#define YES cout << "YES\n";
#define Yes cout << "Yes\n";
#define NO cout << "NO\n";
#define No cout << "No\n";
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
const int maxn = 2e6 + 2;

struct node {
    int l;
    int r;
    int lvl;

    bool operator<(const node& other) const {
        return lvl < other.lvl;
    }
};
int a[maxn];

void solveTask(int testNr) {

    int n, k;
    cin >> n >> k;
    int pr = (1 << (n + 1));
    if (pr - 1 < k) {
        No;
        return;
    }
    if (pr - 1 - (n + 1) < k && pr - 1 != k) {
        No;
        return;
    }

    int p = (1 << n);
    for (int i = 1; i <= p; ++i) {
        a[i] = 1;
    }

    multiset<pair<int, node>> s;
    s.insert({n + 1, {1, n, n}});
    int nr = (1 << (n + 1)) - 1;
    while (nr != k) {
        auto it = (--s.end());
        if (nr - (*it).fi < k) {
            s.erase(it);
            continue;
        }
        int v = (*it).fi;
        int l = (*it).se.l;
        int r = (*it).se.r;
        int lvl = (*it).se.lvl;
        nr -= v;
        a[l] = 0;
        s.erase(it);
        int dist = 2;
        int st = l + 1, dr = l + 1;
        for (int j = 0; j < lvl; ++j) {
            s.insert({j + 1, {st, dr, j}});
            st = dr + 1;
            dr = st + dist - 1;
            dist *= 2;
        }
    }

    Yes;
    for (int i = 1; i <= p; ++i) {
        cout << a[i];
    }
    cout << '\n';
}

void precompute() {}

int main() {

    LightningFastReadWrite
    RealValuesHighPrecision

    #ifdef LocalRun
        auto start = chrono::high_resolution_clock::now();
    #endif

    int totalNrOfTests = 1;
    cin >> totalNrOfTests;
    precompute();
    for (int testNr = 1; testNr <= totalNrOfTests; ++testNr) {
        // cout << "Case #" << testNr << ": ";
        // cout << "Test #" << testNr << ": ";
        solveTask(testNr);
    }

    #ifdef LocalRun
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        cout << "\nTime taken: " << duration.count() << " seconds." << '\n';
    #endif

    return 0;
}