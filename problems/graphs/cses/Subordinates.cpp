/*
  ░█████╗░██╗░░░░░███████╗██╗░░██╗░█████╗░███╗░░██╗██████╗░██████╗░██╗░░░██╗██╗███╗░░██╗██╗░░░██╗
  ██╔══██╗██║░░░░░██╔════╝╚██╗██╔╝██╔══██╗████╗░██║██╔══██╗██╔══██╗██║░░░██║██║████╗░██║██║░░░██║
  ███████║██║░░░░░█████╗░░░╚███╔╝░███████║██╔██╗██║██║░░██║██████╔╝██║░░░██║██║██╔██╗██║╚██╗░██╔╝
  ██╔══██║██║░░░░░██╔══╝░░░██╔██╗░██╔══██║██║╚████║██║░░██║██╔══██╗██║░░░██║██║██║╚████║░╚████╔╝░
  ██║░░██║███████╗███████╗██╔╝╚██╗██║░░██║██║░╚███║██████╔╝██║░░██║╚██████╔╝██║██║░╚███║░░╚██╔╝░░
  ╚═╝░░╚═╝╚══════╝╚══════╝╚═╝░░╚═╝╚═╝░░╚═╝╚═╝░░╚══╝╚═════╝░╚═╝░░╚═╝░╚═════╝░╚═╝╚═╝░░╚══╝░░░╚═╝░░░
  They forged me in fire, they broke me in battle, yet here I rise, Invictus!

  Conquered:
    -> 26   Official Championships Problems
    -> 92   Hard Problems (Aimed to improve my skills and deep thinking)
    -> 9    Fast Training Problems (Aimed to improve my speed on easier problems)
    -> 12   Leveling Up Problems (A mix of speed and thinking, climbing the Level AK ladder)
    -> 17   Virtual Contests Problems (Aimed to simulate live performances)
    -> 90   Random Problems from different sites
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
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
   -> Debugging & Tests Generator
   ======================================================================== */
// #define DebugMode
// #define TestsGenerator
namespace Debug {
    // Flow Debug
    #ifdef DebugMode
        #include "debug/debug.hpp"
        #define debug(...) std::cerr << DebugUtil::outer << __LINE__ << \
                ": [", DebugUtil::debugImpl(#__VA_ARGS__, __VA_ARGS__)
        #define debugArr(...) std::cerr << DebugUtil::outer << __LINE__ << \
                ": [", DebugUtil::debugArrImpl(#__VA_ARGS__, __VA_ARGS__)
        #define Sdebug(...) DebugUtil::SdebugImpl(__LINE__, #__VA_ARGS__, __VA_ARGS__)
        #define SdebugArr(...) DebugUtil::SdebugArrImpl(__LINE__, #__VA_ARGS__, __VA_ARGS__)
    #else
        #define debug(...) ((void)0)
        #define debugArr(...) ((void)0)
        #define Sdebug(...) (std::string{})
        #define SdebugArr(...) (std::string{})
    #endif

    // Timer Debug
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = Clock::time_point;

    TimePoint startPrecomputation, endPrecomputation, startComputation, endComputation;

    static double getDuration(chrono::high_resolution_clock::time_point start, chrono::high_resolution_clock::time_point end) {
        return chrono::duration<double>(end - start).count();
    }

    void reset() {
        startPrecomputation = endPrecomputation = startComputation = endComputation = TimePoint{};
    }

    void startPrecomputationTimer() {
        #if defined(DebugMode) && !defined(TestsGenerator)
                startPrecomputation = chrono::high_resolution_clock::now();
        #endif
    }

    void endPrecomputationTimerAndStartComputationTimer() {
        #if defined(DebugMode) && !defined(TestsGenerator)
                endPrecomputation = chrono::high_resolution_clock::now();
                startComputation = chrono::high_resolution_clock::now();
        #endif
    }

    void endComputationTimer() {
        #if defined(DebugMode) && !defined(TestsGenerator)
                endComputation = chrono::high_resolution_clock::now();
        #endif
    }

    void debugTimings() {
        #if defined(DebugMode) && !defined(TestsGenerator)
                cout << "\n\n=================================================================\n";
                cout << "-> Precomputation Running Time:    " << getDuration(startPrecomputation, endPrecomputation) << " seconds.\n";
                cout << "-> Computation Running Time:       " << getDuration(startComputation, endComputation) << " seconds.\n";
                cout << "-> Total Running Time:             " << getDuration(startPrecomputation, endComputation) << " seconds.\n";
                cout << "=================================================================\n";
        #endif
    }
}
using namespace Debug;

/* ========================================================================
   -> Utility Functions And Structures
   ======================================================================== */
namespace Utils {
    /* ========================================================================
       -> Policy‑based ordered set and multiset
       ======================================================================== */
    namespace OrderedStructures {
        using namespace __gnu_pbds;

        template<class T, class C = std::less<T>>
        using ordered_set = tree<T, null_type, C, rb_tree_tag, tree_order_statistics_node_update>;

        template<class T, class C = std::less<T>>
        using ordered_multiset = tree<std::pair<T, int>, null_type, C, rb_tree_tag, tree_order_statistics_node_update>;
    }
    using namespace OrderedStructures;

    /* ========================================================================
       -> Custom hash for unordered containers
       ======================================================================== */
    namespace Hash {
        struct numberHash {
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
        struct pairHash {
            size_t operator()(const pair<T, U>& p) const {
                return numberHash{}(p.first ^ (numberHash{}(p.second) << 1));
            }
        };
    }
    using namespace Hash;

    /* ========================================================================
       -> Functions
       ======================================================================== */
    namespace Functions {

        namespace private_helpers {
            // Random Helpers
            std::mt19937 rng {
                static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count())
            };
        }

        // Fast IO and High Pecision
        void FastIO() {
            ios_base::sync_with_stdio(false);
            cin.tie(nullptr);
        }

        void HighPrecisionOutput() {
            cout << fixed << setprecision(17);
        }

        // Random generator
        template<typename T>
        T rnd(T x) {
            assert(x != 0);
            int sgn = x >= 0 ? 1 : -1;
            if (x < 0) x = -x;
            T result = uniform_int_distribution<T>(0, x - 1)(private_helpers::rng) * sgn;
            return result;
        }

        template<typename T>
        T rnd(T x, T y) {
            if (x > y) swap(x, y);
            T result = uniform_int_distribution<T>(x, y)(private_helpers::rng);
            return result;
        }

        // Y Combinator for recursive calls
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
        decltype(auto) y_combinator(Func&& func) {
            return y_combinator_result<std::decay_t<Func>>{std::forward<Func>(func)};
        }

        // BinPow for fast power calculation
        long long rBinPow(long long a, long long b, long long m = -1) {
            assert(b >= 0);
            if (m == -1) m = mod;
            long long  res = 1; a %= m;
            for (; b > 0; b >>= 1) {
                if (b & 1) res = res * a % m;
                a = a * a % m;
            }
            return res;
        }

        long long binPow(long long a, long long b) {
            assert(b >= 0);
            long long res = 1;
            for (; b > 0; b >>= 1) {
                if (b & 1) res = res * a;
                a *= a;
            }
            return res;
        }

        // Number Theory
        template<typename T>
        T gcd(T a, T b) {
            return b ? gcd(b, a % b) : a;
        }

        long long lcm(const long long a, const long long b) {
            return a / gcd(a, b) * b;
        }

        // Vectors Operations
        template<typename T>
        void makeUnique(vector<T>& v) {
            sort(v.begin(), v.end());
            v.erase(unique(v.begin(), v.end()), v.end());
        }

        // Bit operations
        template<typename T>
        bool hasBit(T x, int bit) {
            return ((x >> bit) & 1) != 0;
        }

        template<typename T>
        int countBits(T x) {
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
        int highestBit(T x) {
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
        int lowestBit(T x) {
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

        // Matrix
        template<typename T>
        bool inGrid(T x, T y, T n, T m = -1) {
            if (m == -1) m = n;
            return (x >= 1 && x <= n && y >= 1 && y <= m);
        }

        // Strings
        string readLine() {
            string line;
            getline(cin, line);
            return line;
        }

        vector<string> splitWords(const string& line, const string& extraDelimiters = "") {
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

        // YES / NO
        void YES() { cout << "YES\n"; }  void Yes() { cout << "Yes\n"; }  void yes() { cout << "yes\n"; }
        void NO () { cout << "NO\n"; }  void No () { cout << "No\n"; }  void no () { cout << "no\n"; }
    };
    using namespace Functions;

}
using namespace Utils;

/* ========================================================================
   -> Defines
   ======================================================================== */
namespace Define {
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
}
using namespace Define;

/* ========================================================================
   -> Templates written before
   ======================================================================== */
namespace Template {
    struct Tree {
    explicit Tree(int _n = 0) { init(_n); }

    // ----------------------------- public API ----------------------------- //
    void addEdge(int u, int v) {
        assert(!built && "addEdge() must be called before build()");
        g[u].push_back(v), g[v].push_back(u);
    }

    // build overloads – same behaviour as Ancestor
    void build(int root = 1)                              { runBuild({root}); }
    void build(const vector<int>& roots)                  { runBuild(roots); }

    void build(const vector<vector<int>>& adj)                             { g = adj; runBuild({}); }
    void build(const vector<vector<int>>& adj, int root)                  { g = adj; runBuild({root}); }
    void build(const vector<vector<int>>& adj, const vector<int>& roots)  { g = adj; runBuild(roots); }

    // classical binary‑lifting / distance queries
    int kth_ancestor(int v, int k) const { assertBuilt(); return lift(v,k); }
    int lca(int u, int v)          const { assertBuilt(); return lcaImpl(u,v); }
    int dist(int u, int v)         const {
        assertBuilt();
        int a = lcaImpl(u,v);
        return a == -1 ? -1 : depth[u] + depth[v] - 2*depth[a];
    }

    // Subtree / leaf helpers ---------------------------------------------- //
    const vector<int>& leaves()         const { assertBuilt(); return leaf_nodes; }
    int                nrLeaves()       const { assertBuilt(); return (int)leaf_nodes.size(); }
    int                subtreeSize(int v) const { assertBuilt(); return subtree_sz[v]; }
    const vector<int>& allSubtreeSizes() const { assertBuilt(); return subtree_sz; }

    /** Return *copy* of the vertices in the subtree rooted at v.  O(size). */
    vector<int> subtreeOf(int v) const {
        assertBuilt();
        if (tin[v] == -1) return {};
        return vector<int>( euler.begin() + tin[v], euler.begin() + tout[v] );
    }

    bool isAncestor(int u, int v) const {
        assertBuilt();
        return comp[u] == comp[v] && tin[u] <= tin[v] && tout[v] <= tout[u];
    }

    int rootOf(int v) const {
        assertBuilt();
        return root_of_comp[ comp[v] ];
    }

    // Re‑use --------------------------------------------------------------- //
    void reset()          { init(n); }
    void reset(int new_n) { init(new_n); }

private:
    // State ---------------------------------------------------------------- //
    int n = 0, LOG = 0;
    vector<vector<int>> g;            // adjacency list
    vector<vector<int>> up;           // up[k][v] = 2^k‑ancestor (0 ⇒ none)
    vector<int> depth;                // depth[v]
    vector<int> comp;                 // component id of v
    vector<int> root_of_comp;         // root vertex for each component

    // Euler tour / subtree data
    vector<int> tin, tout, euler;     // entry/exit positions in Euler order
    vector<int> subtree_sz;           // |subtree rooted at v|
    vector<int> leaf_nodes;           // vertices with no children

    bool built = false;

    // Initialisation ------------------------------------------------------- //
    void init(int _n) {
        n = _n;
        LOG = 32 - __builtin_clz(max(1, n)) + 1;   // smallest LOG s.t. 2^LOG ≥ n
        g.assign(n + 1, {});
        up.assign(LOG, vector<int>(n + 1, 0));
        depth.assign(n + 1, 0);
        comp.assign(n + 1, -1);
        subtree_sz.assign(n + 1, 0);
        tin.assign(n + 1, -1);
        tout.assign(n + 1, -1);
        root_of_comp.clear();
        euler.clear();
        leaf_nodes.clear();
        built = false;
    }

    // Build helpers -------------------------------------------------------- //
    void runBuild(const vector<int>& roots) {
        assert(!built && "build() called twice");
        vector<char> used_root(n + 1, 0);
        int cid = 0;

        // 1) DFS from user‑designated roots
        for (int r : roots)
            if (1 <= r && r <= n && !used_root[r] && comp[r] == -1) {
                used_root[r] = 1;
                root_of_comp.push_back(r);
                dfs(r, 0, cid++);
            }

        // 2) Any remaining vertices become roots of their own components
        for (int v = 1; v <= n; ++v)
            if (comp[v] == -1) {
                root_of_comp.push_back(v);
                dfs(v, 0, cid++);
            }

        built = true;
    }

    void dfs(int v, int p, int cid) {
        comp[v] = cid;
        up[0][v] = p;
        for (int k = 1; k < LOG; ++k)
            up[k][v] = up[k-1][v] ? up[k-1][ up[k-1][v] ] : 0;

        // Enter Euler tour
        tin[v] = (int)euler.size();
        euler.push_back(v);
        subtree_sz[v] = 1;

        int child_cnt = 0;
        for (int to : g[v]) if (to != p) {
            depth[to] = depth[v] + 1;
            dfs(to, v, cid);
            subtree_sz[v] += subtree_sz[to];
            ++child_cnt;
        }

        if (child_cnt == 0) leaf_nodes.push_back(v);

        tout[v] = (int)euler.size();   // exit Euler tour (exclusive)
    }

    // Query helpers -------------------------------------------------------- //
    int lift(int v, int k) const {
        for (int i = 0; v && k; ++i, k >>= 1)
            if (k & 1) v = up[i][v];
        return v ? v : -1;
    }

    int lcaImpl(int u, int v) const {
        if (comp[u] != comp[v]) return -1;      // different components
        if (depth[u] < depth[v]) swap(u, v);
        u = lift(u, depth[u] - depth[v]);
        if (u == v) return u;
        for (int i = LOG - 1; i >= 0; --i)
            if (up[i][u] && up[i][u] != up[i][v]) {
                u = up[i][u];
                v = up[i][v];
            }
        return up[0][u] ? up[0][u] : -1;
    }

    void assertBuilt() const { assert(built && "build() must be called first"); }
};

}
using namespace Template;

constexpr int MAXN = 2e5 + 2;



void Compute(const int testNr, const bool isLastTest) {

    int n;
    cin >> n;
    Tree tree(n);
    for (int i = 2; i <= n; ++i) {
        int x;
        cin >> x;
        tree.addEdge(x, i);
    }
    tree.build();

    for (int i = 1; i <= n; ++i) {
        cout << tree.subtreeSize(i) - 1 << " ";
    }
}

void Precompute() {}

int main() {

    FastIO();
    HighPrecisionOutput();

    int numberOfTests = 1;
    // cin >> numberOfTests;

    startPrecomputationTimer();

    Precompute();

    endPrecomputationTimerAndStartComputationTimer();

    for (int testNr = 1; testNr <= numberOfTests; ++testNr) {
        // cout << "Case #" << testNr << ": ";
        // cout << "Test #" << testNr << ": ";
        Compute(testNr, testNr == numberOfTests);
    }

    endComputationTimer();
    debugTimings();

    return 0;
}