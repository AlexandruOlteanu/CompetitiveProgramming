/*
    Programmer : Alexandru Olteanu (OltAlexandru)
    Problem Link: https://www.pbinfo.ro/probleme/4021/tablou1
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

ifstream fin("tablou.in");
ofstream fout("tablou.out");
#define cin fin
#define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 2e5 + 5;

int a[101][101];
int can_inc[101];

int main() {



    FastEverything
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int n, s;
        cin >> n >> s;
        int need = n * (n + 1) / 2 * n;
        if (need > s) {
            cout << "0\n";
            return 0;
        }
        for (int j = 1; j <= n; ++j) {
            a[1][j] = j;
        }
        for (int i = 2; i <= n; ++i) {
            a[i][1] = n - i + 2;
        }
        for (int i = 2; i <= n; ++i) {
            for (int j = 2; j <= n; ++j) {
                a[i][j] = a[i - 1][j - 1];
            }
        }

        s -= need;
        int can = s / (n * n);
        s -= can * n * n;
        for (int i = n; i >= 1; --i) {
            if (s >= n) {
                can_inc[i] = n;
                s -= n;
            } else {
                can_inc[i] = s;
                break;
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (can_inc[a[i][j]]) {
                    --can_inc[a[i][j]];
                    ++a[i][j];
                }
                a[i][j] += can;
            }
        }


        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                cout << a[i][j] << " ";
            }
            cout << '\n';
        }

    }

    return 0;
}
