/*
    Programmer : Alexandru Olteanu
    Problem : https://codeforces.com/contest/622/problem/C
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// GCC Optimizations
// #pragma GCC optimize("Ofast");
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

struct t {
    pii x = {-1, -1};
    pii y = {-1, -1};
};

template<typename A>
struct SegmentTree{
    vector<A> array;
    vector<t> tree;
    vector<A> lazy;

    SegmentTree(int n){
        array.resize(n + 1, 0);
        tree.resize(4 * (n + 1) + 1);
        lazy.resize(4 * (n + 1) + 1, 0);
    }

    t func(t a, t b){
        t res;
        vector<pii> v;
        if (a.x.fi != -1) v.pb(a.x);
        if (a.y.fi != -1) v.pb(a.y);
        if (b.x.fi != -1) v.pb(b.x);
        if (b.y.fi != -1) v.pb(b.y);
        if (v.empty()) return res;
        sort(all(v));
        res.x = {v[0].fi, v[0].se}, res.y = {v.back().fi, v.back().se};
        if (res.y.fi == res.x.fi) res.y = {-1, -1};
        return res;
    }

    void build(int node, int l, int r){
        if(l == r){
            tree[node].x = {array[l], l};
            tree[node].y = {-1, -1};
            return;
        }
        int mid = l + (r - l) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        tree[node] = func(tree[node * 2], tree[node * 2 + 1]);
        return;
    }

    void push(int node, int l, int r){
        if(lazy[node] != 0){
            if(l != r){
                tree[node] = func(tree[node * 2], tree[node * 2 + 1]);
                lazy[node * 2] ^= 1;                    //Probably it needs changes
                lazy[node * 2 + 1] ^= 1;
            }
            else{
                tree[node].x = {array[l], l};   
                tree[node].y = {-1, -1};
            }
            lazy[node] = 0;
        }
        return;
    }

    void update(int node, int l, int r, int L, int R){
        push(node, l, r);
        if(r < L || l > R)return;
        if(l >= L && r <= R){
            lazy[node] ^= 1;
            push(node, l, r);
            return;
        }
        int mid = l + (r - l) / 2;
        update(node * 2, l, mid, L, R);
        update(node * 2 + 1, mid + 1, r, L, R);
        tree[node] = func(tree[node * 2], tree[node * 2 + 1]);
        return;
    }

    t get(int node, int l, int r, int L, int R){
        push(node, l, r);
        if(l >= L && r <= R){
            return tree[node];
        }
        int mid = l + (r - l) / 2;
        if(mid < L){
            return get(node * 2 + 1, mid + 1, r, L, R);
        }
        if(mid >= R){
            return get(node * 2, l, mid, L, R);
        }
        return func(get(node * 2, l, mid, L, R), get(node * 2 + 1, mid + 1, r, L, R));
    }
};

int a[maxn];

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin>>test;
    for (int tt = 1; tt <= test; ++tt) {

        int n, k;
        cin >> n >> k;
        SegmentTree<int> st(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> st.array[i];
        }

        st.build(1, 1, n);

        for (int i = 1; i <= k; ++i) {
            int l, r, x;
            cin >> l >> r >> x;
            t res = st.get(1, 1, n, l, r);
            if (res.x.fi != -1 && res.x.fi != x) {
                cout << res.x.se << '\n';
                continue;
            }
            if (res.y.fi != -1 && res.y.fi != x) {
                cout << res.y.se << '\n';
                continue;
            }
            cout << "-1\n";
        }


        
    }

    return 0;
} 