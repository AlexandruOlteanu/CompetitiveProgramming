/*
    Programmer : Alexandru Olteanu
    Problem Link : https://www.pbinfo.ro/probleme/4413/parcare2
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

ifstream fin("parcare.in");
ofstream fout("parcare.out");
#define cin fin
#define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 2e5 + 5;

int res[maxn], res1[maxn];
set<tuple<int, int, int>> s;


int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int n, m, t;
        cin >> n >> m >> t;
        for (int i = 1; i <= n; ++i) {
           s.insert(make_tuple(-1, -1, i)); 
        }
        for (int i = 1; i <= m; ++i) {
            int x, y;
            cin >> x >> y;
            auto u = *s.begin();
            int f = get<0>(u);
            int st = get<1>(u);
            int idx = get<2>(u);
            if (f == -1 || f <= x) {
                res[i] = idx;
                s.erase(s.begin());
                s.insert(make_tuple(y, x, idx));
                continue;
            }

            res[i] = -1;
        }

        while (!s.empty()) {
            auto u = *s.begin();
            int f = get<0>(u);
            int st = get<1>(u);
            int idx = get<2>(u);
            s.erase(s.begin());
            if (f <= t) {
                res1[idx] = -1;
            }
            else {
                res1[idx] = st;
            }
        }

        for (int i = 1; i <= m; ++i) {
            cout << res[i] << '\n';
        }
        for (int i = 1; i <= n; ++i) {
            cout << res1[i] << " ";
        }
        cout << '\n';
        
    }

    return 0;
}