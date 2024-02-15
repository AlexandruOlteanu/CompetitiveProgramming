/*
    Programmer : Alexandru Olteanu
    Problem Link : https://www.pbinfo.ro/probleme/4405/unificare
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

ifstream fin("unificare.in");
ofstream fout("unificare.out");
#define cin fin
#define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 1e5 + 5;

int a[maxn];
bool have[maxn][10];

int cmp(int cur[], int mx[]) {
    int sz1 = 0, sz2 = 0;
    bool h1 = false, h2 = false;
    for (int j = 0; j <= 9; ++j) {
        sz1 += cur[j];
        sz2 += mx[j];
        if (j > 0 && cur[j] > 0) h1 = true;
        if (j > 0 && mx[j] > 0) h2 = true;
    }
    if (h1 && h2) {
        if (sz1 > sz2) return 1;
        if (sz1 < sz2) return -1;
    }

    for (int j = 9; j >= 0; --j) {
        if (cur[j] > mx[j]) return 1;
        if (cur[j] < mx[j]) return -1;
    }

    return 0;

}


void comb(int n, int k) {

    int mx[10] = {0}, cur[10] = {0};
    for (int i = 1; i <= n; ++i) {
        int x = a[i];
        while (x) {
            have[i][x % 10] = true;
            x /= 10;
        }
        if (i <= k) {
            for (int j = 0; j <= 9; ++j) {
                mx[j] += have[i][j];
            }
        }
    }

    for (int j = 0; j <= 9; ++j) {
        cur[j] = mx[j];
    }

    for (int i = k + 1; i <= n; ++i) {
        for (int j = 0; j <= 9; ++j) {
            cur[j] -= have[i - k][j];
            cur[j] += have[i][j];
        }
        int res = cmp(cur, mx);
        if (res == 1) {
            for (int j = 0; j <= 9; ++j) {
                mx[j] = cur[j];
            }
        }
    }

    bool ok = true;
    for (int j = 9; j >= 0; --j) {
        if (j == 0) {
            if (ok) {
                while (mx[j]) {
                    cout << "0";
                    --mx[j];
                }
            }
            else {
                if (mx[j]) cout << "0";
            }
            continue;
        }
        while (mx[j]) {
            cout << j;
            --mx[j];
        }
    }

}


int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int c, n, k;
        cin >> c >> n >> k;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }

        if (c == 1) {
            int mx = 0;
            for (int i = 1; i <= n; ++i) {
                int x = a[i];
                int cif = 0;
                while (x) {
                    ++cif;
                    x /= 10;
                }
                if (cif == k) {
                    mx = max(mx, a[i]);
                }
            }
            cout << mx << '\n';

            return 0;
        }

        if (c == 2) {
            comb(n, 2);
            return 0;
        }

        comb(n, k);
        
    }

    return 0;
}