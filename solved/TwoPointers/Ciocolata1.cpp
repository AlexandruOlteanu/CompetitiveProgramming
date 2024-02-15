/*
    Programmer : Alexandru Olteanu
    Problem Link : https://www.pbinfo.ro/probleme/4402/ciocolata1
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

ifstream fin("ciocolata.in");
ofstream fout("ciocolata.out");
#define cin fin
#define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 1e5 + 5;

int ap[10001];
int a[maxn];

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int c, n;
        cin >> c >> n;
        int nr = 0;
        int mx = 0;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            ++ap[a[i]];
            if (ap[a[i]] == mx) {
                nr = min(nr, a[i]);
            }
            if (ap[a[i]] > mx) {
                mx = ap[a[i]];
                nr = a[i];
            }
        }

        if (c == 1) {
            cout << nr << '\n';
            return 0;
        }

        int dif = inf;
        int sum1 = 0, sum2 = 0;
        int i = 1, j = n;
        while (i < j) {
            sum1 += a[i];
            while (j > i && sum2 + a[j] <= sum1) {
                sum2 += a[j];
                --j;
            }
            if (sum2 != 0) {
                dif = min(dif, sum1 - sum2);
            }
            ++i;
        }

        cout << dif << '\n';


        
    }

    return 0;
}
