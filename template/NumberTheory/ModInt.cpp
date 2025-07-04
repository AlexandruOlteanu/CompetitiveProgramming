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

// https://github.com/AlexandruOlteanu/CompetitiveProgramming/blob/main/template/NumberTheory/ModInt.cpp
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
  Type getValue() const { return value; }
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

constexpr int MAX_FACT_COMPUTED = 2000000;

void computeFactUpToN(int n) {
    if (n < static_cast<int>(fact.size())) return;
    int cur = static_cast<int>(fact.size());
    fact.reserve(n + 1);
    inv_fact.reserve(n + 1);
    while (cur <= n) {
        fact.push_back(fact.back() * cur);
        inv_fact.push_back(1 / fact.back());
        ++cur;
    }
}

Mint getFactFromXtoY(long long x, long long y) {
    if (x > y) return 1;
    Mint res = 1;
    if (MAX_FACT_COMPUTED >= x && MAX_FACT_COMPUTED <= y) {
        computeFactUpToN(MAX_FACT_COMPUTED);
        res = fact[MAX_FACT_COMPUTED] * inv_fact[x - 1];
        x = MAX_FACT_COMPUTED + 1;
    }
    for (long long i = x; i <= y; i++) {
        res *= i;
    }
    return res;
}

template<typename T>
Mint P(T n) {
    assert(n >= 0);
    if (n == 0) return 1;
    return getFactFromXtoY(1, n);
}

template <typename T>
Mint A(T n, T k) {
    assert(n >= 0);
    k = n - k;
    if (k < 0 || k > n) return 0;
    if (k == n) return 1;

    if (n <= MAX_FACT_COMPUTED) {
        computeFactUpToN(n);
        return fact[n] * inv_fact[k];
    }

    Mint res = 1;
    res = getFactFromXtoY(k + 1, n);

    return res;
}

template <typename T>
Mint C(T n, T k) {
    assert(n >= 0 && k >= 0);
    if (k < 0 || k > n) return 0;
    if (k == 0 || n == k) return 1;
    if (k > n - k) k = n - k;

    if (n <= MAX_FACT_COMPUTED) {
        computeFactUpToN(n);
        return fact[n] * inv_fact[k] * inv_fact[n - k];
    }

    Mint res = 1;
    res = getFactFromXtoY(n - k + 1, n);

    int min_k = min(1LL * k, 1LL * MAX_FACT_COMPUTED);
    computeFactUpToN(min_k);
    res *= inv_fact[min_k];
    for (long long i = min_k + 1; i <= k; ++i) {
        res /= Mint(i);
    }
    return res;
}