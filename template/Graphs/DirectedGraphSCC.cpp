/*
*  ───────────────────────────────────────────────────────────────────────
 *  |     STRONGLY-CONNECTED COMPONENTS (Kosaraju, directed graphs)       |
 *  |     1-indexed, reusable across test-cases, cycle detection, DAG      |
 *  ───────────────────────────────────────────────────────────────────────
 *
 *  HOW TO USE
 *  ───────────────────────────────────────────────────────────────────────
 *
 *      DirectedGraphSCC g(n);                // vertices are 1 … n
 *
 *      g.addEdge(u, v);                      // directed edge  u → v
 *
 *      int scc = g.run();                    // Kosaraju, returns #SCCs
 *
 *      g.componentOf(v);                     // component id of vertex v (1 … scc)
 *
 *      auto dag = g.generateDAG();           // contracts SCCs → DAG (same API)
 *
 *      auto cyc = g.detectCycle();           // one cycle inside any non-trivial SCC
 *                                            // empty if graph is already a DAG
 *
 *      g.reset();                            // reuse (keep n)
 *      g.reset(new_n);                       // reuse & resize
 *
 *  COMPLEXITIES
 *      run() / detectCycle()   O(n + m)
 *      componentOf(v)          O(1)
 *      memory                  O(n + m)
 *
 *  IMPORTANT
 *  • Vertices are **1-indexed**.  Component ids start at 1.
 *  • `addEdge()` must be called *before* `run()`, any query must be *after* `run()`.
 *    Violations trip an `assert`.
 *  • `generateDAG()` returns a new `DirectedGraphSCC` in which each vertex is an
 *    SCC of the original graph.  Edges are unique and acyclic.
 *  ───────────────────────────────────────────────────────────────────────
 */


// https://github.com/AlexandruOlteanu/CompetitiveProgramming/blob/main/template/Graphs/DirectedGraphSCC.cpp
struct DirectedGraphSCC {
    /* ── types & storage ────────────────────────────────────────── */
    int n = 0, scc_cnt = 0;
    vector<vector<int>> in, out, in_component;
    vector<int> used, order, component;
    bool ran = false;                               // has run() been called?

    /* ── construction ───────────────────────────────────────────── */
    explicit DirectedGraphSCC(int _n = 0) { init(_n); }

    /* ── edge insertion ─────────────────────────────────────────── */
    void addEdge(int u, int v) {
        assert(!ran && "addEdge() must precede run()");
        out[u].push_back(v);
        in [v].push_back(u);
    }

    /* ── run Kosaraju ───────────────────────────────────────────── */
    int run() {
        assert(!ran && "run() called twice; call reset() first");
        used.assign(n + 1, 0);
        order.clear();
        for (int v = 1; v <= n; ++v)
            if (!used[v]) dfs(v);

        used.assign(n + 1, 0);
        scc_cnt = 0;
        for (int i = (int)order.size() - 1; i >= 0; --i)
            if (!used[order[i]])
                reverseDfs(order[i], ++scc_cnt);

        in_component.resize(scc_cnt + 1);
        ran = true;
        return scc_cnt;
    }

    /* ── queries ───────────────────────────────────────────────── */
    /** component id of vertex v (1 … scc_cnt) */
    int componentOf(int v) const { assertRan(); return component[v]; }

    /** one cycle inside any non-trivial SCC, empty if none exists */
    vector<int> detectCycle() {
        assertRan();
        vector<int> sz(scc_cnt + 1, 0);
        for (int v = 1; v <= n; ++v) ++sz[component[v]];
        int c = int(find_if(sz.begin() + 1, sz.end(), [](int s){ return s > 1; }) - sz.begin());
        if (c > scc_cnt) return {};                    // already a DAG

        int start = int(find(component.begin() + 1, component.end(), c) - component.begin());
        vector<int> cycle{start};
        used.assign(n + 1, 0); used[start] = 1;
        if (cycleDfs(start, start, c, cycle)) return cycle;
        return {};
    }

    /** contracts SCCs into a DAG, preserving API */
    DirectedGraphSCC generateDAG() {
        assertRan();
        DirectedGraphSCC dag(scc_cnt);
        for (int u = 1; u <= n; ++u)
            for (int v : out[u])
                if (component[u] != component[v])
                    dag.out[component[u]].push_back(component[v]),
                    dag.in [component[v]].push_back(component[u]);

        for (int v = 1; v <= scc_cnt; ++v) {
            auto &vin = dag.in[v], &vout = dag.out[v];
            sort(vin.begin(), vin.end());
            vin.erase(unique(vin.begin(), vin.end()), vin.end());
            sort(vout.begin(), vout.end());
            vout.erase(unique(vout.begin(), vout.end()), vout.end());
        }
        dag.in_component = in_component;
        dag.ran = true;                  // DAG is already an SCC of SCCs
        dag.scc_cnt = dag.n;             // each vertex is its own SCC
        dag.component.resize(dag.n + 1);
        iota(dag.component.begin(), dag.component.end(), 0);
        return dag;
    }

    /* ── reuse across test cases ───────────────────────────────── */
    void reset()               { init(n); }
    void reset(int new_n)      { init(new_n); }

private:
    /* ── helpers ───────────────────────────────────────────────── */
    void init(int _n) {
        n = _n;
        in.assign (n + 1, {});
        out.assign(n + 1, {});
        in_component.assign(n + 1, {});
        component.assign(n + 1, 0);
        used.clear(); order.clear();
        ran = false; scc_cnt = 0;
    }
    void dfs(int v) {
        used[v] = 1;
        for (int u : out[v]) if (!used[u]) dfs(u);
        order.push_back(v);
    }
    void reverseDfs(int v, int id) {
        used[v] = 1; component[v] = id; in_component[id].push_back(v);
        for (int u : in[v]) if (!used[u]) reverseDfs(u, id);
    }
    bool cycleDfs(int v, int start, int comp, vector<int>& cyc) {
        for (int u : out[v])
            if (component[u] == comp) {
                if (u == start) { cyc.push_back(u); return true; }
                if (!used[u]) {
                    used[u] = 1; cyc.push_back(u);
                    if (cycleDfs(u, start, comp, cyc)) return true;
                    cyc.pop_back();
                }
            }
        return false;
    }
    void assertRan() const { assert(ran && "run() must be called first"); }
};