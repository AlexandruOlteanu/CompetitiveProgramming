/*
  ░█████╗░██╗░░░░░███████╗██╗░░██╗░█████╗░███╗░░██╗██████╗░██████╗░██╗░░░██╗██╗███╗░░██╗██╗░░░██╗
  ██╔══██╗██║░░░░░██╔════╝╚██╗██╔╝██╔══██╗████╗░██║██╔══██╗██╔══██╗██║░░░██║██║████╗░██║██║░░░██║
  ███████║██║░░░░░█████╗░░░╚███╔╝░███████║██╔██╗██║██║░░██║██████╔╝██║░░░██║██║██╔██╗██║╚██╗░██╔╝
  ██╔══██║██║░░░░░██╔══╝░░░██╔██╗░██╔══██║██║╚████║██║░░██║██╔══██╗██║░░░██║██║██║╚████║░╚████╔╝░
  ██║░░██║███████╗███████╗██╔╝╚██╗██║░░██║██║░╚███║██████╔╝██║░░██║╚██████╔╝██║██║░╚███║░░╚██╔╝░░
  ╚═╝░░╚═╝╚══════╝╚══════╝╚═╝░░╚═╝╚═╝░░╚═╝╚═╝░░╚══╝╚═════╝░╚═╝░░╚═╝░╚═════╝░╚═╝╚═╝░░╚══╝░░░╚═╝░░░
  They forged me in fire, they broke me in battle, yet here I rise, Invictus!
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

// Link: https://codeforces.com/contest/2094/problem/G
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// Useful
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
#define LightningFastReadWrite ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
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

deque<ll> v1, v2;

int main() {

    LightningFastReadWrite
    HighPrecision
    int test = 1;
    cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        v1.clear();
        v2.clear();
        int q;
        cin >> q;
        bool reversed = false;
        ll ans1 = 0, ans2 = 0;
        ll sumt = 0;

        while (q--) {
            int c;
            cin >> c;
            if (c == 3) {
                ll x;
                cin >> x;
                if (!reversed) {
                    v1.push_back(x);
                    ans1 += x * v1.size();


                    ans2 += sumt;
                    ans2 += x;
                    v2.push_front(x);
                } else {
                    v2.push_back(x);
                    ans2 += x * v2.size();


                    ans1 += sumt;
                    ans1 += x;
                    v1.push_front(x);
                }
                sumt += x;
            } else if (c == 1) {
                if (!reversed) {
                    if (v1.size() > 1) {
                        ans1 -= (v1.size() - 1) * v1.back();
                        ans1 += sumt - v1.back();
                        ll x = v1.back();
                        v1.pop_back();
                        v1.push_front(x);
                    }

                    ll x = v2.front();
                    v2.pop_front();
                    v2.push_back(x);
                    ans2 -= sumt;
                    ans2 += x * v2.size();
                } else {
                    if (v2.size() > 1) {
                        ans2 -= (v2.size() - 1) * v2.back();
                        ans2 += sumt - v2.back();
                        ll x = v2.back();
                        v2.pop_back();
                        v2.push_front(x);
                    }

                    ll x = v1.front();
                    v1.pop_front();
                    v1.push_back(x);
                    ans1 -= sumt;
                    ans1 += x * v1.size();
                }
            } else {
                reversed = !reversed;
            }

            if (!reversed) {
                cout << ans1 << '\n';
            } else {
                cout << ans2 << '\n';
            }

        }

    }

    return 0;
}