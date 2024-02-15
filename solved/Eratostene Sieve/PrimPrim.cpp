/*
    Programmer : Alexandru Olteanu
    Problem Link : https://www.pbinfo.ro/probleme/4400/primprim
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

ifstream fin("primprim.in");
ofstream fout("primprim.out");
#define cin fin
#define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 2e5 + 5;

bool p[1000001];
int a[1000001];
vector<int> primes;

int find(int x) {
    int lo = 0, hi = (int) primes.size() - 1;
    int ans = 0;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (primes[mid] <= x) {
            ans = mid;
            lo = mid + 1;
            continue;
        }
        hi = mid - 1;
    }
    int dif = abs(x - primes[ans]);
    if (ans == primes.size() - 1) return dif;
    dif = min(dif, primes[ans + 1] - x);
    return dif;
}

int have[100];

int main() {


    for (int i = 2; i <= 1000000; ++i) {
        if (!p[i]) {
            primes.push_back(i);
            for (int j = i + i; j <= 1000000; j += i) {
                p[j] = true;
            }
        }
    }

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
            int sum = 0;
            for (int i = 1; i <= n; ++i) {
                sum += find(a[i]);
            }
            cout << sum << '\n';
            return 0;
        }

        for (int i = 1; i <= n; ++i) {
            ++have[find(a[i])];
        }

        int q;
        cin >> q;
        for (int i = 1; i <= q; ++i) {
            int pos, x, k;
            cin >> pos >> x >> k;
            int cost = find(a[pos]);
            --have[cost];
            a[pos] = x;
            cost = find(x);
            ++have[cost];
            int ans = 0;
            for (int j = 0; j <= 60 && k; ++j) {
                if (k > have[j]) {
                    ans += have[j] * j;
                    k -= have[j];
                    continue;
                }
                ans += k * j;
                k = 0;
            }
            cout << ans << '\n';
        }
        
    }

    return 0;
}