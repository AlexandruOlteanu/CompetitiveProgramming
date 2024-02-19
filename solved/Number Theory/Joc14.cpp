/*
    Programmer : Alexandru Olteanu
    Problem Link : https://www.pbinfo.ro/probleme/4590/joc14
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

ifstream fin("joc.in");
ofstream fout("joc.out");
#define cin fin
#define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 2e5 + 5;

int solve(int x) {
    int d = 2;
    int mx = 0, nr = 0;
    while (x != 1) {
        if (x % d == 0) {
            int p = 0;
            while (x % d == 0) x /= d, ++p;
            if (p == mx) {
                nr = max(nr, d);
            }
            if (p > mx) {
                mx = p;
                nr = d;
            }
        }
        if (d == 2) d = 3;
        else d += 2;
        if (d * d > x) d = x;
    }

    return nr;
}

int main() {



    FastEverything
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int n;
        cin >> n;
        vector<int> r1(n + 1), r2(n + 1);
        for (int i = 1; i <= n; ++i) {
            int x; cin >> x;
            r1[i] = solve(x);
        }
        int s1 = 0, s2 = 0;
        for (int i = 1; i <= n; ++i) {
            int x; cin >> x;
            r2[i] = solve(x);
            if (r1[i] == r2[i]) s1 += 5, s2 += 5;
            if (r1[i] < r2[i]) s2 += 10;
            if (r1[i] > r2[i]) s1 += 10;
        }
        sort(all(r1));
        sort(all(r2));

        if (s1 < s2) {
            cout << "2 ";
        }
        if (s1 > s2) {
            cout << "1 ";
        }
        if (s1 == s2) {
            if (r1.back() > r2.back()) cout << "1 ";
            else cout << "2 ";
        }
        cout << max(s1, s2) << " ";
        cout << max(r1.back(), r2.back()) << '\n';
        
    }

    return 0;
}
