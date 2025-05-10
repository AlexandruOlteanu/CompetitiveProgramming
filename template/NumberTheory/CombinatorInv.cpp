/*
    Template created by Alexandru Olteanu {A1exandruAI}

    How to use: 
        CombinatorInv combinatorInv(n, mod);
        combinatorInv.build();
        int res = combinatorInv.comb(n, k)
        
    How to use for division:
        CombinatorInv inv(mod);
        int res = inv.divideInv(x, y);    
*/
struct CombinatorInv {

    vector<ll> fact;
    vector<ll> inv;
    int N;
    ll invMod;

    // only for usage of devideInverse
    CombinatorInv(int mod) {
        invMod = mod;
    }

    CombinatorInv(int n, int mod){
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

    long long combInv(int n, int k) {
        if (k > n) return 0;
        if (k < 0 || n < 0) return 0;
        return fact[n] * inv[n - k] % invMod * inv[k] % invMod;
    }

    long long divideInv(long long x, long long y) {
        long long yinv = power(y, invMod - 2);
        return x % invMod * yinv % invMod;
    }
};