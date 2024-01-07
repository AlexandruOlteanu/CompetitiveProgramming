/*
    Programmer : Alexandru Olteanu
    Problem : https://codeforces.com/contest/1547/problem/F
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// GCC Optimizations
// #pragma GCC optimize("Ofast")
// #pragma GCC target("fma,sse,sse2,sse3,ssse3,sse4,popcnt")
// #pragma GCC target("abm,mmx,avx,avx2,tune=native")
// #pragma GCC optimize(3)
// #pragma GCC optimize("inline")
// #pragma GCC optimize("-fgcse")
// #pragma GCC optimize("-fgcse-lm")
// #pragma GCC optimize("-fipa-sra")
// #pragma GCC optimize("-ftree-pre")
// #pragma GCC optimize("-ftree-vrp")
// #pragma GCC optimize("-fpeephole2")
// #pragma GCC optimize("-ffast-math")
// #pragma GCC optimize("-fsched-spec")
// #pragma GCC optimize("unroll-loops")
// Useful
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
#define FastEverything  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define HighPrecision cout<<fixed<<setprecision(17);
typedef long long ll;
typedef pair<int,int> pii;
ll const mod=1000000007LL;
ll const mod2 = 100000000LL;
ll const md=998244353LL;
ll mypowr(ll a,ll b, ll mod1) {ll res=1;if(b<0)b=0;a%=mod1; assert(b>=0);
for(;b;b>>=1){if(b&1)res=res*a%mod1;a=a*a%mod1;}return res;}
ll mypow(ll a,ll b) {ll res=1;if(b<0)b=0;assert(b>=0);
for(;b;b>>=1){if(b&1)res=res*a;a=a*a;}return res;}
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(), x.rend()

// ifstream in("input.txt");
// ofstream out("output.txt");
// #define cin in
// #define cout out

const ll infll = 9e18;
const int inf = 2e9;
const ll maxn = 2e5 + 5;

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


int a[maxn];

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    cin>>test;
    for (int tt = 1; tt <= test; ++tt) {

        int n;
        cin >> n;
        SparseTable<int> st(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> st.array[i];
        }

        st.build(1, n);

        int lo = 0, hi = n - 1;
        int ans = 0;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            bool ok = true;
            int val = -1;
            for (int i = 1; i <= n; ++i) {
                int x;
                int start = i, end = i + mid;
                if (end <= n) {
                    x = st.get(start, end);
                } 
                else {
                    x = __gcd(st.get(1, end - n), st.get(start, n));
                }
                if (val == -1)val = x;
                if (x != val) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                ans = mid;
                hi = mid - 1;
            }
            else {
                lo = mid + 1;
            }
        }

        cout << ans << '\n';
        
    }

    return 0;
} 