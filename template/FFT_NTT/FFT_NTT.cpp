/*****************************************************************
* FFT – Complex Fast Fourier Transform (Rounded Integer Output) *
* ------------------------------------------------------------- *
* Purpose: Multiply two polynomials with integer coefficients.  *
* Returns a vector<long long> with rounded integer coefficients.*
* Uses complex numbers → may suffer from rounding errors.       *
* Time Complexity: O(n log n)                                   *
* ------------------------------------------------------------- *
* Usage:                                                        *
*   vector<int> A = {1, 2};                                     *
*   vector<int> B = {3, 4};                                     *
*   auto C = FFT::multiply(A, B);                               *
*****************************************************************/
struct FFT {
    using cd = complex<double>;
    static constexpr double PI = acos(-1.0);

    // In-place Cooley–Tukey FFT (invert = true for inverse)
    static void transform(vector<cd>& a, bool invert) {
        int n = a.size();
        for (int i = 1, j = 0; i < n; ++i) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if (i < j) swap(a[i], a[j]);
        }
        for (int len = 2; len <= n; len <<= 1) {
            double ang = 2 * PI / len * (invert ? -1 : 1);
            cd wlen(cos(ang), sin(ang));
            for (int i = 0; i < n; i += len) {
                cd w(1);
                for (int j = 0; j < len / 2; ++j) {
                    cd u = a[i + j];
                    cd v = a[i + j + len / 2] * w;
                    a[i + j]             = u + v;
                    a[i + j + len / 2]   = u - v;
                    w *= wlen;
                }
            }
        }
        if (invert)
            for (cd& x : a) x /= n;
    }

    // Multiply integer polynomials A and B using FFT
    // Returns vector<long long> (rounded coefficients)
    static vector<long long> multiply(const vector<int>& A,
                                      const vector<int>& B) {
        vector<cd> fa(A.begin(), A.end()), fb(B.begin(), B.end());
        int n = 1;
        while (n < int(A.size() + B.size())) n <<= 1;
        fa.resize(n);
        fb.resize(n);

        transform(fa, false);
        transform(fb, false);
        for (int i = 0; i < n; ++i) fa[i] *= fb[i];
        transform(fa, true);

        vector<long long> res(n);
        for (int i = 0; i < n; ++i)
            res[i] = llround(fa[i].real());
        while (!res.empty() && res.back() == 0)
            res.pop_back();
        return res;
    }
};



/*****************************************************************
* NTT<MOD, ROOT> – Modular FFT (Exact Convolution)              *
* ------------------------------------------------------------- *
* Purpose: Multiply two integer polynomials modulo a prime.     *
* Requires:                                                     *
*   - MOD ≡ 1 (mod 2^k) (e.g., 998244353 = 119 · 2^23 + 1)      *
*   - ROOT is a primitive root of MOD                           *
* Returns exact results mod MOD.                                *
* Time Complexity: O(n log n)                                   *
* ------------------------------------------------------------- *
* Usage:                                                        *
*   using NTT998 = NTT<998244353, 3>;                           *
*   vector<uint32_t> A = {1, 2};                                *
*   vector<uint32_t> B = {3, 4};                                *
*   auto C = NTT998::multiply(A, B);                            *
*****************************************************************/
template<uint32_t MOD, uint32_t ROOT>
struct NTT {
    using uint = uint32_t;

    // Fast exponentiation: base^exp % MOD
    static uint mod_pow(uint base, uint exp) {
        uint64_t res = 1, x = base;
        while (exp) {
            if (exp & 1) res = res * x % MOD;
            x = x * x % MOD;
            exp >>= 1;
        }
        return uint(res);
    }

    // In-place NTT transform (invert = true for inverse)
    static void transform(vector<uint>& a, bool invert) {
        int n = a.size();
        for (int i = 1, j = 0; i < n; ++i) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if (i < j) swap(a[i], a[j]);
        }
        for (int len = 2; len <= n; len <<= 1) {
            uint wlen = mod_pow(ROOT, (MOD - 1) / len);
            if (invert) wlen = mod_pow(wlen, MOD - 2);
            for (int i = 0; i < n; i += len) {
                uint64_t w = 1;
                for (int j = 0; j < len / 2; ++j) {
                    uint u = a[i + j];
                    uint v = uint64_t(a[i + j + len / 2]) * w % MOD;
                    a[i + j]             = (u + v) % MOD;
                    a[i + j + len / 2]   = (u + MOD - v) % MOD;
                    w = w * wlen % MOD;
                }
            }
        }
        if (invert) {
            uint inv_n = mod_pow(n, MOD - 2);
            for (uint& x : a)
                x = uint64_t(x) * inv_n % MOD;
        }
    }

    // Multiply two integer polynomials mod MOD
    // Returns vector<uint32_t> of length A.size() + B.size() - 1
    static vector<uint> multiply(const vector<uint>& A,
                                 const vector<uint>& B) {
        vector<uint> fa(A.begin(), A.end()), fb(B.begin(), B.end());
        int n = 1;
        while (n < int(A.size() + B.size())) n <<= 1;
        fa.resize(n);
        fb.resize(n);

        transform(fa, false);
        transform(fb, false);
        for (int i = 0; i < n; ++i)
            fa[i] = uint64_t(fa[i]) * fb[i] % MOD;
        transform(fa, true);
        return fa;
    }
};