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

// Link: https://www.pbinfo.ro/probleme/852/paranteze3

constexpr int mod = 1000000007;
// constexpr int mod = 998244353;

/* ========================================================================
   -> Local Run Time and Debugging
   ======================================================================== */
// #define DebugMode
// #define Generator
#if defined(DebugMode) && !defined(Generator)
    #include "debug.hpp"
    #define dbg(...) std::cerr << __DEBUG_UTIL__::outer << __LINE__ << \
                     ": [", __DEBUG_UTIL__::printer(#__VA_ARGS__, __VA_ARGS__)
    #define dbgArr(...) std::cerr << __DEBUG_UTIL__::outer << __LINE__ << \
                     ": [", __DEBUG_UTIL__::printerArr(#__VA_ARGS__, __VA_ARGS__)
#else
    #define dbg(...) ((void)0)
    #define dbgArr(...) ((void)0)
#endif

/* ========================================================================
   -> Policy‑based ordered set shortcut
   ======================================================================== */
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template<typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

/* ========================================================================
   -> RNG & custom hash for unordered containers
   ======================================================================== */
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

/* ========================================================================
   -> Helper functions
   ======================================================================== */
long long mypowr(long long a, long long b, long long m = -1) {
    if (m == -1) m = mod;
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
T gcd(T a, T b) {
    return b ? gcd(b, a % b) : a;
}

long long lcm(const long long a, const long long b) {
    return a / gcd(a, b) * b;
}

template<typename T>
void make_unique(std::vector<T>& v) {
    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());
}

void YES() { cout << "YES\n"; }  void Yes() { cout << "Yes\n"; }  void yes() { cout << "yes\n"; }
void NO () { cout << "NO\n"; }  void No () { cout << "No\n"; }  void no () { cout << "no\n"; }

/* ========================================================================
   -> Defines
   ======================================================================== */
#define LightningFastReadWrite ios_base::sync_with_stdio(false); cin.tie(nullptr);
#define RealValuesHighPrecision cout << fixed << setprecision(17);
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using ll  = long long;
using pii = pair<int, int>;
constexpr pair<int, int> dir4[] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
constexpr pair<int, int> dir8[] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
constexpr long long infBig = numeric_limits<long long> :: max();
constexpr long long infMid = 1e15;
constexpr int inf = numeric_limits<int> :: max();
constexpr int infSmall = 1e9;

/* ========================================================================
   -> Templates Start
   ======================================================================== */

/* ========================================================================
   -> Templates End
   ======================================================================== */

ifstream fin("paranteze3.in");
ofstream fout("paranteze3.out");
#define cin fin
#define cout fout

constexpr int MAXN = 2e5 + 2;



void CoreCompute(const int currentTestNumber) {

    string s;
    cin >> s;
    vector<int> v;
    for (auto x : s) {
        int val = 0;
        if (x == '(') val = 1;
        else if (x == '[') val = 2;
        if (val != 0) {
            v.push_back(val);
            continue;
        }
        if (x == ')') val = 1;
        else val = 2;
        if (v.empty() || v.back() != val) {
            cout << "0\n";
            return;
        }
        v.pop_back();
    }
    if (!v.empty()) {
        cout << "0\n";
        return;
    }
    cout << "1\n";
}

void Precompute() {}

int main() {

    LightningFastReadWrite
    RealValuesHighPrecision

    int numberOfTests = 1;
    cin >> numberOfTests;

    #if defined(DebugMode) && !defined(Generator)
        const auto startPrecomputation = chrono::high_resolution_clock::now();
    #endif

    Precompute();

    #if defined(DebugMode) && !defined(Generator)
        const auto endPrecompute = chrono::high_resolution_clock::now();
        const chrono::duration<double> precomputationDuration = endPrecompute - startPrecomputation;
        const auto startCoreComputation = chrono::high_resolution_clock::now();
    #endif

    for (int currentTestNumber = 1; currentTestNumber <= numberOfTests; ++currentTestNumber) {
        // cout << "Case #" << currentTestNumber << ": ";
        // cout << "Test #" << currentTestNumber << ": ";
        CoreCompute(currentTestNumber);
    }

    #if defined(DebugMode) && !defined(Generator)
        cout << "\n\n=================================================================\n";
        cout << "-> Precomputation Running Time:    " << precomputationDuration.count() << " seconds." << '\n';
        const auto endCoreComputation = chrono::high_resolution_clock::now();
        const chrono::duration<double> coreComputationDuration = endCoreComputation - startCoreComputation;
        cout << "-> Core Computation Running Time:  " << coreComputationDuration.count() << " seconds." << "\n";
        const chrono::duration<double> totalComputationDuration = endCoreComputation - startPrecomputation;
        cout << "-> Total Computation Running Time: " << totalComputationDuration.count() << " seconds." << "\n";
        cout << "=================================================================\n";
    #endif

    return 0;
}