/*
    Programmer : Alexandru Olteanu
    Problem Link : https://codeforces.com/contest/1548/problem/B
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

// ifstream fin("input.txt");
// ofstream fout("output.txt");
// #define cin fin
// #define cout fout

const long long infll = numeric_limits<long long> :: max();
const int inf = numeric_limits<int> :: max();
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
        A val;
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
        res.val = __gcd(a.val, b.val); //Probably it needs changes
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

ll a[maxn];

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    cin >> test;
    for (int tt = 1; tt <= test; ++tt) {

        int n;
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i]; 
        }
        if (n == 1) {
            cout << "1\n";
            continue;
        }
        SegmentTree<ll> st(n - 1);
        for (int i = 1; i < n; ++i) {
            st.array[i] = abs(a[i] - a[i + 1]);
        }

        st.build(1, n - 1);
        int ans = 0;
        for (int i = 1; i < n; ++i) {
            int lo = i + ans, hi = n - 1;
            ll g = st.get(i, lo).val;
            while (lo <= hi) {
                int mid = lo + (hi - lo) / 2;
                ll res = st.get(lo, mid).val;
                res = __gcd(res, g);
                if (res >= 2) {
                    g = res;
                    ans = mid - i + 1;
                    lo = mid + 1;
                }
                else {
                    hi = mid - 1;
                }
            }
        }

        cout << ans + 1 << '\n';
        


        
    }

    return 0;
}


// Optimal Solution (Using 2 Pointers)
// /*
//     Programmer : Alexandru Olteanu
// */
// #include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
// using namespace std;
// template<typename T>
// using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// // Useful
// mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
// #define FastEverything  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
// #define HighPrecision cout << fixed << setprecision(17);
// typedef long long ll;
// typedef pair<int, int> pii;
// const int mod = 1000000007;
// const int mod1 = 998244353;
// ll mypowr(ll a, ll b, ll mod1) {ll res = 1; if(b < 0)b = 0; a %= mod1; assert(b >= 0);
// for(; b; b >>= 1){if (b & 1) res = res * a % mod1;a = a * a % mod1;} return res;}
// ll mypow(ll a, ll b) {ll res = 1; if(b < 0)b = 0;assert(b >= 0);
// for(; b; b >>= 1){if(b & 1) res = res * a;a = a * a;} return res;}
// #define pb push_back
// #define fi first
// #define se second
// #define all(x) x.begin(), x.end()
// #define rall(x) x.rbegin(), x.rend()

// // ifstream fin("input.txt");
// // ofstream fout("output.txt");
// // #define cin fin
// // #define cout fout

// const long long infll = numeric_limits<long long> :: max();
// const int inf = numeric_limits<int> :: max();
// const int maxn = 2e5 + 5;

// /*
//     Template created by Alexandru Olteanu

//     How to use: 
//         SegmentTree<int> st(n);
//         st.get(start, end);

//         st.array[index] = value;
//         st.update(index, index)
// */
// template<typename A>
// struct SegmentTree{
    
//     vector<A> array;
//     struct TreeNode {
//         A val;
//     };
//     vector<TreeNode> tree;
//     vector<A> lazy;
//     int N;

//     SegmentTree(int n){
//         N = n;
//         array.resize(n + 1, 0);
//         tree.resize(4 * (n + 1) + 1);
//         lazy.resize(4 * (n + 1) + 1);
//     }

//     void build(int start, int end) {
//         buildX(1, start, end);
//     }

//     void update(int start, int end) {
//         updateX(1, 1, N, start, end);
//     }

//     TreeNode get(int start, int end) {
//         return getX(1, 1, N, start, end);
//     }
    

// private:

//     TreeNode func(TreeNode a, TreeNode b){
//         TreeNode res;
//         res.val = __gcd(a.val, b.val); //Probably it needs changes
//         return res;      
//     }

//     void buildX(int node, int l, int r){
//         if(l == r){
//             tree[node].val = array[l]; //Probably it needs changes
//             return;
//         }
//         int mid = l + (r - l) / 2;
//         buildX(node * 2, l, mid);
//         buildX(node * 2 + 1, mid + 1, r);
//         tree[node] = func(tree[node * 2], tree[node * 2 + 1]);
//         return;
//     }

//     void push(int node, int l, int r){
//         if(lazy[node] != 0){
//             if(l != r){
//                 tree[node] = func(tree[node * 2], tree[node * 2 + 1]);
//                 lazy[node * 2] ^= 1;                    //Probably it needs changes
//                 lazy[node * 2 + 1] ^= 1;
//             }
//             else{
//                 tree[node].val = array[l];    //Probably it needs changes
//             }
//             lazy[node] = 0;
//         }
//         return;
//     }

//     void updateX(int node, int l, int r, int L, int R){
//         push(node, l, r);
//         if(r < L || l > R)return;
//         if(l >= L && r <= R){
//             lazy[node] ^= 1;
//             push(node, l, r);
//             return;
//         }
//         int mid = l + (r - l) / 2;
//         updateX(node * 2, l, mid, L, R);
//         updateX(node * 2 + 1, mid + 1, r, L, R);
//         tree[node] = func(tree[node * 2], tree[node * 2 + 1]);
//         return;
//     }

//     TreeNode getX(int node, int l, int r, int L, int R){
//         push(node, l, r);
//         if(l >= L && r <= R){
//             return tree[node];
//         }
//         int mid = l + (r - l) / 2;
//         if(mid < L){
//             return getX(node * 2 + 1, mid + 1, r, L, R);
//         }
//         if(mid >= R){
//             return getX(node * 2, l, mid, L, R);
//         }
//         return func(getX(node * 2, l, mid, L, R), getX(node * 2 + 1, mid + 1, r, L, R));
//     }
// };

// ll a[maxn];

// int main() {

//     FastEverything
//     HighPrecision
//     int test = 1;
//     cin >> test;
//     for (int tt = 1; tt <= test; ++tt) {

//         int n;
//         cin >> n;
//         for (int i = 1; i <= n; ++i) {
//             cin >> a[i]; 
//         }
//         if (n == 1) {
//             cout << "1\n";
//             continue;
//         }
//         SegmentTree<ll> st(n - 1);
//         for (int i = 1; i < n; ++i) {
//             st.array[i] = abs(a[i] - a[i + 1]);
//         }

//         st.build(1, n - 1);

//         int ans = 0;
//         int i = 1, j = 1;
//         while (i < n) {
//             if (i > j) j = i;
//             while (j < n && st.get(i, j).val >= 2) {
//                 ++j;
//             }
//             ans = max(ans, j - i);
//             ++i;
//         }

//         cout << ans + 1 << '\n';
    
        
//     }

//     return 0;
// }

