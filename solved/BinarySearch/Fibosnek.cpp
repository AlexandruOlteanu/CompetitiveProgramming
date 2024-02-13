/*
    Programmer : Alexandru Olteanu
    Problem Link : https://www.pbinfo.ro/probleme/4406/fibosnek
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

ifstream fin("fibosnek.in");
ofstream fout("fibosnek.out");
#define cin fin
#define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 2e5 + 5;

vector<int> fib; 
vector<short> a(2250000 + 1);
vector<bool> is(2250000 + 1);

int findFib(int x) {
    int lo = 0, hi = fib.size() - 1;
    int ans = 0;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (fib[mid] <= x) {
            ans = mid;
            lo = mid + 1;
            continue;
        }
        hi = mid - 1;
    }
    if (ans == fib.size() - 1) return ans;
    if (x - fib[ans] <= fib[ans + 1] - x) return ans;
    return ans + 1;
}

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int x = 0, y = 1;
        fib.push_back(x);
        fib.push_back(y);
        for (int i = 2; i <= 46; ++i) {
            int z = x + y;
            fib.push_back(z);
            x = y;
            y = z;
        }

        int c, n, m;
        int cnt = 0;
        cin >> c >> n >> m;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                int x;
                cin >> x;
                int y = findFib(x);
                a[(j - 1) * n + i] = y;
                if (x == fib[y]) {
                    ++cnt;
                    is[(j - 1) * n + i] = true;
                }
            }
        }

        if (c == 1) {
            cout << cnt << '\n';
            return 0;
        }
        int sz = n * m;

        int lmax = 0;
        ll ans = 0;
        ll sum1 = 0, bad = 0, sum2 = 0;
        int l1 = 0, lb = 0, l2 = 0;
        for (int i = 1; i <= sz; ++i) {
            if (is[i]) {
                if (bad == 0) sum1 += fib[a[i]], ++l1;
                else sum2 += fib[a[i]], ++l2;
            }
            else {
                if (sum2 > 0) {
                    sum1 = sum2;
                    l1 = l2;
                    bad = fib[a[i]];
                    lb = 1;
                    sum2 = 0;
                    l2 = 0;
                }
                else {
                    bad += fib[a[i]];
                    ++lb;
                }
            }

            if (l1 + lb + l2 > lmax) {
                lmax = l1 + lb + l2;
                ans = sum1 + bad + sum2;
            }
        }

        cout << ans << '\n';


        

        
    }

    return 0;
}