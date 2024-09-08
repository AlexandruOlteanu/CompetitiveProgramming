/*
    Programmer : Alexandru Olteanu (OltAlexandru)
    Problem Link : https://www.pbinfo.ro/probleme/2313/ferma1
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

ifstream fin("ferma1.in");
ofstream fout("ferma1.out");
#define cin fin
#define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 5e1 + 5;

char c[maxn][maxn];
bool vis[maxn][maxn];
int n, m;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

void dfs(int x, int y) {
    if (x < 2 || y < 2 || x > n - 1 || y > m - 1) return;
    if (vis[x][y]) return;
    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
            if (c[i][j] == '+') {
                return;
            }
        }
    }
    
    vis[x][y] = true;
    for (int i = 0; i < 4; ++i) {
        dfs(x + dx[i], y + dy[i]);
    }
}


int main() {



    FastEverything
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int x, y;
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                cin >> c[i][j];
                if (c[i][j] == 'R') {
                    x = i, y = j;
                }
            }
        }

        dfs(x, y);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (c[i][j] == 'R') c[i][j] = '.';
                if (vis[i][j]) {
                    c[i - 1][j - 1] = c[i - 1][j] = c[i - 1][j + 1] = '*';
                    c[i][j - 1] = c[i][j] = c[i][j + 1] = '*';
                    c[i + 1][j - 1] = c[i + 1][j] = c[i + 1][j + 1] = '*';
                }
            }
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                cout << c[i][j];
            }
            cout << '\n';
        }

        
    }

    return 0;
}
