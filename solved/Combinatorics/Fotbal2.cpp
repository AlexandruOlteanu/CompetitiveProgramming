/*
    Programmer : Alexandru Olteanu
    Problem Link : https://www.pbinfo.ro/probleme/4394/fotbal2
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
const int mod = 1000000009;
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

ifstream fin("fotbal.in");
ofstream fout("fotbal.out");
#define cin fin
#define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 2e5 + 5;

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

vector<tuple<int, int, int>> v; 

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int n, k;
        cin >> n >> k;
        ModInv<long long> mi(n, mod);
        mi.build();
        
        for (int i = 1; i <= n; ++i) {
            int x, y, t;
            cin >> x >> y >> t;
            v.push_back(make_tuple(x, 1, t));
            v.push_back(make_tuple(y + 1, -1, t));
        }
        sort(all(v));
        int st = 0, dr = 0;
        ll ans = 0;
        bool ok = false;
        for (auto u : v) {
            int a, b, c;
            a = get<0>(u);
            b = get<1>(u);
            c = get<2>(u);
            if (b == -1) {
                if (c == 0) --st;
                else --dr;
                continue;
            }
            
            if (c == 0) ++st;
            else ++dr;
            if (st + dr < k || st == 0 || dr == 0) continue;

            if (!ok) {
                ans += mi.comb(st + dr, k);
                ans -= mi.comb(st, k);
                ans -= mi.comb(dr, k);
                while (ans < 0) ans += mod;
                ok = true;
                continue;
            }
            
            ans += mi.comb(st + dr - 1, k - 1);
            ans %= mod;

            if (c == 0) {
               ans -= mi.comb(st - 1, k - 1);
            }
            else {
               ans -= mi.comb(dr - 1, k - 1);
            }
         

            while (ans < 0) ans += mod;

        }


        cout << ans << '\n';
        
    }

    return 0;
}