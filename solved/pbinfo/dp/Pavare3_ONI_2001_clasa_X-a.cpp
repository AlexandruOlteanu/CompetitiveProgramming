/*
    Programmer : Alexandru Olteanu (OltAlexandru)
    Problem Link : https://www.pbinfo.ro/probleme/3234/pavare3
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

ifstream fin("pavare.in");
ofstream fout("pavare.out");
#define cin fin
#define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 2e5 + 5;

const int Dig = 10;
 
struct bigint {
    deque<int> num;
    int sign = 1;
 
    //constructor
    bigint() {
    }
    bigint(long long x) {
        num.clear();
        if (x < 0)
            sign = -1, x = -x;
        if (x == 0)
            num.push_back(x);
        while (x > 0) {
            num.push_back(x % Dig);
            x /= Dig;
        }
    }
    bigint(int x) {
        num.clear();
        if (x < 0)
            sign = -1, x = -x;
        if (x == 0)
            num.push_back(x);
        while (x > 0) {
            num.push_back(x % Dig);
            x /= Dig;
        }
    }
    bigint(const bigint &x) {
        sign = x.sign;
        num = x.num;
    }
 
    // change to int
    friend int BtoI(const bigint &x) {
        int res = 0, t = 1;
        for (int i = 0; i < x.num.size(); i++)
            res += t * x.num[i];
        return res;
 
    }
 
    //absolut
    friend bigint abs(const bigint &x) {
        bigint res = x;
        res.sign = 1;
        return res;
    }
 
    //clear 0
    void clr() {
        while (!num.empty() and !num.back())
            num.pop_back();
    }
 
    //normalize
    void normalize() {
        (*this).clr();
        int carry = 0;
        for (int i = 0; i < num.size(); i++) {
            int t = num[i] + carry;
            if (t < 0) {
                t += Dig;
                carry = -1;
                num[i] = t;
            }
            else {
                num[i] = t % Dig;
                carry = t / Dig;
            }
        }
        if (carry > 0)
            num.push_back(carry);
        if (carry < 0) {
            sign *= -1;
            num.push_back(-carry);
        }
        (*this).clr();
        if (num.empty())
            sign = 1;
 
    }
 
    //is 0
    bool isZero() {
        (*this).normalize();
        return num.empty();
    }
 
    //compare operators
    bool operator<(const bigint &x) const {
        bigint a = (*this);
        bigint b = x;
        a.normalize();
        b.normalize();
        if (a.sign != b.sign)
            return a.sign < b.sign;
        bool res = false, flag = false;
        if (a.num.size() != b.num.size()) {
            res = (a.num.size() < b.num.size());
            flag = true;
        }
        else {
            for (int i = a.num.size() - 1; i >= 0; i--)
                if (a.num[i] != b.num[i]) {
                    flag = true;
                    res = (a.num[i] < b.num[i]);
                    break;
                }
        }
        if (!flag)
            return false;
        if (sign == -1)
            return !res;
        return res;
    }
    bool operator==(const bigint &x) const {
        bigint a = (*this);
        bigint b = x;
        a.normalize();
        b.normalize();
        if (a.sign == b.sign and a.num.size() == b.num.size()) {
            bool res = true;
            for (int i = 0; i < a.num.size() and res; i++)
                if (a.num[i] != b.num[i])
                    res = false;
            return res;
        }
        else
            return false;
    }
    bool operator<=(const bigint &x) const {
        return (((*this) < x) or ((*this) == x));
    }
    bool operator>(const bigint &x) const {
        return (!((*this) <= x));
    }
    bool operator>=(const bigint &x) const {
        return (!((*this) < x));
    }
    bool operator!=(const bigint &x) const {
        return (!((*this) == x));
    }
    friend bigint max(bigint &x, bigint &y) {
        return (x > y? x: y);
    }
    friend bigint min(bigint &x, bigint &y) {
        return (x < y? x: y);
    }
 
    //math operators
    bigint operator+(const bigint &x) const {
        if (sign == x.sign) {
            bigint res;
            res.sign = sign;
            for (int i = 0; i < max(x.num.size(), num.size()); i++) {
                int t = (i >= num.size()? 0: num[i]) + (i >= x.num.size()? 0: x.num[i]);
                res.num.push_back(t);
            }
            res.normalize();
            return res;
        }
        if (sign == -1)
            return x - abs(*this);
        else
            return (*this) - abs(x);
    }
    bigint operator-(const bigint &x) const {
        if (sign == x.sign) {
            bigint res, a = abs(*this), b = abs(x);
            a.clr();
            b.clr();
            if (a == b) {
                res = 0;
                return res;
            }
            if (b < a) {
                for (int i = 0; i < a.num.size(); i++) {
                    int t = a.num[i] - (i >= b.num.size()? 0: b.num[i]);
                    res.num.push_back(t);
                }
                res.normalize();
            }
            else {
                for (int i = 0; i < b.num.size(); i++) {
                    int t = b.num[i] - (i >= a.num.size()? 0: a.num[i]);
                    res.num.push_back(t);
                }
                res.normalize();
                res.sign *= -1;
            }
            if (sign == -1)
                res.sign *= -1;
            return res;
        }
        if (sign == -1) {
            bigint res = abs(*this) + x;
            res.sign *= -1;
            return res;
        }
        else
            return (*this) + abs(x);
    }
    void operator+=(const bigint &x) {
        (*this) = (*this) + x;
    }
    void operator-=(const bigint &x) {
        (*this) = (*this) - x;
    }
    void operator++() {
        (*this) += 1;
    }

    
    friend ostream& operator<<(ostream &stream, bigint &x) {
        if (x.num.empty()) {
            stream << 0;
            return stream;
        }
        if (!x.num.empty() and x.sign == -1)
            stream << '-';
        stream << (x.num.empty() ? 0 : x.num.back());
        for (int i = (int) x.num.size() - 2; i >= 0; i--)
            stream  << x.num[i];
        return stream;
    }
 
};



vector<vector<int>> ans;
vector<int> sol;

void bkt(int x) {
    if (x == 3) {
        ans.pb(sol);
        return;
    }
    for (int i = 1; i <= 4; ++i) {
        if (x != 0) {
            if (sol.back() == 4 && i != 2) {
                continue;
            }
            if (i == 1 || i == 3) {
                sol.pb(i);
                bkt(x + 1);
                sol.pop_back();
                continue;
            }
            if (i == 2 && sol.back() == 4) {
                sol.pb(i);
                bkt(x + 1);
                sol.pop_back();
                continue;
            }
            if (i == 4 && x + 1 != 3) {
                sol.pb(i);
                bkt(x + 1);
                sol.pop_back();
                continue;
            }
            continue;
        }
        if (i != 2) {
            sol.pb(i);
            bkt(x + 1);
            sol.pop_back();
            continue;
        }
    }
}
set<pair<int, int>> s;
bigint dp[201][15];

int main() {



    FastEverything
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int n;
        cin >> n;
        n *= 2;
        bkt(0);
        int k = ans.size();
        vector<int> a, b;
        for (int i = 1; i <= k; ++i) {
            a = ans[i - 1];
            for (int j = i; j <= k; ++j) {
                b = ans[j - 1];
                bool ok = true;
                for (int t = 0; t < 3; ++t) {
                    if ((a[t] == 1 && b[t] != 3) || (b[t] == 3 && a[t] != 1)) {
                        ok = false;
                    }
                }
                if (ok) {
                    s.insert({i, j});
                }
                if (i != j) {
                    ok = true;
                    for (int t = 0; t < 3; ++t) {
                        if ((b[t] == 1 && a[t] != 3) || (a[t] == 3 && b[t] != 1)) {
                            ok = false;
                        }
                    }
                    if (ok) {
                        s.insert({j, i});
                    }
                }
            }
        }
        for (int i = 0; i < k; ++i) {
            bool ok = true;
            for (auto x : ans[i]) {
                if (x == 3) {
                    ok = false;
                    break;
                }
            }
            dp[1][i + 1] = ok;
        }

        for (int i = 2; i < n; ++i) {
            for (int j = 1; j <= k; ++j) {
                for (int t = 1; t <= k; ++t) {
                    if (s.count({t, j})) {
                        dp[i][j] += dp[i - 1][t];
                    }
                }
            }
        }
        for (int j = 1; j <= k; ++j) {
            bool ok = true;
            for (auto x : ans[j - 1]) {
                if (x == 1) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                for (int t = 1; t <= k; ++t) {
                    if (s.count({t, j}) && dp[n - 1][t] > 0) {
                        dp[n][j] += dp[n - 1][t];
                    }
                }
            }
        }

        bigint cnt = 0;
        for (int i = 1; i <= k; ++i) {
            cnt += dp[n][i];
        }
        cout << cnt << '\n';
    }

    return 0;
}