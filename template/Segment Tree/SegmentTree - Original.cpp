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