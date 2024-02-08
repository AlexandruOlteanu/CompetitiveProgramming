/*
    Programmer : Alexandru Olteanu
    Problem Link : https://codeforces.com/contest/1207/problem/D
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// Useful
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
#define FastEverything  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define HighPrecision cout << fixed << setprecision(17);
typedef long long ll;
typedef pair<int, int> pii;
const int mod = 1000000007;
const int mod1 = 998244353;
ll mypowr(ll a, ll b, ll mod1) {ll res = 1; if(b < 0)b = 0; a %= mod1; assert(b >= 0);
for(; b; b >>= 1){if (b & 1) res = res * a % mod1;a = a * a % mod1;} return res;}
ll mypow(ll a, ll b) {ll res = 1; if(b < 0)b = 0;assert(b >= 0);
for(; b; b >>= 1){if(b & 1) res = res * a;a = a * a;} return res;}
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

// ifstream fin("input.txt");
// ofstream fout("output.txt");
// #define cin fin
// #define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 3e5 + 5;

/*
    Template created by Alexandru Olteanu

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

pii a[maxn];

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int n;
        cin >> n;
        ModInv<long long> mi(n, mod1);
        mi.build();

        for (int i = 1; i <= n; ++i) {
            cin >> a[i].fi >> a[i].se;
        }
        sort(a + 1, a + n + 1);
        ll ans = mi.fact[n];
        int g = 1;
        int p = 1;
        for (int i = 2; i <= n; ++i) {
            if (a[i].fi == a[i - 1].fi) {
                ++g;
            }
            else {
                p = 1LL * p * mi.fact[g] % mod1;
                g = 1; 
            }
        }

        p = 1LL * p * mi.fact[g] % mod1;
        ans -= p;
        if (ans < 0) ans += mod1;

        for (int i = 1; i <= n; ++i) {
            swap(a[i].fi, a[i].se);
        }

        sort(a + 1, a + n + 1);
        g = 1;
        p = 1;
        for (int i = 2; i <= n; ++i) {
            if (a[i].fi == a[i - 1].fi) {
                ++g;
            }
            else {
                p = 1LL * p * mi.fact[g] % mod1;
                g = 1; 
            }
        }

        p = 1LL * p * mi.fact[g] % mod1;
        ans -= p;
        if (ans < 0) ans += mod1;
        for (int i = 2; i <= n; ++i) {
            if (a[i].se < a[i - 1].se) {
                cout << ans << '\n';
                return 0;
            }
        }

        g = 1;
        p = 1;
        for (int i = 2; i <= n; ++i) {
            if (a[i].fi == a[i - 1].fi && a[i].se == a[i - 1].se) {
                ++g;
            }
            else {
                p = 1LL * p * mi.fact[g] % mod1;
                g = 1;
            }
        }
        p = 1LL * p * mi.fact[g] % mod1;
        ans += p;
        ans %= mod1;

        cout << ans << '\n';
        
    }

    return 0;
}