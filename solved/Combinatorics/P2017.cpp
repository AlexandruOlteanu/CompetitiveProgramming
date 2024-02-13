/*
    Programmer : Alexandru Olteanu
    Problem Link : https://www.pbinfo.ro/probleme/2017/p2017
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll mypow(ll a, ll b) {ll res = 1; if(b < 0)b = 0;assert(b >= 0);
for(; b; b >>= 1){if(b & 1) res = res * a;a = a * a;} return res;}

ifstream fin("2017.in");
ofstream fout("2017.out");
#define cin fin
#define cout fout

ll sum[14];
short v[15];


int main() {

    sum[0] = 0;
    sum[1] = 1;
    for (int i = 2; i <= 13; ++i) {
        sum[i] = sum[i - 1];
        sum[i] += mypow(10, i - 1);
        sum[i] += 9 * (i - 1) * mypow(10, i - 2);
    }

    int test = 1;
    cin >> test;
    ll lo, hi;
    short c, cif, i, j;
    ll k, ans, x, mid, have, val;
    for (int tt = 1; tt <= test; ++tt) {

        cin >> c >> k;
        lo = 1, hi = 1e12;
        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;
            x = mid;
            cif = 0;
            while (x) {
                ++cif;
                x /= 10;
            } 
            have = sum[cif - 1];
            if (have >= k) {
                ans = mid;
                hi = mid - 1;
                continue;
            }
            x = mid;
            for (i = cif; i >= 1; --i) {
                v[i] = x % 10;
                x /= 10;
            }

            for (i = 1; i <= cif; ++i) {
                have += (v[i] - (i == 1)) * sum[cif - i];
                if (c < v[i]) {
                    have += mypow(10, cif - i);
                } 
                if (c == v[i]) {
                    val = 0;
                    for (j = i + 1; j <= cif; ++j) {
                        val = val * 10 + v[j];
                    }
                    have += val + 1;
                }
            }

            if (have >= k) {
                ans = mid;
                hi = mid - 1;
                continue;
            }
            lo = mid + 1;

        }

        cout << ans << '\n';
        
    }

    return 0;
}