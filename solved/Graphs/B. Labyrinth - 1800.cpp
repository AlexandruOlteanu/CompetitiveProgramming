/*
    Programmer : Alexandru Olteanu
    Problem Link : https://codeforces.com/problemset/problem/1063/B 
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

const ll infll = 0x7fffffffffffffff;
const int inf = 0x7fffffff;
const int maxn = 2e3 + 5;

char c[maxn][maxn];

int n, m, l, r, x, y;

vector<pii> d[maxn][maxn];
set<pii> in_q;

bool update(int x, int y, pii cost) {
    if (cost.fi < 0 || cost.se < 0) return false;
    if (x < 1 || x > n || y < 1 || y > m) return false;
    if (c[x][y] == '*') return false;
    if (d[x][y].empty()) {
        d[x][y].push_back(cost);
        return true;
    }
    vector<pii> before = d[x][y];
    d[x][y].clear();
    bool ok = false;
    for (auto x : before) {
        if (cost.fi > x.fi || cost.se > x.se) {
            ok = true;
            break;
        }
    }
    if (!ok) {
        d[x][y] = before;
        return false;
    }
    for (auto u : before) {
        if (cost.fi > u.fi && cost.se > u.se) {
            continue;
        }
        d[x][y].push_back(u);
    }
    d[x][y].push_back(cost);
    return true;
}

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        cin >> n >> m >> x >> y >> l >> r;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                cin >> c[i][j];
            }
        }

        queue<pii> q;
        d[x][y].push_back({l, r});
        in_q.insert({x, y});
        q.push({x, y});
        while (!q.empty()) {
            auto top = q.front();
            q.pop();
            in_q.erase({top.fi, top.se});
            for (auto u : d[top.fi][top.se]) {
                if (update(top.fi - 1, top.se, u)) {
                    if (!in_q.count({top.fi - 1, top.se})) {
                        q.push({top.fi - 1, top.se});
                        in_q.insert({top.fi - 1, top.se});
                    }
                }
                if (update(top.fi + 1, top.se, u)) {
                    if (!in_q.count({top.fi + 1, top.se})) {
                        q.push({top.fi + 1, top.se});
                        in_q.insert({top.fi + 1, top.se});
                    }
                }
                if (update(top.fi, top.se - 1, {u.fi - 1, u.se})) {
                    if (!in_q.count({top.fi, top.se - 1})) {
                        q.push({top.fi, top.se - 1});
                        in_q.insert({top.fi, top.se - 1});
                    }
                }
                if (update(top.fi, top.se + 1, {u.fi, u.se - 1})) {
                    if (!in_q.count({top.fi, top.se + 1})) {
                        q.push({top.fi, top.se + 1});
                        in_q.insert({top.fi, top.se + 1});
                    }
                }
            }
        }


        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                ans += (!d[i][j].empty());
            }
        }

        cout << ans << '\n';
        
    }

    return 0;
}

// Optimal Solution
// /*
//     Programmer : Alexandru Olteanu
// */
// #include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
// using namespace std;
// template<typename T>
// using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// // Useful
// mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
// #define FastEverything  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
// #define HighPrecision cout << fixed << setprecision(17);
// typedef long long ll;
// typedef pair<int, int> pii;
// const int mod = 1000000007;
// const int mod1 = 998244353;
// ll mypowr(ll a, ll b, ll mod1) {ll res = 1; if(b < 0)b = 0; a %= mod1; assert(b >= 0);
// for(; b; b >>= 1){if (b & 1) res = res * a % mod1;a = a * a % mod1;} return res;}
// ll mypow(ll a, ll b) {ll res = 1; if(b < 0)b = 0;assert(b >= 0);
// for(; b; b >>= 1){if(b & 1) res = res * a;a = a * a;} return res;}
// #define pb push_back
// #define fi first
// #define se second
// #define all(x) x.begin(), x.end()
// #define rall(x) x.rbegin(), x.rend()

// // ifstream fin("input.txt");
// // ofstream fout("output.txt");
// // #define cin fin
// // #define cout fout

// const ll infll = 0x7fffffffffffffff;
// const int inf = 0x7fffffff;
// const int maxn = 2e3 + 5;

// char c[maxn][maxn];
// int d[maxn][maxn];
// int dx[] = {0, 0, -1, 1};
// int dy[] = {-1, 1, 0, 0};
// set<pii> in_q;


// int main() {

//     FastEverything
//     HighPrecision
//     int test = 1;
//     // cin >> test;
//     for (int tt = 1; tt <= test; ++tt) {

//         int n, m, x, y, l, r;
//         cin >> n >> m >> x >> y >> l >> r;
//         for (int i = 1; i <= n; ++i) {
//             for (int j = 1; j <= m; ++j) {
//                 cin >> c[i][j];
//                 d[i][j] = inf;
//             }
//         }

//         deque<pii> q;
//         q.push_back({x, y});
//         d[x][y] = 0;
//         in_q.insert({x, y});
//         while (!q.empty()) {
//             auto top = q.front();
//             q.pop_front();
//             in_q.erase(top);
//             for (int i = 0; i < 4; ++i) {
//                 int x = top.fi + dx[i];
//                 int y = top.se + dy[i];
//                 if (x < 1 || x > n || y < 1 || y > m) continue;
//                 if (c[x][y] == '*') continue;
//                 int cost = (i == 0);
//                 if (d[x][y] > d[top.fi][top.se] + cost) {
//                     d[x][y] = d[top.fi][top.se] + cost;
//                     if (!in_q.count({x, y})) {
//                         if (cost) {
//                             q.push_back({x, y});
//                         }
//                         else {
//                             q.push_front({x, y});
//                         }
//                     }
//                 }
//             }
//         }

//         int ans = 0;
//         for (int i = 1; i <= n; ++i) {
//             for (int j = 1; j <= m; ++j) {
//                 if (c[i][j] == '*') continue;
//                 int l1 = d[i][j];
//                 int r1 = l1 + j - y;
//                 ans += (l1 <= l && r1 <= r);
//             }
//         }

//         cout << ans << '\n';

        
//     }

//     return 0;
// }
