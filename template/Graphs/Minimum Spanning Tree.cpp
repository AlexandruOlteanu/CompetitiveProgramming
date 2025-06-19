/*
*  ───────────────────────────────────────────────────────────────────────
 *  |                MINIMUM-SPANNING TREE (Kruskal + inline DSU)          |
 *  |           Undirected, 1-indexed, fully reusable across cases         |
 *  ───────────────────────────────────────────────────────────────────────
 *
 *  HOW TO USE
 *  ───────────────────────────────────────────────────────────────────────
 *
 *      MST<long long> mst(n);           // n = number of vertices (1 … n)
 *
 *      mst.add_edge(u, v, w);           // undirected edge (u – v) with weight w
 *      … (add as many edges as you need)
 *
 *      auto tree_cost = mst.build();    // runs Kruskal, returns total cost
 *
 *      const auto& g = mst.adj();       // adjacency list of the MST
 *                                       //   g[u] = { {v, w}, … }
 *
 *      mst.reset();                     // reuse (keep n)
 *      mst.reset(new_n);                // reuse & resize
 *
 *  COMPLEXITIES
 *      add_edge()               O(1)
 *      build()                  O(m log m)
 *      memory                   O(n + m)
 *
 *  IMPORTANT
 *  • Vertices are **1-indexed**.  Passing 0 or > n trips an assert.
 *  • `add_edge()` must be called **before** `build()`.  Calling it after,
 *    or querying the tree before `build()`, trips an assert.
 *  • `build()` may be called only once per run; call `reset()` to reuse.
 */

// https://github.com/AlexandruOlteanu/CompetitiveProgramming/blob/main/template/Graphs/Minimum%20Spanning%20Tree.cpp
template <typename W>
struct MST {
    explicit MST(int _n = 0) { init(_n); }

    /* ── edge insertion ─────────────────────────────────────────── */
    void add_edge(int u, int v, W w) {
        assert(!built && "add_edge() must precede build()");
        assert(valid(u) && valid(v) && "vertex id out of range");
        edges.emplace_back(w, u, v);
    }

    /* ── build Kruskal ──────────────────────────────────────────── */
    /** returns total weight of the MST; −1 if the graph is disconnected */
    W build() {
        assert(!built && "build() called twice; call reset() first");
        std::sort(edges.begin(), edges.end());
        W cost = 0;
        int picked = 0;
        for (auto [w, u, v] : edges) {
            if (join(u, v)) {
                tree[u].push_back({v, w});
                tree[v].push_back({u, w});
                cost += w;
                ++picked;
            }
        }
        built = true;
        return (picked == n - 1 ? cost : W(-1));      // −1 ⇒ not connected
    }

    /* ── queries ───────────────────────────────────────────────── */
    /** adjacency list of the MST */
    const std::vector<std::vector<std::pair<int, W>>>& adj() const {
        assertBuilt(); return tree;
    }

    /* ── reuse across test cases ───────────────────────────────── */
    void reset()                 { init(n); }
    void reset(int new_n)        { init(new_n); }

private:
    /* ── DSU ────────────────────────────────────────────────────── */
    std::vector<int> parent, sz;
    int find(int x) { return x == parent[x] ? x : parent[x] = find(parent[x]); }
    bool join(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) std::swap(a, b);
        parent[b] = a; sz[a] += sz[b];
        return true;
    }

    /* ── helpers / state ───────────────────────────────────────── */
    int n = 0;
    std::vector<std::tuple<W,int,int>> edges;
    std::vector<std::vector<std::pair<int,W>>> tree;
    bool built = false;

    void init(int _n) {
        n = _n;
        parent.resize(n + 1);
        std::iota(parent.begin(), parent.end(), 0);
        sz.assign(n + 1, 1);
        edges.clear();
        tree.assign(n + 1, {});
        built = false;
    }
    bool valid(int v) const { return 1 <= v && v <= n; }
    void assertBuilt() const { assert(built && "build() must be called first"); }
};
