/*
    Programmer : Alexandru Olteanu
    Problem Link : https://www.pbinfo.ro/probleme/4407/partitura
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

ifstream fin("partitura.in");
ofstream fout("partitura.out");
#define cin fin
#define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 20;

vector<ll> v[maxn];

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int n;
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            int x, y;
            cin >> x >> y;
            v[x].push_back(y);
        }

        for (int i = 18; i >= 1; --i) {
            sort(all(v[i]));
            while (!v[i].empty()) {
                ll h1 = v[i].back();
                v[i].pop_back();
                ll h2 = v[i].back();
                v[i].pop_back();
                v[i - 1].push_back(h1 + h2);
            }
        }
        
        ll ans = 0;
        sort(all(v[0]));
        while (!v[0].empty()) {
            ll h1 = v[0].back();
            v[0].pop_back();
            ans += 1LL * h1 * h1;
        }

        cout << ans << '\n';

    }

    return 0;
}
