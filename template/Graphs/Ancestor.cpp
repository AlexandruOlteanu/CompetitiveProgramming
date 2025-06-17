/*
 *  ───────────────────────────────────────────────────────────────
 *  |                  BINARY-LIFTING LCA TEMPLATE                 |
 *  |                1-indexed, works for FORESTS                  |
 *  ───────────────────────────────────────────────────────────────
 *
 *  QUICK REFERENCE ─ what you can call after `Ancestor lca(n);`
 *  ───────────────────────────────────────────────────────────────
 *
 *    addEdge(u, v)               // undirected edge (u, v); repeat as needed
 *
 *    build()                     // auto-root every component (no preference)
 *    build(root)                 // same, but make `root` the root of *its* component
 *    build({r1, r2, …})          // give a preferred root for *each* component
 *
 *    build(adj)                  // build directly from a ready adjacency list
 *    build(adj, root)            // … + single preferred root
 *    build(adj, {r1, r2, …})     // … + several preferred roots
 *
 *    lca(u, v)                   // lowest common ancestor vertex
 *    dist(u, v)                  // #edges on the u-v path
 *    kth_ancestor(v, k)          // k-th ancestor of v  (-1 if it doesn’t exist)
 *
 *    reset()                     // clear everything, keep same n
 *    reset(new_n)                // clear & resize
 *
 *  RETURN-VALUES & GUARANTEES
 *  ───────────────────────────────────────────────────────────────
 *  • All queries return -1 when u and v are in **different trees**.
 *  • kth_ancestor(v, k) returns -1 if k ≥ depth(v)+1 (i.e. climbs past the root).
 *  • Adding edges **after** build() or querying **before** build() → `assert` fail.
 *
 *  COMPLEXITIES
 *  ───────────────────────────────────────────────────────────────
 *      build(...)        O(n log n)
 *      lca / dist / kth  O(log n)     (per query)
 *      memory            O(n log n)
 *
 *  EXAMPLES
 *  ───────────────────────────────────────────────────────────────
 *  1)  ONE TREE, NO SPECIAL ROOT
 *
 *      Ancestor L(5);
 *      L.addEdge(1,2); L.addEdge(1,3); L.addEdge(3,4); L.addEdge(3,5);
 *      L.build();                       // 1 becomes the root automatically
 *      cout << L.lca(4,5) << '\n';      // 3
 *
 *  2)  ONE TREE, GIVEN ROOT
 *
 *      L.reset();
 *      L.addEdge(1,2); …same edges…
 *      L.build(3);                      // explicitly root the tree at 3
 *      cout << L.lca(4,5) << '\n';      // still 3
 *      cout << L.kth_ancestor(4,2) << '\n'; // 3 → 1 (2 steps)  → prints 1
 *
 *  3)  FOREST WITH MULTIPLE PREFERRED ROOTS
 *
 *      int n = 13;
 *      vector<vector<int>> adj(n+1);
 *      auto add=[&](int u,int v){ adj[u].push_back(v); adj[v].push_back(u); };
 *      // first component
 *      add(8,9); add(8,10); add(10,11); add(10,12); add(12,13);
 *      // second component
 *      add(4,5);
 *
 *      Ancestor F(n);
 *      F.build(adj, {12,4});            // 12 is root of comp#0, 4 of comp#1
 *
 *      cout << F.lca(11,13) << '\n';    // 12
 *      cout << F.lca(5,13)  << '\n';    // -1  (different trees)
 *
 *  4)  RE-USING THE SAME OBJECT FOR MULTIPLE TEST CASES
 *
 *      for (int tc = 0; tc < T; ++tc) {
 *          int n; cin >> n;
 *          Ancestor L(n);               // or keep one global object and L.reset(n)
 *          …read edges…
 *          L.build();
 *          …answer queries…
 *      }
 *
 *  IMPLEMENTATION NOTE
 *  ───────────────────────────────────────────────────────────────
 *  • Internally vertex 0 is a “null parent”.  All real vertices are 1…n.
 *  • Each preferred root is accepted only if it is within [1, n] and unvisited.
 *    If two roots fall in the same component the first one visited wins.
 *
 *  ───────────────────────────────────────────────────────────────
 */
// https://github.com/AlexandruOlteanu/CompetitiveProgramming/blob/main/template/Graphs/Ancestor.cpp
struct Ancestor {
    explicit Ancestor(int _n) { init(_n); }

    /* --------- add edges one by one --------- */
    void addEdge(int u, int v) {
        assert(!built && "addEdge() must be called before build()");
        g[u].push_back(v), g[v].push_back(u);
    }

    /* --------- build(): three overloads --------- */
    void build(int root = 1)               { runBuild({root}); }      // one root
    void build(const vector<int>& roots)   { runBuild(roots); }       // many

    /* adjacency-list versions */
    void build(const vector<vector<int>>& adj)                { g = adj; runBuild({}); }
    void build(const vector<vector<int>>& adj, int root)      { g = adj; runBuild({root}); }
    void build(const vector<vector<int>>& adj,
               const vector<int>& roots)                      { g = adj; runBuild(roots); }

    /* --------- queries --------- */
    int kth_ancestor(int v, int k) const { assertBuilt(); return lift(v,k); }
    int lca(int u, int v)          const { assertBuilt(); return lcaImpl(u,v); }
    int dist(int u, int v)         const { assertBuilt();
        int a = lcaImpl(u,v);
        return a == -1 ? -1 : depth[u] + depth[v] - 2*depth[a];
    }

    /* --------- reuse --------- */
    void reset()          { init(n); }
    void reset(int new_n) { init(new_n); }

private:
    /* --------- state --------- */
    int n{}, LOG{};
    vector<vector<int>> up;     // up[k][v] = 2^k-th ancestor (0 ⇒ none)
    vector<int> depth;          // depth[v]
    vector<vector<int>> g;      // adjacency list
    vector<int> comp;           // component id
    bool built = false;

    /* --------- init --------- */
    void init(int _n) {
        n = _n;
        LOG = 32 - __builtin_clz(max(1, n)) + 1;   // 2^LOG ≥ n
        up.assign(LOG, vector<int>(n + 1, 0));
        depth.assign(n + 1, 0);
        g.assign(n + 1, {});
        comp.assign(n + 1, -1);
        built = false;
    }

    /* --------- build internals --------- */
    void runBuild(const vector<int>& roots) {
        assert(!built && "build() called twice");

        vector<char> used_root(n + 1, 0);
        int cid = 0;

        /* 1. DFS from every user-supplied root (ignore duplicates / wrong ids) */
        for (int r : roots)
            if (1 <= r && r <= n && !used_root[r] && comp[r] == -1) {
                used_root[r] = 1;
                dfs(r, 0, cid++);
            }

        /* 2. finish remaining components with arbitrary roots */
        for (int v = 1; v <= n; ++v)
            if (comp[v] == -1) dfs(v, 0, cid++);

        built = true;
    }

    void dfs(int v, int p, int cid) {
        comp[v] = cid;
        up[0][v] = p;
        for (int k = 1; k < LOG; ++k)
            up[k][v] = up[k-1][v] ? up[k-1][ up[k-1][v] ] : 0;
        for (int to : g[v]) if (to != p) {
            depth[to] = depth[v] + 1;
            dfs(to, v, cid);
        }
    }

    /* --------- query helpers --------- */
    int lift(int v, int k) const {
        for (int i = 0; v && k; ++i, k >>= 1)
            if (k & 1) v = up[i][v];
        return v ? v : -1;
    }

    int lcaImpl(int u, int v) const {
        if (comp[u] != comp[v]) return -1;
        if (depth[u] < depth[v]) swap(u,v);
        u = lift(u, depth[u] - depth[v]);
        if (u == v) return u;
        for (int i = LOG-1; i >= 0; --i)
            if (up[i][u] && up[i][u] != up[i][v])
                u = up[i][u], v = up[i][v];
        return up[0][u] ? up[0][u] : -1;
    }

    void assertBuilt() const { assert(built && "build() must be called first"); }
};
