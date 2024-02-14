/*
    Programmer : Alexandru Olteanu
    Problem Link : https://www.pbinfo.ro/probleme/4408/aeriana
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

ifstream fin("aeriana.in");
ofstream fout("aeriana.out");
#define cin fin
#define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 1e3 + 5;

vector<vector<string>> s;

int timeDif(int h1, int m1, int h2, int m2) {

    if (h1 == h2) {
        if (m1 <= m2) {
            return m2 - m1;
        }
        return 24 * 60 - (m1 - m2);
    }

    if (h2 > h1) {
        return (h2 - h1) * 60 + m2 - m1;
    }

    return (24 - h1 + h2) * 60 + m2 - m1;
}

int sumCif(int x) {
    int s = 0;
    while (x) {
        s += x % 10;
        x /= 10;
    }

    return s;
}

bool prime(int x) {
    if (x <= 1) return false;
    if (x <= 3) return true;
    if (x % 2 == 0 || x % 3 == 0) return false;
    for (int i = 5; i * i <= x; ++i) {
        if (x % i == 0 || x % (i + 2) == 0) return false;
    }

    return true;
}

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int c, n;
        cin >> c >> n;
        s.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            string a, b, h1, m1, h2, m2;
            cin >> a >> b >> h1 >> m1 >> h2 >> m2;
            s[i].push_back(a);
            s[i].push_back(b);
            s[i].push_back(h1);
            s[i].push_back(m1);
            s[i].push_back(h2);
            s[i].push_back(m2);
        }

        if (c == 1) {
           int ans = 0;
           for (int i = 1; i <= n; ++i) {
               int h1 = stoi(s[i][2]);
               int h2 = stoi(s[i][4]);
               int m1 = stoi(s[i][3]);
               int m2 = stoi(s[i][5]);
               int t = timeDif(h1, m1, h2, m2);
               ans = max(ans, t);
           } 
           cout << ans / 60 << " " << ans % 60 << '\n';
           return 0;
        }

        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            int a = stoi(s[i][0]);
            int b = stoi(s[i][1]);
            int h1 = stoi(s[i][2]);
            int h2 = stoi(s[i][4]);
            int m1 = stoi(s[i][3]);
            int m2 = stoi(s[i][5]);
            bool is = prime(a);
            int s = sumCif(a);
            bool is1 = (s != 0 && b % s == 0);
            if (is && is1) {
                swap(h1, h2);
                swap(m1, m2);
            }

             int t = timeDif(h1, m1, h2, m2);
            ans = max(ans, t);
        }

        cout << ans / 60 << " " << ans % 60 << '\n';
        
    }

    return 0;
}
