/*
  ░█████╗░██╗░░░░░███████╗██╗░░██╗░█████╗░███╗░░██╗██████╗░██████╗░██╗░░░██╗██╗███╗░░██╗██╗░░░██╗
  ██╔══██╗██║░░░░░██╔════╝╚██╗██╔╝██╔══██╗████╗░██║██╔══██╗██╔══██╗██║░░░██║██║████╗░██║██║░░░██║
  ███████║██║░░░░░█████╗░░░╚███╔╝░███████║██╔██╗██║██║░░██║██████╔╝██║░░░██║██║██╔██╗██║╚██╗░██╔╝
  ██╔══██║██║░░░░░██╔══╝░░░██╔██╗░██╔══██║██║╚████║██║░░██║██╔══██╗██║░░░██║██║██║╚████║░╚████╔╝░
  ██║░░██║███████╗███████╗██╔╝╚██╗██║░░██║██║░╚███║██████╔╝██║░░██║╚██████╔╝██║██║░╚███║░░╚██╔╝░░
  ╚═╝░░╚═╝╚══════╝╚══════╝╚═╝░░╚═╝╚═╝░░╚═╝╚═╝░░╚══╝╚═════╝░╚═╝░░╚═╝░╚═════╝░╚═╝╚═╝░░╚══╝░░░╚═╝░░░
  They forged me in fire, they broke me in battle, yet here I rise, Invictus!

  Conquered:
    -> 92   Hard Problems (Aimed to improve my skills and deep thinking)
    -> 9    Fast Training Problems (Aimed to improve my speed on easier problems)
    -> 12   Leveling Up Problems (A mix of speed and thinking, climbing the Level AK ladder)
    -> 13   Virtual Contests Problems (Aimed to simulate live performances)
    -> 98   Random Problems from different sites
*/

// Link: https://codeforces.com/contest/1717/problem/D
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
// ========================================================================
// = Modular Int taken from tourist, respect
// =
// = This template provides a type-safe modular arithmetic class `Modular<T>`
// = for computations under a fixed modulus. It supports all basic arithmetic
// = operations and combination (nCk) calculations with precomputed factorials.
// =
// = ------------------------------ USAGE --------------------------------
// =
// = Define a type alias using a fixed modulus:
// =     constexpr int MintMod = 998244353;
// =     using Mint = Modular<std::integral_constant<decay<decltype(MintMod)>::type, MintMod>>;
// =
// = Basic operations:
// =     Mint a = 5, b = 3;
// =     Mint c = a + b;        // c = 8
// =     Mint d = a - b;        // d = 2
// =     Mint e = a * b;        // e = 15
// =     Mint f = a / b;        // f = a * inverse(b)
// =
// =     int x = c();           // get underlying value of c
// =     Mint b = static_cast<Mint>(42);  // cast an integer to Mint
// =
// = Modular exponentiation:
// =     Mint x = power(a, 3);  // x = a^3 % mod
// =
// = Combinatorics (n choose k):
// =     Mint comb = C(5, 2);   // comb = 10
// =
// = Input/output:
// =     cin >> a >> b;
// =     cout << a + b << '\n';
// =
// = You can also compare with integers directly:
// =     if (a == 5) { ... }
// =
// = ======================================================================

template <typename T>
T inverse(T a, T m) {
    T u = 0, v = 1;
    while (a != 0) {
        T t = m / a;
        m -= t * a; swap(a, m);
        u -= t * v; swap(u, v);
    }
    assert(m == 1);
    return u;
}

template <typename T>
class Modular {
 public:
  using Type = typename decay<decltype(T::value)>::type;

  constexpr Modular() : value() {}
  template <typename U>
  Modular(const U& x) {
    value = normalize(x);
  }

  template <typename U>
  static Type normalize(const U& x) {
      Type v;
      if (-mod() <= x && x < mod()) v = static_cast<Type>(x);
      else v = static_cast<Type>(x % mod());
      if (v < 0) v += mod();
      return v;
  }

  const Type& operator()() const { return value; }
  template <typename U>
  explicit operator U() const { return static_cast<U>(value); }
  constexpr static Type mod() { return T::value; }

  Modular& operator+=(const Modular& other) { value += other.value; value -= (value >= mod()) * mod(); return *this; }
  Modular& operator-=(const Modular& other) { value -= other.value; value += (value < 0) * mod(); return *this; }
  template <typename U> Modular& operator+=(const U& other) { return *this += Modular(other); }
  template <typename U> Modular& operator-=(const U& other) { return *this -= Modular(other); }
  Modular& operator++() { return *this += 1; }
  Modular& operator--() { return *this -= 1; }
  Modular operator++(int) { Modular result(*this); *this += 1; return result; }
  Modular operator--(int) { Modular result(*this); *this -= 1; return result; }
  Modular operator-() const { return Modular(-value); }

  template <typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, int>::value, Modular>::type& operator*=(const Modular& rhs) {
    value = normalize(static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value));
    return *this;
  }
  template <typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, int64_t>::value, Modular>::type& operator*=(const Modular& rhs) {
    int64_t q = int64_t(static_cast<long double>(value) * rhs.value / mod());
    value = normalize(value * rhs.value - q * mod());
    return *this;
  }
  template <typename U = T>
  typename enable_if<!is_integral<typename Modular<U>::Type>::value, Modular>::type& operator*=(const Modular& rhs) {
    value = normalize(value * rhs.value);
    return *this;
  }

  Modular& operator/=(const Modular& other) { return *this *= Modular(inverse(other.value, mod())); }

  friend const Type& abs(const Modular& x) { return x.value; }

  template <typename U>
  friend bool operator==(const Modular<U>& lhs, const Modular<U>& rhs);

  template <typename U>
  friend bool operator<(const Modular<U>& lhs, const Modular<U>& rhs);

  template <typename V, typename U>
  friend V& operator>>(V& stream, Modular<U>& number);

 private:
  Type value;
};

template <typename T> bool operator==(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value == rhs.value; }
template <typename T, typename U> bool operator==(const Modular<T>& lhs, U rhs) { return lhs == Modular<T>(rhs); }
template <typename T, typename U> bool operator==(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) == rhs; }

template <typename T> bool operator!=(const Modular<T>& lhs, const Modular<T>& rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(const Modular<T>& lhs, U rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(U lhs, const Modular<T>& rhs) { return !(lhs == rhs); }

template <typename T> bool operator<(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value < rhs.value; }

template <typename T> Modular<T> operator+(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U> Modular<T> operator+(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U> Modular<T> operator+(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }

template <typename T> Modular<T> operator-(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U> Modular<T> operator-(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U> Modular<T> operator-(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }

template <typename T> Modular<T> operator*(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U> Modular<T> operator*(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U> Modular<T> operator*(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }

template <typename T> Modular<T> operator/(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> operator/(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> operator/(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }

template<typename T, typename U>
Modular<T> power(const Modular<T>& a, const U& b) {
    assert(b >= 0);
    Modular<T> x = a, res = 1;
    U p = b;
    while (p > 0) {
        if (p & 1) res *= x;
        x *= x;
        p >>= 1;
    }
    return res;
}

template <typename T>
bool IsZero(const Modular<T>& number) {
    return number() == 0;
}

template <typename T>
string to_string(const Modular<T>& number) {
    return to_string(number());
}

// U == std::ostream? but done this way because of fastoutput
template <typename U, typename T>
U& operator<<(U& stream, const Modular<T>& number) {
    return stream << number();
}

// U == std::istream? but done this way because of fastinput
template <typename U, typename T>
U& operator>>(U& stream, Modular<T>& number) {
    typename common_type<typename Modular<T>::Type, int64_t>::type x;
    stream >> x;
    number.value = Modular<T>::normalize(x);
    return stream;
}

// using ModType = int;
//
// struct VarMod { static ModType value; };
// ModType VarMod::value;
// ModType& MintMod = VarMod::value;
// using Mint = Modular<VarMod>;

constexpr int MintMod = 1000000007;
// constexpr int MintMod = 998244353;
using Mint = Modular<std::integral_constant<decay<decltype(MintMod)>::type, MintMod>>;

void print(Mint number) {
    cerr << number();
}

vector<Mint> fact(1, 1);
vector<Mint> inv_fact(1, 1);

Mint C(int n, int k) {
    if (k < 0 || k > n) {
      return 0;
    }
    while ((int) fact.size() < n + 1) {
        fact.push_back(fact.back() * (int) fact.size());
        inv_fact.push_back(1 / fact.back());
    }
    return fact[n] * inv_fact[k] * inv_fact[n - k];
}
/* ========================================================================
   -> Templates End
   ======================================================================== */

constexpr int MAXN = 2e5 + 2;



void CoreCompute(const int testIdx, const bool isLastTest) {

    int n, k;
    cin >> n >> k;
    if (k >= n) {
        cout << func::RmyPow(2, n) << '\n';
        return;
    }

    Mint ans = 0;
    for (int i = 0; i <= k; ++i) {
        ans += C(n, i);
    }

    cout << ans << '\n';

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