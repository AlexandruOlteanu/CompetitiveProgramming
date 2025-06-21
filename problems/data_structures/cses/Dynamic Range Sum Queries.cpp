/*
  ░█████╗░██╗░░░░░███████╗██╗░░██╗░█████╗░███╗░░██╗██████╗░██████╗░██╗░░░██╗██╗███╗░░██╗██╗░░░██╗
  ██╔══██╗██║░░░░░██╔════╝╚██╗██╔╝██╔══██╗████╗░██║██╔══██╗██╔══██╗██║░░░██║██║████╗░██║██║░░░██║
  ███████║██║░░░░░█████╗░░░╚███╔╝░███████║██╔██╗██║██║░░██║██████╔╝██║░░░██║██║██╔██╗██║╚██╗░██╔╝
  ██╔══██║██║░░░░░██╔══╝░░░██╔██╗░██╔══██║██║╚████║██║░░██║██╔══██╗██║░░░██║██║██║╚████║░╚████╔╝░
  ██║░░██║███████╗███████╗██╔╝╚██╗██║░░██║██║░╚███║██████╔╝██║░░██║╚██████╔╝██║██║░╚███║░░╚██╔╝░░
  ╚═╝░░╚═╝╚══════╝╚══════╝╚═╝░░╚═╝╚═╝░░╚═╝╚═╝░░╚══╝╚═════╝░╚═╝░░╚═╝░╚═════╝░╚═╝╚═╝░░╚══╝░░░╚═╝░░░
  They forged me in fire, they broke me in battle, yet here I rise, Invictus!

  Conquered:
    -> 23   Official Championships Problems
    -> 92   Hard Problems (Aimed to improve my skills and deep thinking)
    -> 9    Fast Training Problems (Aimed to improve my speed on easier problems)
    -> 12   Leveling Up Problems (A mix of speed and thinking, climbing the Level AK ladder)
    -> 17   Virtual Contests Problems (Aimed to simulate live performances)
    -> 89   Random Problems from different sites
*/

// Link: https://cses.fi/problemset/task/1648/
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
   -> Local Run Time and Debugging
   ======================================================================== */
// #define DebugMode
// #define Generator
namespace Debug {
    #ifdef DebugMode
        #include "debug/debug.hpp"
        #define dbg(...) std::cerr << __DEBUG_UTIL__::outer << __LINE__ << \
                    ": [", __DEBUG_UTIL__::printer(#__VA_ARGS__, __VA_ARGS__)
        #define dbgArr(...) std::cerr << __DEBUG_UTIL__::outer << __LINE__ << \
                    ": [", __DEBUG_UTIL__::printerArr(#__VA_ARGS__, __VA_ARGS__)
    #else
        #define dbg(...) ((void)0)
        #define dbgArr(...) ((void)0)
    #endif
}
using namespace Debug;

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

namespace Template {
    // https://github.com/AlexandruOlteanu/CompetitiveProgramming/blob/main/template/Segment%20Tree/SegmentTree.cpp
template<typename A>
struct SegmentTree {
    struct TreeNode {
        A val;
    };

    int N;
    vector<TreeNode> array, tree, lazy;
    vector<bool> lazyStatus;

    SegmentTree(int n) {
        reset(n);
    }

    void reset(int n) {
        N = n;
        array.assign(N + 1, defaultTreeNode());
        tree .assign(4 * (N + 1), defaultTreeNode());
        lazy .assign(4 * (N + 1), defaultTreeNode());
        lazyStatus.assign(4 * (N + 1), false);
    }

    void build(int start, int end, int operation = 1) {
        buildX(1, start, end, operation, 1);
    }

    void update(int start, int end, TreeNode value, int operation = 1) {
        updateX(1, 1, N, start, end, value, operation, 1);
    }

    TreeNode getWithExcludedIndices(int start, int end, vector<int> excluded, int operation = 1) {
        excluded.erase(remove_if(excluded.begin(), excluded.end(),
                                  [&](int p) { return p < start || p > end; }),
                                  excluded.end());

        sort(excluded.begin(), excluded.end());
        excluded.erase(unique(excluded.begin(), excluded.end()), excluded.end());

        TreeNode res = defaultTreeNode();
        int curL = start;

        for (int p : excluded) {
            int curR = p - 1;
            if (curL <= curR) {
                TreeNode chunk = get(curL, curR, operation);
                res = applyFunction(res, chunk, operation);
            }
            curL = p + 1;
        }

        if (curL <= end) {
            TreeNode chunk = get(curL, end, operation);
            res = applyFunction(res, chunk, operation);
        }
        return res;
    }

    TreeNode get(int start, int end, int operation = 1) {
        return getX(1, 1, N, start, end, operation, 1);
    }

    // Things you may need to change
    TreeNode applyFunction(TreeNode x, TreeNode y, int operation) {
        if (operation == 1) return function1(x, y);
        if (operation == 2) return function2(x, y);
        return TreeNode();
    }

    TreeNode function1(TreeNode x, TreeNode y) {
        TreeNode res;
        res.val = x.val + y.val;
        return res;
    }

    TreeNode function2(TreeNode x, TreeNode y) {
        TreeNode res;
        res.val = max(x.val, y.val);
        return res;
    }

    TreeNode applyUpdateFunction(TreeNode x, TreeNode y) {
        TreeNode res;
        res = y;
        return res;
    }

    TreeNode defaultTreeNode() {
        TreeNode res;
        res.val = 0;
        return res;
    }

    int changeOperationAfterLevel(int level, int operation) {
        return operation;
    }
    // End of things you may need to change
private:
    void push(int node, int l, int r, int operation) {
        if (!lazyStatus[node]) return;
        tree[node] = applyUpdateFunction(tree[node], lazy[node]);
        if (l != r) {
            lazy[node * 2] = applyUpdateFunction(lazy[node * 2], lazy[node]);
            lazy[node * 2 + 1] = applyUpdateFunction(lazy[node * 2 + 1], lazy[node]);
            lazyStatus[node * 2] = lazyStatus[node * 2 + 1] = true;
        }
        lazy[node] = defaultTreeNode();
        lazyStatus[node] = false;
    }

    void buildX(int node, int l, int r, int operation, int level) {
        if (l == r) { tree[node] = array[l]; return; }
        int mid = (l + r) >> 1;
        int nextOp = changeOperationAfterLevel(level, operation);
        buildX(node * 2, l, mid, nextOp, level + 1);
        buildX(node * 2 + 1, mid + 1, r, nextOp, level + 1);
        tree[node] = applyFunction(tree[node * 2], tree[node * 2 + 1], operation);
    }

    void updateX(int node, int l, int r, int L, int R, TreeNode val, int operation, int level) {
        push(node, l, r, operation);
        if (r < L || l > R) return;
        if (l >= L && r <= R) {
            lazy[node] = applyUpdateFunction(lazy[node], val);
            lazyStatus[node] = true;
            push(node, l, r, operation);
            return;
        }
        int mid = (l + r) >> 1;
        int nextOp = changeOperationAfterLevel(level, operation);
        updateX(node * 2, l, mid, L, R, val, nextOp, level + 1);
        updateX(node * 2 + 1, mid + 1, r, L, R, val, nextOp, level + 1);
        tree[node] = applyFunction(tree[node * 2], tree[node * 2 + 1], operation);
    }

    TreeNode getX(int node, int l, int r, int L, int R, int operation, int level) {
        push(node, l, r, operation);
        if (r < L || l > R) {
            return defaultTreeNode();
        }
        if (l >= L && r <= R) return tree[node];
        int mid = l + (r - l) / 2;
        int nextOp = changeOperationAfterLevel(level, operation);
        if (mid < L)  return getX(node * 2 + 1, mid + 1, r, L, R, nextOp, level + 1);
        if (mid >= R) return getX(node * 2, l, mid, L, R, nextOp, level + 1);
        return applyFunction(
            getX(node * 2, l,     mid, L, R, nextOp, level + 1),
            getX(node * 2 + 1, mid + 1, r, L, R, nextOp, level + 1),
            operation
        );
    }
};
}
using namespace Template;

constexpr int MAXN = 2e5 + 2;



void Compute(const int testId, const bool isLastTest) {

    int n, q;
    cin >> n >> q;
    SegmentTree<ll> seg(n);
    for (int i = 1; i <= n; ++i) {
        cin >> seg.array[i].val;
    }

    seg.build(1, n);
    while (q--) {
        int p, x, y;
        cin >> p >> x >> y;
        if (p == 1) {
            seg.update(x, x, {y});
        } else {
            cout << seg.get(x, y).val << '\n';
        }
    }
}

void Precompute() {}

// #define ComputeMultipleTests
int main() {

    FastIO();
    HighPrecisionOutput();

    int numberOfTests = 1;
    #ifdef ComputeMultipleTests
        cin >> numberOfTests;
    #endif

    #if defined(DebugMode) && !defined(Generator)
        auto getDuration = [] (auto start, auto end) {return chrono::duration<double>(end - start).count();};
        const auto startPrecomputation = chrono::high_resolution_clock::now();
    #endif

    Precompute();

    #if defined(DebugMode) && !defined(Generator)
        const auto endPrecomputation = chrono::high_resolution_clock::now();
        const auto startComputation = endPrecomputation;
    #endif

    for (int testId = 1; testId <= numberOfTests; ++testId) {
        // cout << "Case #" << testId << ": ";
        // cout << "Test #" << testId << ": ";
        Compute(testId, testId == numberOfTests);
    }

    #if defined(DebugMode) && !defined(Generator)
        const auto endComputation = chrono::high_resolution_clock::now();
        cout << "\n\n=================================================================\n";
        cout << "-> Precomputation Running Time:    " << getDuration(startPrecomputation, endPrecomputation) << " seconds." << '\n';
        cout << "-> Computation Running Time:       " << getDuration(startComputation, endComputation) << " seconds." << "\n";
        cout << "-> Total Computation Running Time: " << getDuration(startPrecomputation, endComputation) << " seconds." << "\n";
        cout << "=================================================================\n";
    #endif

    return 0;
}
