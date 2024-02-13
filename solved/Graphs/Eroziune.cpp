/*
    Programmer : Alexandru Olteanu
    Problem Link : https://www.pbinfo.ro/probleme/594/eroziune
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

// ifstream fin("input.txt");
// ofstream fout("output.txt");
// #define cin fin
// #define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 1e2 + 5;

int a[maxn][maxn];
int have[maxn][maxn];

set<tuple<int, int, int>> s;
int dx[] = {0, -1, 0, 1};
int dy[] = {-1, 0, 1, 0};

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                cin >> a[i][j];
            }
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (a[i][j] == 0) continue;
                int sum = 0;
                sum += (j > 1 && !a[i][j - 1]);
                sum += (j < m && !a[i][j + 1]);
                sum += (i > 1 && !a[i - 1][j]);
                sum += (i < n && !a[i + 1][j]);
                s.insert(make_tuple(sum, i, j));
                have[i][j] = sum;
            }
        }

        if (s.empty()) {
            cout << "0\n";
            return 0;
        }

        int ans = 0;

        while (!s.empty()) {
            vector<pii> v;
            while (true) {
                if (s.empty()) break;
                auto u = *(--s.end());
                int val = get<0>(u);
                int x = get<1>(u);
                int y = get<2>(u);
                if (val >= 2) {
                    v.push_back({x, y});
                    s.erase(--s.end());
                }
                else {
                    break;
                }
            }
            
            if (v.empty()) {
                cout << "-1\n";
                return 0;
            }
            for (auto u : v) {
                int x = u.first;
                int y = u.second;
                for (int i = 0; i < 4; ++i) {
                    int x1 = x + dx[i];
                    int y1 = y + dy[i];
                    if (s.count(make_tuple(have[x1][y1], x1, y1))) {
                        s.erase(s.find(make_tuple(have[x1][y1], x1, y1)));
                        ++have[x1][y1];
                        s.insert(make_tuple(have[x1][y1], x1, y1));
                    }
                }
            }
            ++ans;
        }        

        cout << ans << '\n';
        
    }

    return 0;
}