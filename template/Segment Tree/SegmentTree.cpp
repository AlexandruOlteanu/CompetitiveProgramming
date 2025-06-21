/*
    Template created by Alexandru Olteanu {AlexandruINV}
    
    Usage Example:
    SegmentTree<int> st(n);
    st.array[i].val = value;
    st.build(1, n, operation);
    st.update(l, r, {value}, operation);
    st.get(l, r, operation);
*/

// https://github.com/AlexandruOlteanu/CompetitiveProgramming/blob/main/template/Segment%20Tree/SegmentTree.cpp
template<typename A>
struct SegmentTree {
    struct TreeNode {
        A val;
    };

    int N;
    vector<TreeNode> array, tree, lazy;
    vector<bool> lazyStatus;

    SegmentTree(int n) {
        reset(n);
    }

    void reset(int n) {
        N = n;
        array.assign(N + 1, defaultTreeNode());
        tree .assign(4 * (N + 1), defaultTreeNode());
        lazy .assign(4 * (N + 1), defaultTreeNode());
        lazyStatus.assign(4 * (N + 1), false);
    }

    void build(int start, int end, int operation = 1) {
        buildX(1, start, end, operation, 1);
    }

    void update(int start, int end, TreeNode value, int operation = 1) {
        updateX(1, 1, N, start, end, value, operation, 1);
    }

    TreeNode getWithExcludedIndices(int start, int end, vector<int> excluded, int operation = 1) {
        excluded.erase(remove_if(excluded.begin(), excluded.end(),
                                  [&](int p) { return p < start || p > end; }),
                                  excluded.end());

        sort(excluded.begin(), excluded.end());
        excluded.erase(unique(excluded.begin(), excluded.end()), excluded.end());

        TreeNode res = defaultTreeNode();
        int curL = start;

        for (int p : excluded) {
            int curR = p - 1;
            if (curL <= curR) {
                TreeNode chunk = get(curL, curR, operation);
                res = applyFunction(res, chunk, operation);
            }
            curL = p + 1;
        }

        if (curL <= end) {
            TreeNode chunk = get(curL, end, operation);
            res = applyFunction(res, chunk, operation);
        }
        return res;
    }

    TreeNode get(int start, int end, int operation = 1) {
        return getX(1, 1, N, start, end, operation, 1);
    }

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

    TreeNode applyUpdateFunction(TreeNode x, TreeNode y) {
        TreeNode res;
        res = y;
        return res;
    }

    TreeNode defaultTreeNode() {
        TreeNode res;
        res.val = 0;
        return res;
    }

    int changeOperationAfterLevel(int level, int operation) { 
        return operation; 
    }
    // End of things you may need to change
private:
    void push(int node, int l, int r, int operation) {
        if (!lazyStatus[node]) return;
        tree[node] = applyUpdateFunction(tree[node], lazy[node]);
        if (l != r) {
            lazy[node * 2] = applyUpdateFunction(lazy[node * 2], lazy[node]);
            lazy[node * 2 + 1] = applyUpdateFunction(lazy[node * 2 + 1], lazy[node]);
            lazyStatus[node * 2] = lazyStatus[node * 2 + 1] = true;
        }
        lazy[node] = defaultTreeNode();
        lazyStatus[node] = false;
    }

    void buildX(int node, int l, int r, int operation, int level) {
        if (l == r) { tree[node] = array[l]; return; }
        int mid = (l + r) >> 1;
        int nextOp = changeOperationAfterLevel(level, operation);
        buildX(node * 2, l, mid, nextOp, level + 1);
        buildX(node * 2 + 1, mid + 1, r, nextOp, level + 1);
        tree[node] = applyFunction(tree[node * 2], tree[node * 2 + 1], operation);
    }

    void updateX(int node, int l, int r, int L, int R, TreeNode val, int operation, int level) {
        push(node, l, r, operation);
        if (r < L || l > R) return;
        if (l >= L && r <= R) {
            lazy[node] = applyUpdateFunction(lazy[node], val);
            lazyStatus[node] = true;
            push(node, l, r, operation);
            return;
        }
        int mid = (l + r) >> 1;
        int nextOp = changeOperationAfterLevel(level, operation);
        updateX(node * 2, l, mid, L, R, val, nextOp, level + 1);
        updateX(node * 2 + 1, mid + 1, r, L, R, val, nextOp, level + 1);
        tree[node] = applyFunction(tree[node * 2], tree[node * 2 + 1], operation);
    }

    TreeNode getX(int node, int l, int r, int L, int R, int operation, int level) {
        push(node, l, r, operation);
        if (r < L || l > R) {
            return defaultTreeNode();
        }
        if (l >= L && r <= R) return tree[node];
        int mid = l + (r - l) / 2;
        int nextOp = changeOperationAfterLevel(level, operation);
        if (mid < L)  return getX(node * 2 + 1, mid + 1, r, L, R, nextOp, level + 1);
        if (mid >= R) return getX(node * 2, l, mid, L, R, nextOp, level + 1);
        return applyFunction(
            getX(node * 2, l,     mid, L, R, nextOp, level + 1),
            getX(node * 2 + 1, mid + 1, r, L, R, nextOp, level + 1),
            operation
        );
    }
};
