/*
    Programmer : Alexandru Olteanu
    Problem Link : https://www.pbinfo.ro/probleme/4448/legos
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

ifstream fin("legos.in");
ofstream fout("legos.out");
#define cin fin
#define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 2e5 + 5;



int main() {



    FastEverything
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int c, n;
        cin >> c >> n;
        if (c == 1) {
            int r = sqrt(n);
            cout << r * r << '\n';
            return 0;
        }
        
        if (c == 2) {
            int x = (n + 4) / 13;
            if (x == 0) {
                cout << "0\n";
                return 0;
            }
            int y = (n - 4 * x + 4) / x;
            int r = sqrt(y);
            y = r * r;
            cout << y + (x - 1) * (y + 4) << '\n';
            return 0;
        } 

        ll ans = 0;
        for (int i = 3; i * i <= n; ++i) {
            if (n % i == 0) {
                ++ans;
                if (i != n / i) ++ans;
            }
        }
        
        cout << ans << '\n';
        
    }

    return 0;
}

// 9 + (x - 1) * 13 <= n 
//             9 + 13x - 13 <= n 
//             13x <= n + 4
//             x <= (n + 4) / 13

// x etaje -> 9 + (x - 1) * 13
        //    y + (x - 1) * (y + 4) <= n 
        // xy + 4x - 4 <= n 
        // xy = n - 4x + 4 
        // y = (n - 4x + 4) / x;

