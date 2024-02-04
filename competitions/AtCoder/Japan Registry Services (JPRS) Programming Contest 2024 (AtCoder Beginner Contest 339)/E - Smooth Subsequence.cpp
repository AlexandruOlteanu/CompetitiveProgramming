/*
    Programmer : Alexandru Olteanu
    Problem Link : https://atcoder.jp/contests/abc339/tasks/abc339_e
*/
#include <bits/stdc++.h>
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
#define HighPrecision cout << fixed << setprecision(17);
typedef long long ll;
typedef pair<int, int> pii;
const int mod = 1000000007;
const int mod2 = 100000000;
const int md = 998244353LL;
ll mypowr(ll a, ll b, ll mod1) {ll res = 1; if(b < 0)b = 0; a %= mod1; assert(b >= 0);
for(; b; b >>= 1){if (b & 1) res = res * a % mod1;a = a * a % mod1;} return res;}
ll mypow(ll a, ll b) {ll res = 1; if(b < 0)b = 0;assert(b >= 0);
for(; b; b >>= 1){if(b & 1) res = res * a;a = a * a;} return res;}
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

// ifstream fin("input.txt");
// ofstream fout("output.txt");
// #define cin fin
// #define cout fout

const ll infll = 0x7fffffffffffffff;
const int inf = 0x7fffffff;
const int maxn = 2e5 + 5;

/*
    Template created by Alexandru Olteanu

    How to use: 
        SegmentTree<int> st(n);
        st.get(start, end);

        st.array[index] = value;
        st.update(index, index)
*/
template<typename A>
struct SegmentTree{
    
    vector<A> array;
    struct TreeNode {
        int val;
    };
    vector<TreeNode> tree;
    vector<A> lazy;
    int N;

    SegmentTree(int n){
        N = n;
        array.resize(n + 1, 0);
        tree.resize(4 * (n + 1) + 1);
        lazy.resize(4 * (n + 1) + 1);
    }

    void build(int start, int end) {
        buildX(1, start, end);
    }

    void update(int start, int end) {
        updateX(1, 1, N, start, end);
    }

    TreeNode get(int start, int end) {
        return getX(1, 1, N, start, end);
    }
    

private:
    TreeNode func(TreeNode a, TreeNode b){
        TreeNode res;
        res.val = max(a.val, b.val); //Probably it needs changes
        return res;      
    }

    void buildX(int node, int l, int r){
        if(l == r){
            tree[node].val = array[l]; //Probably it needs changes
            return;
        }
        int mid = l + (r - l) / 2;
        buildX(node * 2, l, mid);
        buildX(node * 2 + 1, mid + 1, r);
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
                tree[node].val = array[l];    //Probably it needs changes
            }
            lazy[node] = 0;
        }
        return;
    }

    void updateX(int node, int l, int r, int L, int R){
        push(node, l, r);
        if(r < L || l > R)return;
        if(l >= L && r <= R){
            lazy[node] ^= 1;
            push(node, l, r);
            return;
        }
        int mid = l + (r - l) / 2;
        updateX(node * 2, l, mid, L, R);
        updateX(node * 2 + 1, mid + 1, r, L, R);
        tree[node] = func(tree[node * 2], tree[node * 2 + 1]);
        return;
    }

    TreeNode getX(int node, int l, int r, int L, int R){
        push(node, l, r);
        if(l >= L && r <= R){
            return tree[node];
        }
        int mid = l + (r - l) / 2;
        if(mid < L){
            return getX(node * 2 + 1, mid + 1, r, L, R);
        }
        if(mid >= R){
            return getX(node * 2, l, mid, L, R);
        }
        return func(getX(node * 2, l, mid, L, R), getX(node * 2 + 1, mid + 1, r, L, R));
    }
};

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    // cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        SegmentTree<int> st(500000);
        for (int i = 1; i <= 500000; ++i) {
            st.array[i] = 0;
        }

        int n, d;
        cin >> n >> d;
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            int x;
            cin >> x;
            int start = x - d, end = x + d;
            start = max(start, 1);
            end = min(end, 500000);
            auto res = st.get(start, end);
            ans = max(ans, res.val + 1);
            st.array[x] = res.val + 1;
            st.update(x, x);
        }

        cout << ans << '\n';
        
    }

    return 0;
}
