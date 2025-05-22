/*
 * 1‑Indexed Binary‑Lifting LCA Template (Competitive Programming)
 * -------------------------------------------------------------
 * HOW TO USE
 *   1. LCA lca(n);                // vertices are 1..n
 *   2. lca.addEdge(u, v);         // undirected edge (u, v)
 *   3. lca.build(root = 1);       // preprocess from chosen root (default 1)
 *   4. lca.lca(u, v);             // returns lowest common ancestor
 *   5. lca.dist(u, v);            // (optional) distance in edges
 *
 * COMPLEXITIES
 *   build()   : O(n log n)
 *   lca()     : O(log n)
 *   dist()    : O(log n)
 *   memory    : O(n log n)
 * -------------------------------------------------------------
 */


struct LCA {
    int n, LOG;                       // LOG = ceil(log2(n))
    vector<vector<int>> up;           // up[k][v] : 2^k‑th ancestor of v
    vector<int> depth;                // depth[1..n]
    vector<vector<int>> g;            // adjacency list (1‑indexed)

    explicit LCA(int _n) : n(_n), LOG(32 - __builtin_clz(_n)), up(LOG, vector<int>(_n + 1)), depth(_n + 1), g(_n + 1) {}

    void addEdge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void dfs(int v, int p) {
        up[0][v] = (p == -1 ? v : p);
        for (int k = 1; k < LOG; ++k) up[k][v] = up[k - 1][up[k - 1][v]];
        for (int to : g[v]) if (to != p) {
            depth[to] = depth[v] + 1;
            dfs(to, v);
        }
    }

    void build(int root = 1) {
        depth[root] = 0;
        dfs(root, -1);
    }

    int lift(int v, int k) const {
        for (int i = 0; i < LOG; ++i) if (k & (1 << i)) v = up[i][v];
        return v;
    }

    int lca(int u, int v) const {
        if (depth[u] < depth[v]) swap(u, v);
        u = lift(u, depth[u] - depth[v]);
        if (u == v) return u;
        for (int i = LOG - 1; i >= 0; --i)
            if (up[i][u] != up[i][v]) {
                u = up[i][u];
                v = up[i][v];
            }
        return up[0][u];
    }

    int dist(int u, int v) const {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }
};
