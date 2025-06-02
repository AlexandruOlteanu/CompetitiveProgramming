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

/* ------------------------------------------------------------------------
   Local Run Time and Debugging
------------------------------------------------------------------------ */
// #define DebugMode
// #define Generator
#if defined(DebugMode) && ! defined(Generator)
    #include "debug.hpp"
    #define dbg(...) std::cerr << __DEBUG_UTIL__::outer << __LINE__ << ": [", __DEBUG_UTIL__::printer(#__VA_ARGS__, __VA_ARGS__)
    #define dbgArr(...) std::cerr << __DEBUG_UTIL__::outer << __LINE__ << ": [", __DEBUG_UTIL__::printerArr(#__VA_ARGS__, __VA_ARGS__)
#else
    #define dbg(...) ((void)0)
    #define dbgArr(...) ((void)0)
#endif

/* ------------------------------------------------------------------------
   Policy‑based ordered set shortcut
------------------------------------------------------------------------ */
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template<typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

/* ------------------------------------------------------------------------
   RNG & custom hash for unordered containers
------------------------------------------------------------------------ */
mt19937 rng(static_cast<unsigned int>(chrono::steady_clock::now().time_since_epoch().count()));

struct number_hash {
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

template<typename T, typename U>
struct pair_hash {
    size_t operator()(const pair<T, U>& p) const {
        return number_hash{}(p.first ^ (number_hash{}(p.second) << 1));
    }
};

/* ------------------------------------------------------------------------
   Helper functions
------------------------------------------------------------------------ */
long long mypowr(long long a, long long b, const long long m = 1000000007) {
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

template<typename T>
T add_m(T a, T b, int mod = 1000000007) {
    return (a + b) % mod;
}

template<typename T>
T mul_m(T a, T b, int mod = 1000000007) {
    return (static_cast<long long>(a) * b) % mod;
}

template<typename T>
T gcd(T a, T b) {
    return b ? gcd(b, a % b) : a;
}

long long lcm(const long long a, const long long b) {
    return a / gcd(a, b) * b;
}

template<typename T>
T div_m(T a, T b, int mod = 1000000007) {
    T inv = mypowr(b, mod - 2, mod);
    return mul_m(a, inv, mod);
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
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using ll  = long long;
using pii = pair<int, int>;
constexpr int mod   = 1000000007;
constexpr int mod1  = 998244353;
constexpr pair<int, int> dir4[] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
constexpr pair<int, int> dir8[] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
constexpr long long infbig = numeric_limits<long long> :: max();
constexpr int inf = numeric_limits<int> :: max();

// ifstream fin("input.in");
// ofstream fout("output.out");
// #define cin fin
// #define cout fout

constexpr int MAXN = 2e5 + 2;



void CoreCompute(const int currentTestNumber) {



}

void Precompute() {}

int main() {

    LightningFastReadWrite
    RealValuesHighPrecision

    int numberOfTests = 1;
    cin >> numberOfTests;

    #if defined(DebugMode) && ! defined(Generator)
        const auto startPrecomputation = chrono::high_resolution_clock::now();
    #endif

    Precompute();

    #if defined(DebugMode) && ! defined(Generator)
        const auto endPrecompute = chrono::high_resolution_clock::now();
        const chrono::duration<double> precomputationDuration = endPrecompute - startPrecomputation;
        const auto startCoreComputation = chrono::high_resolution_clock::now();
    #endif

    for (int currentTestNumber = 1; currentTestNumber <= numberOfTests; ++currentTestNumber) {
        // cout << "Case #" << currentTestNumber << ": ";
        // cout << "Test #" << currentTestNumber << ": ";
        CoreCompute(currentTestNumber);
    }

    #if defined(DebugMode) && ! defined(Generator)
        cout << "\nPrecomputation Running Time:    " << precomputationDuration.count() << " seconds." << '\n';
        const auto endCoreComputation = chrono::high_resolution_clock::now();
        const chrono::duration<double> coreComputationDuration = endCoreComputation - startCoreComputation;
        cout << "Core Computation Running Time:  " << coreComputationDuration.count() << " seconds." << "\n";
        const chrono::duration<double> totalComputationDuration = endCoreComputation - startPrecomputation;
        cout << "Total Computation Running Time: " << totalComputationDuration.count() << " seconds." << "\n\n";
    #endif

    return 0;
}
