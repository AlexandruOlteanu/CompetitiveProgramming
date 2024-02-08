/*
    Programmer : Alexandru Olteanu
    Problem Link : https://codeforces.com/contest/1775/problem/D
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
const int maxn = 3e5 + 5;

int a[maxn];

vector<int> p[maxn];
vector<int> h[maxn];
int divi[maxn];

int par[maxn];

int main() {

    
    FastEverything
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        for (int i = 2; i <= 300000; ++i) {
            if (divi[i] == 0) {
                for (int j = i; j <= 300000; j += i) {
                    divi[j] = i;
                }
            }
        }

        int n;
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            int x;
            cin >> x;
            while (x != 1) {
                int d = divi[x];
                h[d].push_back(i);
                p[i].push_back(d);
                while (x % d == 0) x /= d;
            }
        }

        vector<int> dist(n + 1, inf);
        int x, y;
        cin >> x >> y;
        dist[x] = 0;
        queue<int> q;
        q.push(x);
        par[x] = -1;
        while (!q.empty()) {
            int top = q.front();
            q.pop();
            for (auto x : p[top]) {
                while (!h[x].empty()) {
                    int b = h[x].back();
                    if (dist[b] == inf) {
                        dist[b] = dist[top] + 1;
                        par[b] = top;
                        q.push(b);
                    }
                    h[x].pop_back();
                }
            }
        }

        if (dist[y] == inf) {
            cout << "-1\n";
            return 0;
        }

        cout << dist[y] + 1 << '\n';
        deque<int> res;
        while (y != -1) {
            res.push_front(y);
            y = par[y];
        }

        for (auto x : res) {
            cout << x << " ";
        }
        cout << '\n';

        
    }

    return 0;
}