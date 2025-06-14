/*
  ░█████╗░██╗░░░░░███████╗██╗░░██╗░█████╗░███╗░░██╗██████╗░██████╗░██╗░░░██╗██╗███╗░░██╗██╗░░░██╗
  ██╔══██╗██║░░░░░██╔════╝╚██╗██╔╝██╔══██╗████╗░██║██╔══██╗██╔══██╗██║░░░██║██║████╗░██║██║░░░██║
  ███████║██║░░░░░█████╗░░░╚███╔╝░███████║██╔██╗██║██║░░██║██████╔╝██║░░░██║██║██╔██╗██║╚██╗░██╔╝
  ██╔══██║██║░░░░░██╔══╝░░░██╔██╗░██╔══██║██║╚████║██║░░██║██╔══██╗██║░░░██║██║██║╚████║░╚████╔╝░
  ██║░░██║███████╗███████╗██╔╝╚██╗██║░░██║██║░╚███║██████╔╝██║░░██║╚██████╔╝██║██║░╚███║░░╚██╔╝░░
  ╚═╝░░╚═╝╚══════╝╚══════╝╚═╝░░╚═╝╚═╝░░╚═╝╚═╝░░╚══╝╚═════╝░╚═╝░░╚═╝░╚═════╝░╚═╝╚═╝░░╚══╝░░░╚═╝░░░
  They forged me in fire, they broke me in battle, yet here I rise, Invictus!
*/

// Link: https://infoarena.ro/problema/dijkstra
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

constexpr int mod = 1000000007;
// constexpr int mod = 998244353;

/* ========================================================================
   -> Read from file
   ======================================================================== */
ifstream fin("dijkstra.in");
ofstream fout("dijkstra.out");
#define cin fin
#define cout fout

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
struct Dijkstra {
    using ll = long long;
    static constexpr ll INF = std::numeric_limits<ll>::max() / 4;   // safe sentinel

    bool direct;
    /* ── construction ───────────────────────────────────────────── */
    explicit Dijkstra(int _n = 0, bool _direct = false) { init(_n, _direct); }

    /* ── edge insertion ─────────────────────────────────────────── */
    void addEdge(int u, int v, ll w) {
        assert(!ran && "addEdge() must precede run()");
        g[u].push_back({v, w});
        if (!direct) g[v].push_back({u, w});
    }

    /* ── run Dijkstra ───────────────────────────────────────────── */
    void run(int src = 1)                          { run(vector<int>{src}); }
    void run(const vector<int>& srcs) {
        assert(!ran && "run() called twice; call reset() first");
        prepare();
        using State = pair<ll,int>;
        priority_queue<State, vector<State>, greater<State>> pq;

        for (int s : srcs) if (validVertex(s)) {
            dist_[s] = 0;
            pq.push({0, s});
        }
        while (!pq.empty()) {
            auto [du, u] = pq.top(); pq.pop();
            if (du != dist_[u]) continue;          // stale entry
            for (auto [v, w] : g[u])
                if (dist_[v] > du + w) {
                    dist_[v] = du + w;
                    parent_[v] = u;
                    pq.push({dist_[v], v});
                }
        }
        ran = true;
    }

    /* overloads that accept a ready adjacency list */
    void run(const vector<vector<pair<int,ll>>>& adj, int src)              { g = adj; run(src); }
    void run(const vector<vector<pair<int,ll>>>& adj, const vector<int>& s) { g = adj; run(s);   }

    /* ── queries ────────────────────────────────────────────────── */
    /** shortest distance or −1 if unreachable */
    ll dist(int v) const { assertRan(); return dist_[v] == INF ? -1 : dist_[v]; }

    /** vector with −1 for unreachable vertices */
    vector<ll> distVector() const {
        assertRan();
        vector<ll> out(dist_.size());
        for (size_t i = 1; i < dist_.size(); ++i)
            out[i] = (dist_[i] == INF ? -1 : dist_[i]);
        return out;
    }

    /** one shortest path (empty if unreachable) */
    vector<int> path(int v) const {
        assertRan();
        if (dist_[v] == INF) return {};
        vector<int> p;
        while (v) { p.push_back(v); v = parent_[v]; }
        reverse(p.begin(), p.end());
        return p;
    }

    /* ── reuse across test cases ───────────────────────────────── */
    void reset(bool _direct = false)          { init(n, _direct); }
    void reset(int new_n, bool _direct = false) { init(new_n, _direct); }

private:
    int n = 0;
    vector<vector<pair<int,ll>>> g;   // adjacency list
    vector<ll>  dist_;
    vector<int> parent_;
    bool ran = false;

    /* ── helpers ───────────────────────────────────────────────── */
    void init(int _n, bool _direct) {
        n = _n;
        direct = _direct;
        g.assign(n + 1, {});
        dist_.assign(n + 1, INF);
        parent_.assign(n + 1, 0);
        ran = false;
    }
    void prepare() {
        fill(dist_.begin(),   dist_.end(),   INF);
        fill(parent_.begin(), parent_.end(), 0);
    }
    bool validVertex(int v) const { return 1 <= v && v <= n; }
    void assertRan()       const { assert(ran && "run() must be called first"); }
};
/* ========================================================================
   -> Templates End
   ======================================================================== */

constexpr int MAXN = 2e5 + 2;



void CoreCompute(const int testIdx, const bool isLastTest) {

    int n, m, p;
    cin >> n >> m;
    Dijkstra dijkstra = Dijkstra(n, true);
    for (int i = 1; i <= m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        dijkstra.addEdge(u, v, w);
    }
    dijkstra.run();
    auto res = dijkstra.distVector();
    for (int i = 2; i <= n; ++i) {
        if (res[i] == -1) res[i] = 0;
        cout << res[i] << " ";
    }
    cout << '\n';

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
