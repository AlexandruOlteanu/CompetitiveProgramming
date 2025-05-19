/*
 * 1‑Indexed **Weighted** Centroid Decomposition Template (Competitive Programming)
 * Language: C++20
 * -----------------------------------------------------------------------------
 * Supports arbitrary non‑negative edge weights (int ≤ 1e9). All stored distances
 * are 64‑bit (long long).
 *
 * HOW TO USE
 *   1. CentroidDecomposition cd(n);           // nodes are 1..n
 *   2. cd.addEdge(u, v, w);                  // undirected weighted edge (u, v, w)
 *   3. cd.build(root = 1);                   // preprocess centroid tree
 *
 * Handy members after build():
 *   cd.parentCentroid[v]  – parent in centroid tree (‑1 for root)
 *   cd.level[v]           – depth in centroid tree (root = 0)
 *   cd.distToCentroid[lvl][v] – distance (weight‑sum) from v to its ancestor
 *                               centroid at level lvl
 *
 * EXAMPLE helper (commented): nearest active node under weighted distance
 *
 * COMPLEXITIES (unchanged)
 *   build()    : O(n log n)
 *   queries    : O(log n) (example)
 *   memory     : O(n log n)
 * -----------------------------------------------------------------------------
 */

struct CentroidDecomposition {
    using ll = long long;

    int n;                                       // number of vertices (1‑indexed)
    vector<vector<pair<int,int>>> g;             // (neighbor, weight)
    vector<int> sub;                             // subtree sizes
    vector<char> blocked;                        // 1 if node is centroid already
    vector<int> parentCentroid;                  // parent in centroid tree
    vector<int> level;                           // depth in centroid tree
    vector<vector<ll>> distToCentroid;           // distToCentroid[level][v]

    explicit CentroidDecomposition(int _n)
        : n(_n), g(_n + 1), sub(_n + 1), blocked(_n + 1, 0),
          parentCentroid(_n + 1, -1), level(_n + 1, -1) {}

    void addEdge(int u, int v, int w) {
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    /* ---- centroid decomposition internals ---- */
    int dfs_size(int v, int p) {
        sub[v] = 1;
        for (auto [to, w] : g[v]) if (to != p && !blocked[to]) sub[v] += dfs_size(to, v);
        return sub[v];
    }

    int dfs_centroid(int v, int p, int tot) {
        for (auto [to, w] : g[v]) if (to != p && !blocked[to])
            if (sub[to] * 2 > tot) return dfs_centroid(to, v, tot);
        return v;
    }

    void ensure_level(int lvl) {
        if ((int)distToCentroid.size() <= lvl) distToCentroid.emplace_back(n + 1, -1);
    }

    void dfs_collect(int v, int p, ll d, int lvl) {
        ensure_level(lvl);
        distToCentroid[lvl][v] = d;
        for (auto [to, w] : g[v]) if (to != p && !blocked[to]) dfs_collect(to, v, d + w, lvl);
    }

    void decompose(int entry, int p) {
        int tot = dfs_size(entry, -1);
        int c = dfs_centroid(entry, -1, tot);
        parentCentroid[c] = p;
        level[c] = (p == -1 ? 0 : level[p] + 1);

        // --- CUSTOM WORK per centroid 'c' (reset data structures) ---

        dfs_collect(c, -1, 0, level[c]);
        blocked[c] = 1;
        for (auto [to, w] : g[c]) if (!blocked[to]) decompose(to, c);
    }

    void build(int root = 1) { decompose(root, -1); }
};