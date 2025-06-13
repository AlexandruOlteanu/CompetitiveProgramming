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

// Link: https://infoarena.ro/problema/datorii
constexpr int mod = 1000000007;
// constexpr int mod = 998244353;

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
    static void makeUnique(std::vector<T>& v) {
        std::sort(v.begin(), v.end());
        v.erase(std::unique(v.begin(), v.end()), v.end());
    }

    template<typename T>
    static bool hasBit(T x, int bit) {
        return ((x >> bit) & 1) != 0;
    }

    template<typename T>
    static int countBits(T x) {
        if constexpr (std::is_same_v<T, int>) {
            return __builtin_popcount(x);
        } else if constexpr (std::is_same_v<T, long long>) {
            return __builtin_popcountll(x);
        } else {
            static_assert(std::is_integral_v<T>, "countBits requires an integral type");
            return __builtin_popcountll(static_cast<long long>(x)); // fallback
        }
    }

    template<typename T>
    static int highestBit(T x) {
        if (x == 0) return -1;
        if constexpr (std::is_same_v<T, int>) {
            return 31 - __builtin_clz(x);
        } else if constexpr (std::is_same_v<T, long long>) {
            return 63 - __builtin_clzll(x);
        } else {
            static_assert(std::is_integral_v<T>, "highestBit requires an integral type");
            return 63 - __builtin_clzll(static_cast<long long>(x));
        }
    }

    template<typename T>
    static int lowestBit(T x) {
        if (x == 0) return -1;
        if constexpr (std::is_same_v<T, int>) {
            return __builtin_ctz(x);
        } else if constexpr (std::is_same_v<T, long long>) {
            return __builtin_ctzll(x);
        } else {
            static_assert(std::is_integral_v<T>, "lowestBit requires an integral type");
            return __builtin_ctzll(static_cast<long long>(x));
        }
    }

    template<typename T>
    static bool inGrid(T x, T y, T n, T m = -1) {
        if (m == -1) m = n;
        return (x >= 1 && x <= n && y >= 1 && y <= m);
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
        res = x;
        res.val += y.val;
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
/* ========================================================================
   -> Templates End
   ======================================================================== */

ifstream fin("datorii.in");
ofstream fout("datorii.out");
#define cin fin
#define cout fout

constexpr int MAXN = 2e5 + 2;



void CoreCompute(const int testIdx, const bool isLastTest) {

    int n, q;
    cin >> n >> q;
    SegmentTree<int> st(n);
    for (int i = 1; i <= n; ++i) {
        cin >> st.array[i].val;
    }

    st.build(1, n);

    while (q--) {
        int p, x, y;
        cin >> p >> x >> y;
        if (p == 0) {
            st.update(x, x, {-y});
        } else {
            cout << st.get(x, y).val << "\n";
        }
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
