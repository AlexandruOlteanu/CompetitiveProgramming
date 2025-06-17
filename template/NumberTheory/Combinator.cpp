/*
    Template created by Alexandru Olteanu {AlexandruINV}

    How to use: 
        Combinator combinator(n);
        combinator.build();
        int res = combinator.comb(n, k)

    If I need combinatorics with mod: 
        Combinator combinator(n, invMod);
        combinator.build();
        int res = combinator.comb(n, k)

    If I need just a few combs: 
        Combinator combinator(n, invMod);  // or without mod
        combinator.build();

        // This doesn't work with mod, be careful, only for direct calculation
        int res = combinator.combOnce(n, k)
*/
// https://github.com/AlexandruOlteanu/CompetitiveProgramming/blob/main/template/NumberTheory/Combinator.cpp
struct Combinator {

    vector<vector<int>> c;
    int N;
    int invMod = -1;

    Combinator(int n){
        N = n;
    }

    Combinator(int n, int mod) {
        N = n;
        invMod = mod;
    }

    void build() {
        c.resize(N + 1);
        for (int i = 0; i <= N; ++i) {
            c[i].resize(N + 1);
            c[i][0] = c[i][i] = 1;
            for (int j = 1; j < i; ++j) {
                c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
                if (invMod > 0) c[i][j] %= invMod;
            }
        }
    }

    ll combOnce(int n, int k) {
        if (k > n) return 0;
        k = min(k, n - k);
        ll res = 1;
        for (int i = 1; i <= k; ++i) {
            res = res * (n - k + i) / i;
        }
        return res;
    }

    ll comb(int n, int k) {
        if (k > n) return 0;
        return c[n][k];
    }

};