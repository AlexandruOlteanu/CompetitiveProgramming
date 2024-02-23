/*
    Programmer : Alexandru Olteanu
    Problem Link : https://www.pbinfo.ro/probleme/4401/hibrid
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

ifstream fin("hibrid.in");
ofstream fout("hibrid.out");
#define cin fin
#define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 2e5 + 5;

const int bigInterval = 2e6;

int ap[bigInterval + 2], is[bigInterval + 2], have[bigInterval + 2];
vector<int> v;
int a[maxn];

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int c, k, n;
        cin >> c >> k >> n;
        for (int i = 1; i <= k; ++i) {
            int x, y, cost;
            cin >> x >> y >> cost;
            x += 1e6;
            y += 1e6;
            is[x] += i;
            is[y + 1] -= i;
            v.push_back(cost);
        }

        for (int i = 1; i <= bigInterval; ++i) {
            is[i] += is[i - 1];
        }
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            a[i] += 1e6;
        }
        for (int i = 1; i < n; ++i) {
            int x = a[i], y = a[i + 1];
            if (x > y) swap(x, y);
            ++ap[x], --ap[y + 1];
        }

        for (int i = 1; i <= bigInterval; ++i) {
            ap[i] += ap[i - 1];
        }
        int mx = -1;
        int ans = -1;
        for (int i = 0; i <= bigInterval; ++i) {
            if (!is[i] || !ap[i]) continue;
            if (ap[i] == mx) {
                ans = min(ans, is[i]);
            }
            if (ap[i] > mx) {
                mx = ap[i];
                ans = is[i];
            }
            have[is[i]] = max(have[is[i]], ap[i]);
        }

        if (c == 1) {
            cout << ans << '\n';
            return 0;
        }
        ll cnt = 0;
        for (int i = 1; i <= k; ++i) {
            cnt += 1LL * have[i] * v[i - 1];
        }

        cout << cnt << '\n';
        
    }

    return 0;
}