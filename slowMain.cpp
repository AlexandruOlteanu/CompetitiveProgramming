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

    void showTimings() {
        #if defined(DebugMode) && !defined(TestsGenerator)
            cout << "\n\n=================================================================\n";
            cout << "-> Precomputation Running Time:    " << getDuration(startPrecomputation, endPrecomputation) << " seconds.\n";
            cout << "-> Computation Running Time:       " << getDuration(startComputation, endComputation) << " seconds.\n";
            cout << "-> Total Running Time:             " << getDuration(startPrecomputation, endComputation) << " seconds.\n";
            cout << "=================================================================\n";
        #endif
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
namespace Template {}
using namespace Template;

constexpr int MAXN = 2e5 + 2;



void Compute(const int testNr, const bool isLastTest) {


}

void Precompute() {}

int main() {

    FastIO();
    HighPrecisionOutput();

    int numberOfTests = 1;
    cin >> numberOfTests;

    startPrecomputationTimer();

    Precompute();

    endPrecomputationTimerAndStartComputationTimer();

    for (int testNr = 1; testNr <= numberOfTests; ++testNr) {
        // cout << "Case #" << testNr << ": ";
        // cout << "Test #" << testNr << ": ";
        Compute(testNr, testNr == numberOfTests);
    }

    endComputationTimer();
    showTimings();

    return 0;
}