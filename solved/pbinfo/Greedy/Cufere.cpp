/*
    Programmer : Alexandru Olteanu
    Problem Link : https://www.pbinfo.ro/probleme/4393/cufere
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

ifstream fin("cufere.in");
ofstream fout("cufere.out");
#define cin fin
#define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 1e4 + 5;

int have[100];
bool p[100];

bool check(int x) {
    if (x <= 1) return false;
    if (x <= 3) return true;
    if (x % 2 == 0 || x % 3 == 0) return false;
    for (int i = 5; i * i <= x; ++i) {
        if (x % i == 0 || x % (i + 2) == 0) return false;
    }

    return true;
}

int main() {

    FastEverything
    HighPrecision

    for (int i = 11; i <= 99; i += 2) {
        p[i] = check(i);
    }

    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int c, n;
        cin >> c >> n;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= 3; ++j) {
                for (int t = 1; t <= 9; ++t) {
                    int x;
                    cin >> x;
                    if (x == 0) continue;
                    have[x % 100] += x / 100;
                }
            }
        }

        if (c == 1) {
            for (int i = 10; i <= 99; ++i) {
                if (!have[i]) continue;
                cout << i << " " << have[i] << '\n';
            }
            return 0;
        }

        vector<pii> res;
        for (int i = 10; i <= 99; ++i) {
            if (!have[i]) continue;
            int need = p[i] ? 16 : 64;
            while (have[i] >= need) {
                res.push_back({need, i});
                have[i] -= need;
            }
            if (have[i] > 0) {
                res.push_back({have[i], i});
            }
        }

        int k = 27 * n - res.size();
        while (k) {
            res.push_back({0, 0});
            --k;
        }

        for (int i = 0; i < (int) res.size(); ++i) {
            if (res[i].second == 0) cout << "0";
            else cout << res[i].first << res[i].second;
            if ((i + 1) % 9 == 0) {
                cout << '\n';
            }
            else {
                cout << " ";
            }
        }
        
    }

    return 0;
}
