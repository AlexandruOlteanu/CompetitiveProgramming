/*
    Template created by Alexandru Olteanu
    
    Usage Example:
    SegmentTree<int> st(n);
    st.array[i].val = value;
    st.build(1, n, operation);
    st.update(l, r, {value}, operation);
    st.get(l, r, operation);
*/

template<typename A>
struct SegmentTree {
    struct TreeNode {
        A val = 0;
    };

    int N;
    vector<TreeNode> array, tree, lazy;
    vector<bool> lazyStatus;

    SegmentTree(int n) {
        N = n;
        array.resize(N + 1);
        tree.resize(4 * (N + 1));
        lazy.resize(4 * (N + 1));
        lazyStatus.resize(4 * (N + 1), false);
    }

    void build(int start, int end, int operation) {
        buildX(1, start, end, operation, 1);
    }

    void update(int start, int end, TreeNode value, int operation) {
        updateX(1, 1, N, start, end, value, operation, 1);
    }

    TreeNode get(int start, int end, int operation) {
        return getX(1, 1, N, start, end, operation, 1);
    }

private:

    // Things you may need to change
    TreeNode applyFunction(TreeNode x, TreeNode y, int operation) {
        if (operation == 1) return function1(x, y);
        if (operation == 2) return function2(x, y);
        return TreeNode();
    }

    TreeNode function1(TreeNode x, TreeNode y) {
        TreeNode res;
        res.val = x.val + y.val;
        return res;
    }

    TreeNode function2(TreeNode x, TreeNode y) {
        TreeNode res;
        res.val = max(x.val, y.val);
        return res;
    }

    int changeOperationAfterLevel(int level, int operation) {
        return operation;
    }
    // End of things you may need to change


    void buildX(int node, int l, int r, int operation, int level) {
        if (l == r) {
            tree[node] = array[l];
            return;
        }
        int mid = (l + r) / 2;
        int nextOp = changeOperationAfterLevel(level, operation);
        buildX(node * 2, l, mid, nextOp, level + 1);
        buildX(node * 2 + 1, mid + 1, r, nextOp, level + 1);
        tree[node] = applyFunction(tree[node * 2], tree[node * 2 + 1], operation);
    }

    void push(int node, int l, int r, int operation) {
        if (!lazyStatus[node]) return;
        tree[node] = applyFunction(tree[node], lazy[node], operation);
        if (l != r) {
            lazy[node * 2] = applyFunction(lazy[node * 2], lazy[node], operation);
            lazy[node * 2 + 1] = applyFunction(lazy[node * 2 + 1], lazy[node], operation);
            lazyStatus[node * 2] = lazyStatus[node * 2 + 1] = true;
        }
        lazy[node] = TreeNode();
        lazyStatus[node] = false;
    }

    void updateX(int node, int l, int r, int L, int R, TreeNode value, int operation, int level) {
        push(node, l, r, operation);
        if (r < L || l > R) return;
        if (l >= L && r <= R) {
            lazy[node] = value;
            lazyStatus[node] = true;
            push(node, l, r, operation);
            return;
        }
        int mid = (l + r) / 2;
        int nextOp = changeOperationAfterLevel(level, operation);
        updateX(node * 2, l, mid, L, R, value, nextOp, level + 1);
        updateX(node * 2 + 1, mid + 1, r, L, R, value, nextOp, level + 1);
        tree[node] = applyFunction(tree[node * 2], tree[node * 2 + 1], operation);
    }

    TreeNode getX(int node, int l, int r, int L, int R, int operation, int level) {
        push(node, l, r, operation);
        if (r < L || l > R) return TreeNode();
        if (l >= L && r <= R) return tree[node];
        int mid = (l + r) / 2;
        int nextOp = changeOperationAfterLevel(level, operation);
        if (mid < L) return getX(node * 2 + 1, mid + 1, r, L, R, nextOp, level + 1);
        if (mid >= R) return getX(node * 2, l, mid, L, R, nextOp, level + 1);
        return applyFunction(
            getX(node * 2, l, mid, L, R, nextOp, level + 1),
            getX(node * 2 + 1, mid + 1, r, L, R, nextOp, level + 1),
            operation
        );
    }
};
