/*
    Template created by Alexandru Olteanu
*/
template<typename A>
struct SegmentTree{

    struct TreeNode {
        A val;
    };

    vector<TreeNode> array;
    vector<TreeNode> tree;
    vector<TreeNode> lazy;

    SegmentTree(int n){
        array.resize(n + 1);
        tree.resize(4 * (n + 1) + 1);
        lazy.resize(4 * (n + 1) + 1);
    }

    TreeNode applyFunction(TreeNode x, TreeNode y, int operation) {
        if (operation == 1) return function1(x, y);
        if (operation == 2) return function2(x, y);
    }

    // Maybe the function needs some changes
    TreeNode function1(TreeNode x, TreeNode y) {
        TreeNode res;
        res.val = x.val + y.val;
        return res;
    }

    TreeNode function2(TreeNode x, TreeNode y) {
        TreeNode res;
        if (x.val > y.val) {
            res = x;
        } else {
            res = y;
        }
        return res;
    }

    // maybe the operation needs to be changed by level;
    int changeOperationAfterLevel(int operation) {
        return operation;
    }

    void build(int node, int l, int r, int operation){
        if(l == r){
            tree[node] = array[l];
            return;
        }
        int mid = l + (r - l) / 2;
        build(node * 2, l, mid, p);
        build(node * 2 + 1, mid + 1, r, p);
        tree[node] = applyFunction(tree[node * 2], tree[node * 2 + 1], p);
        return;
    }

    void push(int node, int l, int r, int p){
        if(lazy[node] != 0){
            if(l != r){
                tree[node] = func(tree[node * 2], tree[node * 2 + 1], p);
                lazy[node * 2] ^= 1;                    //Probably it needs changes
                lazy[node * 2 + 1] ^= 1;
            }
            else{
                tree[node] = array[l];   
            }
            lazy[node] = 0;
        }
        return;
    }

    void update(int node, int l, int r, int L, int R, int p){
        push(node, l, r, p);
        if(r < L || l > R)return;
        if(l >= L && r <= R){
            lazy[node] ^= 1;
            push(node, l, r);
            return;
        }
        int mid = l + (r - l) / 2;
        update(node * 2, l, mid, L, R, p);
        update(node * 2 + 1, mid + 1, r, L, R, p);
        tree[node] = func(tree[node * 2], tree[node * 2 + 1], p);
        return;
    }

    A get(int node, int l, int r, int L, int R, int p){
        push(node, l, r, p);
        if(l >= L && r <= R){
            return tree[node];
        }
        int mid = l + (r - l) / 2;
        if(mid < L){
            return get(node * 2 + 1, mid + 1, r, L, R, p);
        }
        if(mid >= R){
            return get(node * 2, l, mid, L, R, p);
        }
        return func(get(node * 2, l, mid, L, R, p), get(node * 2 + 1, mid + 1, r, L, R, p), p);
    }
};
