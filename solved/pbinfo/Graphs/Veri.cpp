/*
    Programmer : Alexandru Olteanu
    Problem Link : https://www.pbinfo.ro/probleme/4411/veri
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

ifstream fin("veri.in");
ofstream fout("veri.out");
#define cin fin
#define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 5e3 + 5;

vector<int> v[maxn], v1[maxn];

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int c, n, m;
        cin >> c >> n >> m;
        int s, a, b;
        cin >> s >> a >> b;
        for (int i = 1; i <= m; ++i) {
            int x, y;
            cin >> x >> y;
            v[x].push_back(y);
            v1[y].push_back(x);
        }


        vector<vector<int>> dist(n + 1, vector<int>(n + 1, -1));
        vector<int> cycle(n + 1, -1);
        vector<vector<int>> ps(n + 1, vector<int>(n + 1, -1));

        queue<int> q;
        for (int i = 1; i <= n; ++i) {
            q.push(i);
            dist[i][i] = 0;
            while (!q.empty()) {
                int top = q.front();
                q.pop();
                for (auto u : v[top]) {
                    if (u == i && cycle[i] < 0) {
                        cycle[i] = top;
                    }
                    if (dist[i][u] == -1) {
                        dist[i][u] = dist[i][top] + 1;
                        ps[i][u] = top;
                        q.push(u);
                    } 
                }
            }
        }
        

        vector<int> dist1(n + 1, -1), dist2(n + 1, -1), p1(n + 1, -1), p2(n + 1, -1);
        q.push(a);
        dist1[a] = 0;
        p1[a] = -1;
        while (!q.empty()) {
            int top = q.front();
            q.pop();
            for (auto u : v1[top]) {
                if (dist1[u] == -1) {
                    dist1[u] = dist1[top] + 1;
                    p1[u] = top;
                    q.push(u); 
                }
            }
        }

        q.push(b);
        dist2[b] = 0;
        p2[b] = -1;
        while (!q.empty()) {
            int top = q.front();
            q.pop();
            for (auto u : v1[top]) {
                if (dist2[u] == -1) {
                    dist2[u] = dist2[top] + 1;
                    p2[u] = top;
                    q.push(u); 
                }
            }
        }

        int ans = inf, nx = -1;
        for (int i = 1; i <= n; ++i) {
            if (dist[s][i] != inf && cycle[i] != -1 && dist1[i] != -1 && dist2[i] != -1) {
                int cost = dist[s][i] + dist[i][cycle[i]] + 1 + max(dist1[i], dist2[i]);
                if (cost < ans) {
                    ans = cost;
                    nx = i;
                }
            }
        }

        if (c == 1) {
            cout << ans << '\n';
            return 0;
        }

        deque<int> res;
        int cur = nx;
        while (cur != -1) {
            res.push_front(cur);
            cur = ps[s][cur];
        }
        cur = cycle[nx];
        vector<int> aux;
        while (cur != nx) {
            aux.push_back(cur);
            cur = ps[nx][cur];
        }
        while (!aux.empty()) {
            res.push_back(aux.back());
            aux.pop_back();
        }
        res.push_back(nx);

        cout << res.size() - 1 << '\n';
        for (auto u : res) {
            cout << u << " ";
        }
        cout << '\n';

        res.clear();
        cur = nx;
        while (cur != -1) {
            res.push_back(cur);
            cur = p1[cur];
        }

        cout << res.size() - 1 << '\n';
        for (auto u : res) {
            cout << u << " ";
        }

        cout << '\n';
        res.clear();
        cur = nx;
        while (cur != -1) {
            res.push_back(cur);
            cur = p2[cur];
        }

        cout << res.size() - 1 << '\n';
        for (auto u : res) {
            cout << u << " ";
        }

        cout << '\n';

        
    }

    return 0;
}