/*
    Programmer : Alexandru Olteanu
    Problem : https://codeforces.com/contest/276/problem/C
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

int a[maxn];

/*
    Template created by Alexandru Olteanu
*/
template<typename A>
struct SegmentTree{
    vector<A> array;
    vector<A> tree;
    vector<A> lazy;

    SegmentTree(int n){
        array.resize(n + 1);
        tree.resize(4 * (n + 1) + 1);
        lazy.resize(4 * (n + 1) + 1);
    }

    A func(A a, A b){
        return (a < b ? a : b);     //Probably it needs changes
    }

    void build(int node, int l, int r){
        if(l == r){
            tree[node] = array[l];
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
            tree[node] += lazy[node];      //Probably it needs changes
            if(l != r){
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
        return;
    }

    void update(int node, int l, int r, int L, int R, A val){
        push(node, l, r);
        if(r < L || l > R)return;
        if(l >= L && r <= R){
            lazy[node] += val;
            push(node, l, r);
            return;
        }
        int mid = l + (r - l) / 2;
        update(node * 2, l, mid, L, R, val);
        update(node * 2 + 1, mid + 1, r, L, R, val);
        tree[node] = func(tree[node * 2], tree[node * 2 + 1]);
        return;
    }

    A get(int node, int l, int r, int L, int R){
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
            cin >> a[i];
        }
        for (int i = 1; i <= k; ++i) {
            int x, y;
            cin >> x >> y;
            st.update(1, 1, n, x, y, 1);
        }

        vector<int> sol;

        for (int i = 1; i <= n; ++i) {
            sol.pb(st.get(1, 1, n, i, i));
        }
        sort(all(sol));
        sort(a + 1, a + n + 1);
        ll p = 0;
        for (int i = 1; i <= n; ++i) {
            p += 1LL * a[i] * sol[i - 1];
        }

        cout << p << '\n';

        
        


        
    }

    return 0;
} 