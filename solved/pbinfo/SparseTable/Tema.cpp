/*
    Programmer : Alexandru Olteanu
    Problem Link : https://www.pbinfo.ro/probleme/4395/tema
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

ifstream fin("tema.in");
ofstream fout("tema.out");
#define cin fin
#define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
const int maxn = 1e5 + 5;

/* 
    Template created by Alexandru Olteanu
*/
template<typename A>
struct SparseTable{
    
    vector<vector<A>> matrix;
    vector<A> array;
    vector<A> log_values;
    
    SparseTable(int n){
        int max_log = 0, power = 1;
        while(power <= n){
            power <<= 1;
            ++max_log;
        }
        array.resize(n + 1);
        log_values.resize(n + 1);
        matrix.resize(n + 1);
        for(int i = 1; i <= n; ++i){
            matrix[i].resize(max_log);
        }
    }
    A func(A a, A b){
        return __gcd(a, b);//Probably it needs changes
    }
    
    void build(int l, int r){
        int max_log = 0, power = 1;
        int n = r - l + 1;
        while(power <= n){
            power <<= 1;
            ++max_log;
        }
        int number = 0;
        power = 1;
        for(int i = 1; i <= n; ++i){
            while(power <= i){
                power <<= 1;
                ++number;
            }
            power >>= 1;
            --number;
            log_values[i] = number;
        }
        for(int j = 0; j < max_log; ++j){
            for(int i = l; i <= r - (1 << j) + 1; ++i){
                if(j == 0){
                    matrix[i][j] = array[i];
                    continue;
                }
                matrix[i][j] = func(matrix[i][j - 1], matrix[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    ll get(A start, A finish){
        ll distance = finish - start + 1;
        ll biggest_power = log_values[distance];
        return func(matrix[start][biggest_power], matrix[finish - (1 << biggest_power) + 1][biggest_power]);
    }
};


int d[1000001];
int a[maxn];

int main() {

    for (int i = 2; i <= 1000000; ++i) {
        if (!d[i]) {
            for (int j = i; j <= 1000000; j += i) {
                d[j] = i;
            }
        }
    }


    FastEverything
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int c, n;
        ll k;
        cin >> c >> n >> k;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }

        if (c == 1) {
            ll sum = 0, sum1 = 0;
            int ans = 0;
            int i = 1, j = 1;
            while (i <= n) {
                if (i > j) j = i;
                while (j <= n) {
                    if (d[a[j]] == a[j]) {
                        sum += a[j];
                    }
                    else if (a[j] != 1) {
                        sum1 += a[j];
                    }
                    if (sum1 == 0 || (sum <= k / sum1)) {
                        ++j;
                    }
                    else {
                        if (d[a[j]] == a[j]) {
                            sum -= a[j];
                        }
                        else if (a[j] != 1) {
                            sum1 -= a[j];
                        }
                        break;
                    }
                }
                ans = max(ans, j - i);
                if (j > i) {
                    if (d[a[i]] == a[i]) sum -= a[i];
                    else if (a[i] != 1) sum1 -= a[i];
                }
                ++i;
            }

            cout << ans << '\n';
            return 0;
        }

        for (int i = 1; i <= n; ++i) {
            if (d[a[i]] == a[i] || a[i] == 1) continue;
            int maxi = d[a[i]];
            int mini = inf;
            int x = a[i];
            while (x != 1) {
                mini = d[x];
                int d1 = d[x];
                while (x % d1 == 0) x /= d1;
            }
            a[i] = maxi * mini;
        }

        SparseTable<int> st(n);
        for (int i = 1; i <= n; ++i) {
            st.array[i] = a[i];
        }
        st.build(1, n);
        int ans = 0;
        int i = 1, j = 1;
        int start = -1, end = -1;
        while (i <= n) {
            if (j < i) j = i;
            while (j <= n && st.get(i, j) > 1) {
                ++j;
            }
            if (j - i >= ans) {
                ans = j - i;
                start = i;
                end = j - 1;
            }
            ++i;
        }

        cout << start << " " << end << '\n';
        
    }

    return 0;
}
