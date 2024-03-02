/*
    Programmer : Alexandru Olteanu
    Problem Link : https://codeforces.com/contest/1928/problem/C
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

// ifstream fin("input.in");
// ofstream fout("output.out");
// #define cin fin
// #define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 2e5 + 5;



int main() {



    FastEverything
    HighPrecision
    int test = 1;
    cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int n, x;
        cin >> n >> x;
        int n1 = n;
        n -= x;
        int ans = 0;
        set<int> s;
        if (n % 2 == 0) {
            n /= 2;
            for (int i = 1; i * i <= n; ++i) {
                if (n % i == 0) {
                    if (i + 1 >= x) {
                        ++ans;
                        s.insert(i + 1);
                    }   
                    if (n / i != i) {
                        if (n / i + 1 >= x) {
                            ++ans;
                            s.insert(n / i + 1);
                        }
                    }
                }
            }     
        }
        // cout << "F " << ans << '\n';
        n = n1;
        n += x;
        if (n % 2 == 0) {
            n /= 2;
            --n;
            for (int i = 1; i * i <= n; ++i) {
                if (n % i == 0) {
                    if (i + 1 >= x && !s.count(i + 1)) {
                        ++ans;
                    }
                    if (n / i != i) {
                        if (n / i + 1 >= x && !s.count(n / i + 1)) {
                            ++ans;
                        }
                    }
                }
            }
        }

        cout << ans << '\n';
        
    }

    return 0;
}

// 1 2 3 4 .. k   k-1 k-3 k-4 ... 2 

// p x

// k -> p % (2k - 2)  

// dif1 = 2k - 2p 
// dif2 = 2p - 2

// t = 2k - 4p - 2 

// x + 2k - 2

// f = x + r * (2k - 2)

// f - x = 2 * r * (k - 1)

// f = x + 2k - 2x + r * (2k - 2)
// f + x = 2k + 2 * r * (k - 1)
// (f + x) / 2 = k + r * (k - 1)
// (f + x) / 2 - 1 = (k - 1) * (r + 1)

 