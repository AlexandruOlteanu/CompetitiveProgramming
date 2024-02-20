/*
    Programmer : Alexandru Olteanu
    Problem Link : https://www.pbinfo.ro/probleme/4447/cadouri1
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

ifstream fin("cadouri.in");
ofstream fout("cadouri.out");
#define cin fin
#define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 2e5 + 5;


int maxDiv(int x) {
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) return x / i;
    }
    return 1;
}

int main() {



    FastEverything
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int c, n;
        cin >> c >> n;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }

        int mx = maxDiv(n);
        bool taken = false;
        int x = maxDiv(n - 1);
        int mini = inf;
        int nrAp = 0;
        if (x > mx) {
            taken = true;
            mx = x;
            for (int i = 1; i <= n; ++i) {
                if (a[i] < mini) {
                    mini = a[i];
                }
            }
            for (int i = 1; i <= n; ++i) {
                if (a[i] == mini) {
                    ++nrAp;
                }
            }
        }

        if (c == 1) {
            cout << mx << " ";
            if (!taken) cout << "0\n";
            else cout << mini << '\n';
            return 0;
        }

        ll ans = 0;
        int mx1 = n / mx;
        if (!taken) {
            for (int i = mx1; i <= n; i += mx1) {
                ll cur = 0;
                for (int j = i - mx1 + 1; j <= i; ++j) {
                    cur += a[j];
                }
                ans = max(ans, cur);
            }
            cout << ans << " 0\n";
            return 0;
        }

        int was = 0;
        for (int i = mx1; i <= n; i += mx1) {
            ll cur = 0;
            bool have = false;
            int newWas = was;
            for (int j = i - mx1 + 1; j <= i; ++j) {
                if (a[j] == mini) have = true, ++newWas;
                cur += a[j];
            }
            if (!have) {
                if (was > 0) {
                    ans = max(ans, cur - a[i - mx1 + 1] + a[i + 1]);
                }
                if (was < nrAp) {
                    ans = max(ans, cur);                    
                }
            }
            else {
                cur -= mini;
                cur += a[i + 1];
                ans = max(ans, cur);
            }
            was = newWas;
        }

        cout << ans << " " << mini << '\n';

        
    }

    return 0;
}
