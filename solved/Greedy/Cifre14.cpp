/*
    Programmer : Alexandru Olteanu
    Problem Link : https://www.pbinfo.ro/probleme/4589/cifre14
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

ifstream fin("cifre.in");
ofstream fout("cifre.out");
#define cin fin
#define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 2e5 + 5;

map<ll, int> m;

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int c, n;
        cin >> c >> n;
        vector<string> s(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> s[i];
        }
        for (int i = 1; i <= n; ++i) {
            string res = "";
            for (auto c : s[i]) {
                res += c;
                if (c % 2 == 0) res += char((c - '0') / 2 + '0');
            }
            s[i] = res;
        }
        if (c == 1) {
            for (int i = 1; i <= n; ++i) {
                cout << s[i] << " ";
            }
            return 0;
        }

        ll mx = 0;
        for (int i = 1; i <= n; ++i) {
            int ap[10] = {0};
            for (auto c : s[i]) {
                ++ap[c - '0'];
            }
            ll res = 0;
            for (int j = 0; j <= 9; ++j) {
                if (!ap[j]) continue;
                res = res * 10 + ap[j] % 10;
            }
            ++m[res];
            mx = max(mx, res);
        }

        cout << mx << " " << m[mx] << '\n';
        
    }

    return 0;
}
