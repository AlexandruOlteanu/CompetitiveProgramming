/*
    Template created by Alexandru Olteanu {A1exandruAI}

    How to use: 
        ModInv<long long> mi(n, mod);
        mi.build();
        int res = mi.comb(n, k)
        
*/
template<typename A>
struct ModInv {

    vector<A> fact;
    vector<A> inv;
    int N;
    ll invMod;

    ModInv(int n, int mod){
        N = n;
        invMod = mod;
        fact.resize(n + 1);
        inv.resize(n + 1);
    }

    long long power(long long a, long long b) {
        long long res = 1;
        if (b < 0) b = 0;
        a %= invMod;
        assert(b >= 0);
        
        for (; b; b >>= 1) {
            if (b & 1) res = res * a % invMod;
            a = a * a % invMod;
        }
        
        return res;
    }

    void build() {
        fact[0] = 1;
        for (int i = 1; i <= N; ++i) {
            fact[i] = fact[i - 1] * i;
            fact[i] %= invMod;
        }
        inv[N] = power(fact[N], invMod - 2);
        for (int i = N - 1; i >= 0; --i) {
            inv[i] = (i + 1) * inv[i + 1];
            inv[i] %= invMod;
        }
    }

    long long comb(int n, int k) {
        if (k > n) return 0;
        if (k < 0 || n < 0) return 0;
        return fact[n] * inv[n - k] % invMod * inv[k] % invMod;
    }
};