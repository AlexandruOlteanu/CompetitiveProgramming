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

// Link: https://www.pbinfo.ro/probleme/1260/asii
/* ------------------------------------------------------------------------
   Local Run Time and Debugging
------------------------------------------------------------------------ */
// #define LocalRun
// #define Debug
#ifdef Debug
    #include "debug.hpp"
    #define dbg(...) std::cerr << __DEBUG_UTIL__::outer << __LINE__ << ": [", __DEBUG_UTIL__::printer(#__VA_ARGS__, __VA_ARGS__)
    #define debugArr(...) std::cerr << __DEBUG_UTIL__::outer << __LINE__ << ": [", __DEBUG_UTIL__::printerArr(#__VA_ARGS__, __VA_ARGS__)
#else
    #define dbg(...) ((void)0)
    #define dbgArr(...) ((void)0)
#endif

/* ------------------------------------------------------------------------
   Policy‑based ordered set shortcut
------------------------------------------------------------------------ */
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

/* ------------------------------------------------------------------------
   RNG & custom hash for unordered containers
------------------------------------------------------------------------ */
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

/* ------------------------------------------------------------------------
   Helper functions
------------------------------------------------------------------------ */
long long mypowr(long long a, long long b, long long m = 1000000007) {
    long long  res = 1; a %= m;
    for (; b > 0; b >>= 1) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
    }
    return res;
}

long long mypow(long long a, long long b) {
    long long res = 1;
    for (; b > 0; b >>= 1) {
        if (b & 1) res = res * a;
        a *= a;
    }
    return res;
}

void YES() { cout << "YES\n"; }  void Yes() { cout << "Yes\n"; }  void yes() { cout << "yes\n"; }
void NO () { cout << "NO\n"; }  void No () { cout << "No\n"; }  void no () { cout << "no\n"; }

/* ------------------------------------------------------------------------
   Defines
------------------------------------------------------------------------ */
#define LightningFastReadWrite ios_base::sync_with_stdio(false); cin.tie(nullptr);
#define RealValuesHighPrecision cout << fixed << setprecision(17);
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
using ll  = long long;
using pii = pair<int, int>;
constexpr int mod   = 1000000007;
constexpr int mod1  = 998244353;
constexpr pair<int, int> dir4[] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
constexpr pair<int, int> dir8[] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
constexpr long long infll = numeric_limits<long long> :: max();
constexpr int inf = numeric_limits<int> :: max();

// ifstream fin("input.in");
// ofstream fout("output.out");
// #define cin fin
// #define cout fout

constexpr int maxn = 2e5 + 2;



/* Solution Main Entry Point */
void Invictus(int testNr) {

    int a, b;
    cin >> a >> b;
    cout << a + b << " " << a - b << " " << a * b << " " << a / b  << '\n';

}

void Precompute() {}

int main() {

    LightningFastReadWrite
    RealValuesHighPrecision

    #ifdef LocalRun
        auto start = chrono::high_resolution_clock::now();
    #endif

    int numberOfTests = 1;
    // cin >> numberOfTests;
    Precompute();
    for (int testNr = 1; testNr <= numberOfTests; ++testNr) {
        // cout << "Case #" << testNr << ": ";
        // cout << "Test #" << testNr << ": ";
        Invictus(testNr);
    }

    #ifdef LocalRun
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        cout << "\nTime taken: " << duration.count() << " seconds." << '\n';
    #endif

    return 0;
}