/*
    Programmer : Alexandru Olteanu
    Problem Link : https://www.pbinfo.ro/probleme/4409/castel4
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

ifstream fin("castel.in");
ofstream fout("castel.out");
#define cin fin
#define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 5e3 + 5;

int a[maxn];

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int c, n;
        cin >> c >> n;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }

        if (c == 1) {
            int ans = 0;
            for (int i = 1; i <= n; ++i) {
                ans += a[i] <= 9;
            }

            cout << ans << '\n';
            return 0;
        }

        int r = sqrt(2 * n);
        if (r * (r + 1) > 2 * n) --r;

        if (c == 2) {

            // 1 + 2 + 3 + ... + k <= n 
            // k(k + 1) / 2 <= n 
            // k(k + 1) <= 2n 
            
            cout << r << " " << a[r * (r + 1) / 2] << '\n';

            return 0;
        }

        cout << r * (r - 1) / 2 << " ";

        int start = 1, end = r;
        ll ans = 0;
        while (r) {
            for (int i = start + 1; i <= end; ++i) {
                ans += a[i] + a[i - 1];
            }
            --r;
            start = end + 1;
            end = start + r - 1;
        }


        cout << ans << '\n';

        
    }

    return 0;
}