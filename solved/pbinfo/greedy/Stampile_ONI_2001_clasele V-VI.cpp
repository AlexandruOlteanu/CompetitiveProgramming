/*
    Programmer : Alexandru Olteanu (OltAlexandru)
    Problem Link : https://www.pbinfo.ro/probleme/3560/stampile
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

// ifstream fin("input.in");
// ofstream fout("output.out");
// #define cin fin
// #define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 2e5 + 5;

int ap[11];

int main() {



    FastEverything
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int n;
        cin >> n;
        vector<int> p;
        for (int i = 1; i <= n; ++i) {
            int x;
            bool dif[11] = {0};
            cin >> x;
            int xc = x;
            int cnt = 0;
            while (x) {
                ++ap[x % 10];
                if (!dif[x % 10]) ++cnt;
                dif[x % 10] = true;
                x /= 10;
            }
            if (cnt == 2) {
                p.pb(xc);
            }
        }
        vector<pii> v;
        for (int i = 0; i <= 9; ++i) {
            v.pb({ap[i], i});
        }
        sort(all(v));
        cout << v[0].se << '\n';
        for (int i = (int) v.size() - 1; i >= 0; --i) {
            cout << v[i].se << " ";
        }
        cout << '\n';
        sort(all(p));
        for (auto x : p) {
            cout << x << " ";
        }
        if (p.empty()) {
            cout << "-1\n";
        }
    }

    return 0;
}