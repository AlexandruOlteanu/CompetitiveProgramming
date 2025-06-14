/*
  ░█████╗░██╗░░░░░███████╗██╗░░██╗░█████╗░███╗░░██╗██████╗░██████╗░██╗░░░██╗██╗███╗░░██╗██╗░░░██╗
  ██╔══██╗██║░░░░░██╔════╝╚██╗██╔╝██╔══██╗████╗░██║██╔══██╗██╔══██╗██║░░░██║██║████╗░██║██║░░░██║
  ███████║██║░░░░░█████╗░░░╚███╔╝░███████║██╔██╗██║██║░░██║██████╔╝██║░░░██║██║██╔██╗██║╚██╗░██╔╝
  ██╔══██║██║░░░░░██╔══╝░░░██╔██╗░██╔══██║██║╚████║██║░░██║██╔══██╗██║░░░██║██║██║╚████║░╚████╔╝░
  ██║░░██║███████╗███████╗██╔╝╚██╗██║░░██║██║░╚███║██████╔╝██║░░██║╚██████╔╝██║██║░╚███║░░╚██╔╝░░
  ╚═╝░░╚═╝╚══════╝╚══════╝╚═╝░░╚═╝╚═╝░░╚═╝╚═╝░░╚══╝╚═════╝░╚═╝░░╚═╝░╚═════╝░╚═╝╚═╝░░╚══╝░░░╚═╝░░░
  They forged me in fire, they broke me in battle, yet here I rise, Invictus!
*/

// Link: https://infoarena.ro/problema/stramosi
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

constexpr int mod = 1000000007;
// constexpr int mod = 998244353;

/* ========================================================================
   -> Read from file
   ======================================================================== */
// ifstream fin("input.in");
// ofstream fout("output.out");
// #define cin fin
// #define cout fout

/* ========================================================================
   -> Local Run Time and Debugging
   ======================================================================== */
// #define DebugMode
// #define Generator
#if defined(DebugMode) && !defined(Generator)
    #include "debug/debug.hpp"
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
   -> Functions
   ======================================================================== */
struct func {

    static void FastIO() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
    }

    static void HighPrecisionOutput() {
        cout << fixed << setprecision(17);
    }

    template <typename Func>
    struct y_combinator_result {
        Func func;
        template <typename... Args>
        decltype(auto) operator()(Args&&... args) {
            return func(*this, std::forward<Args>(args)...);
        }
    };
    //Usage: auto func_name = y_combinator([](auto self, int param1, int param2 ...) -> return_type {  code; });
    template <typename Func>
    static decltype(auto) y_combinator(Func&& func) {
        return y_combinator_result<std::decay_t<Func>>{std::forward<Func>(func)};
    }

    static long long RmyPow(long long a, long long b, long long m = -1) {
        assert(b >= 0);
        if (m == -1) m = mod;
        long long  res = 1; a %= m;
        for (; b > 0; b >>= 1) {
            if (b & 1) res = res * a % m;
            a = a * a % m;
        }
        return res;
    }

    static long long myPow(long long a, long long b) {
        assert(b >= 0);
        long long res = 1;
        for (; b > 0; b >>= 1) {
            if (b & 1) res = res * a;
            a *= a;
        }
        return res;
    }

    template<typename T>
    static T gcd(T a, T b) {
        return b ? gcd(b, a % b) : a;
    }

    static long long lcm(const long long a, const long long b) {
        return a / gcd(a, b) * b;
    }

    template<typename T>
    static void makeUnique(vector<T>& v) {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }

    template<typename T>
    static bool hasBit(T x, int bit) {
        return ((x >> bit) & 1) != 0;
    }

    template<typename T>
    static int countBits(T x) {
        if constexpr (is_same_v<T, int>) {
            return __builtin_popcount(x);
        } else if constexpr (is_same_v<T, long long>) {
            return __builtin_popcountll(x);
        } else {
            static_assert(is_integral_v<T>, "countBits requires an integral type");
            return __builtin_popcountll(static_cast<long long>(x)); // fallback
        }
    }

    template<typename T>
    static int highestBit(T x) {
        if (x == 0) return -1;
        if constexpr (is_same_v<T, int>) {
            return 31 - __builtin_clz(x);
        } else if constexpr (is_same_v<T, long long>) {
            return 63 - __builtin_clzll(x);
        } else {
            static_assert(is_integral_v<T>, "highestBit requires an integral type");
            return 63 - __builtin_clzll(static_cast<long long>(x));
        }
    }

    template<typename T>
    static int lowestBit(T x) {
        if (x == 0) return -1;
        if constexpr (is_same_v<T, int>) {
            return __builtin_ctz(x);
        } else if constexpr (is_same_v<T, long long>) {
            return __builtin_ctzll(x);
        } else {
            static_assert(is_integral_v<T>, "lowestBit requires an integral type");
            return __builtin_ctzll(static_cast<long long>(x));
        }
    }

    template<typename T>
    static bool inGrid(T x, T y, T n, T m = -1) {
        if (m == -1) m = n;
        return (x >= 1 && x <= n && y >= 1 && y <= m);
    }

    static string readLine() {
        string line;
        getline(cin, line);
        return line;
    }

    static vector<string> splitWords(const string& line, const string& extraDelimiters = "") {
        const unordered_set<char> delimiters(extraDelimiters.begin(), extraDelimiters.end());
        vector<string> words;
        string current;

        for (char ch : line) {
            if (isalnum(ch)) {
                current += ch;
            } else if (!current.empty() && (isspace(ch) || delimiters.count(ch) || !isalnum(ch))) {
                words.push_back(current);
                current.clear();
            }
        }

        if (!current.empty()) {
            words.push_back(current);
        }

        return words;
    }
};

void YES() { cout << "YES\n"; }  void Yes() { cout << "Yes\n"; }  void yes() { cout << "yes\n"; }
void NO () { cout << "NO\n"; }  void No () { cout << "No\n"; }  void no () { cout << "no\n"; }

/* ========================================================================
   -> Defines
   ======================================================================== */
#define all(x) (x).begin(), (x).end()
#define all1(x) ++(x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define rall1(x) (x).rbegin(), --(x).rend()
using ll  = long long;
using pii = pair<int, int>;
constexpr pair<int, int> dir4[] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
constexpr pair<int, int> dir8[] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
constexpr pair<int, int> dirDiag[] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
constexpr long long infBig = numeric_limits<long long> :: max() - 23;
constexpr long long infMid = 1e15;
constexpr int inf = numeric_limits<int> :: max() - 23;
constexpr int infSmall = 1e9;

/* ========================================================================
   -> Templates Start
   ======================================================================== */
struct Ancestor {
    explicit Ancestor(int _n) { init(_n); }

    /* --------- add edges one by one --------- */
    void addEdge(int u, int v) {
        assert(!built && "addEdge() must be called before build()");
        g[u].push_back(v), g[v].push_back(u);
    }

    /* --------- build(): three overloads --------- */
    void build(int root = 1)               { runBuild({root}); }      // one root
    void build(const vector<int>& roots)   { runBuild(roots); }       // many

    /* adjacency-list versions */
    void build(const vector<vector<int>>& adj)                { g = adj; runBuild({}); }
    void build(const vector<vector<int>>& adj, int root)      { g = adj; runBuild({root}); }
    void build(const vector<vector<int>>& adj,
               const vector<int>& roots)                      { g = adj; runBuild(roots); }

    /* --------- queries --------- */
    int kth_ancestor(int v, int k) const { assertBuilt(); return lift(v,k); }
    int lca(int u, int v)          const { assertBuilt(); return lcaImpl(u,v); }
    int dist(int u, int v)         const { assertBuilt();
        int a = lcaImpl(u,v);
        return a == -1 ? -1 : depth[u] + depth[v] - 2*depth[a];
    }

    /* --------- reuse --------- */
    void reset()          { init(n); }
    void reset(int new_n) { init(new_n); }

private:
    /* --------- state --------- */
    int n{}, LOG{};
    vector<vector<int>> up;     // up[k][v] = 2^k-th ancestor (0 ⇒ none)
    vector<int> depth;          // depth[v]
    vector<vector<int>> g;      // adjacency list
    vector<int> comp;           // component id
    bool built = false;

    /* --------- init --------- */
    void init(int _n) {
        n = _n;
        LOG = 32 - __builtin_clz(max(1, n)) + 1;   // 2^LOG ≥ n
        up.assign(LOG, vector<int>(n + 1, 0));
        depth.assign(n + 1, 0);
        g.assign(n + 1, {});
        comp.assign(n + 1, -1);
        built = false;
    }

    /* --------- build internals --------- */
    void runBuild(const vector<int>& roots) {
        assert(!built && "build() called twice");

        vector<char> used_root(n + 1, 0);
        int cid = 0;

        /* 1. DFS from every user-supplied root (ignore duplicates / wrong ids) */
        for (int r : roots)
            if (1 <= r && r <= n && !used_root[r] && comp[r] == -1) {
                used_root[r] = 1;
                dfs(r, 0, cid++);
            }

        /* 2. finish remaining components with arbitrary roots */
        for (int v = 1; v <= n; ++v)
            if (comp[v] == -1) dfs(v, 0, cid++);

        built = true;
    }

    void dfs(int v, int p, int cid) {
        comp[v] = cid;
        up[0][v] = p;
        for (int k = 1; k < LOG; ++k)
            up[k][v] = up[k-1][v] ? up[k-1][ up[k-1][v] ] : 0;
        for (int to : g[v]) if (to != p) {
            depth[to] = depth[v] + 1;
            dfs(to, v, cid);
        }
    }

    /* --------- query helpers --------- */
    int lift(int v, int k) const {
        for (int i = 0; v && k; ++i, k >>= 1)
            if (k & 1) v = up[i][v];
        return v ? v : -1;
    }

    int lcaImpl(int u, int v) const {
        if (comp[u] != comp[v]) return -1;
        if (depth[u] < depth[v]) swap(u,v);
        u = lift(u, depth[u] - depth[v]);
        if (u == v) return u;
        for (int i = LOG-1; i >= 0; --i)
            if (up[i][u] && up[i][u] != up[i][v])
                u = up[i][u], v = up[i][v];
        return up[0][u] ? up[0][u] : -1;
    }

    void assertBuilt() const { assert(built && "build() must be called first"); }
};

/* ========================================================================
   -> Templates End
   ======================================================================== */

constexpr int MAXN = 2e5 + 2;



void CoreCompute(const int testIdx, const bool isLastTest) {

    int n, q;
    cin >> n >> q;
    Ancestor ancestor(n);
    vector<int> roots;
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        if (x == 0) {
            roots.push_back(i);
            continue;
        }
        ancestor.addEdge(i, x);
    }

    ancestor.build(roots);
    while (q--) {
        int k, x;
        cin >> x >> k;
        int r = ancestor.kth_ancestor(x, k);
        if (r == -1) r = 0;
        cout << r << '\n';
    }

}

void Precompute() {}

int main() {

    func::FastIO();
    func::HighPrecisionOutput();

    int numberOfTests = 1;
    // cin >> numberOfTests;

    #if defined(DebugMode) && !defined(Generator)
        const auto startPrecomputation = chrono::high_resolution_clock::now();
    #endif

    Precompute();

    #if defined(DebugMode) && !defined(Generator)
        const auto endPrecompute = chrono::high_resolution_clock::now();
        const chrono::duration<double> precomputationDuration = endPrecompute - startPrecomputation;
        const auto startCoreComputation = chrono::high_resolution_clock::now();
    #endif

    for (int testIdx = 1; testIdx <= numberOfTests; ++testIdx) {
        // cout << "Case #" << testIdx << ": ";
        // cout << "Test #" << testIdx << ": ";
        CoreCompute(testIdx, testIdx == numberOfTests);
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
