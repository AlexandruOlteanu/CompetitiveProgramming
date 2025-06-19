/*
*  ───────────────────────────────────────────────────────────────────────
 *  |               EULERIAN PATH / CIRCUIT (directed & undirected)        |
 *  |                Hierholzer, 1-indexed, fully reusable                 |
 *  ───────────────────────────────────────────────────────────────────────
 *
 *  HOW TO USE
 *  ───────────────────────────────────────────────────────────────────────
 *
 *      EulerianPath ep(n, true);        // directed   (u → v)
 *      EulerianPath ep(n, false);       // undirected (u – v)
 *
 *      ep.add_edge(u, v);               // single edge (directed / one side)
 *      ep.add_undirected_edge(u, v);    // *only* for undirected graphs
 *
 *      auto path = ep.get_path();       // empty ⇒ no Euler tour/path
 *
 *      ep.reset();                      // reuse (keep n & directed)
 *      ep.reset(new_n, new_dir);        // reuse & resize / change flavour
 *
 *  COMPLEXITIES
 *      add_edge() / add_undirected_edge()  O(1)
 *      get_path()                          O(n + m)
 *      memory                              O(n + m)
 *
 *  IMPORTANT
 *  • Nodes are **1-indexed**.  Edges must be inserted **before** `get_path()`.
 *    Calling either insertion routine *after* `get_path()` trips an assert.
 *  • For undirected graphs you *must* use `add_undirected_edge()`; mixing the
 *    two insertion styles trips an assert.
 *  • `get_path()` returns a node sequence of length **m + 1** if an Eulerian
 *    path/circuit exists, otherwise an empty vector.
 *  ───────────────────────────────────────────────────────────────────────
 *  Template by Alexandru Olteanu {AlexandruINV}, extended w/ usage notes,
 *  asserts, and reset functionality.
 *  Original: https://github.com/AlexandruOlteanu/CompetitiveProgramming
 *  ───────────────────────────────────────────────────────────────────────
 */

// https://github.com/AlexandruOlteanu/CompetitiveProgramming/blob/main/template/Graphs/EulerianPath.cpp
struct EulerianPath {
    /* ── construction ───────────────────────────────────────────── */
    explicit EulerianPath(int _n = 0, bool is_dir = true) { init(_n, is_dir); }

    /* ── edge insertion ─────────────────────────────────────────── */
    void add_edge(int u, int v) {
        assert(!solved && "add_edge() must precede get_path()");
        assert(directed && "use add_undirected_edge() for undirected graphs");
        graph[u].push_back({v, eid});
        out_deg[u]++; in_deg[v]++;
        used_edge.push_back(false);
        paired_edge.push_back(-1);
        ++eid;
    }
    void add_undirected_edge(int u, int v) {
        assert(!solved && "add_undirected_edge() must precede get_path()");
        assert(!directed && "graph declared as directed");
        graph[u].push_back({v, eid});
        graph[v].push_back({u, eid + 1});
        deg[u]++; deg[v]++;
        used_edge.push_back(false); used_edge.push_back(false);
        paired_edge.push_back(eid + 1);
        paired_edge.push_back(eid);
        eid += 2;
    }

    /* ── solve ──────────────────────────────────────────────────── */
    std::vector<int> get_path() {
        assert(!solved && "get_path() called twice; call reset() first");
        solved = true;
        int start;
        if (!eulerian_start(start)) return {};
        dfs(start);
        std::reverse(path.begin(), path.end());
        const int expected = directed ? eid + 1 : (eid / 2) + 1;
        if ((int)path.size() != expected) return {};
        return path;
    }

    /* ── reuse across test cases ───────────────────────────────── */
    void reset()                                  { init(n, directed);      }
    void reset(int new_n, bool is_dir = true)     { init(new_n, is_dir);    }

private:
    int n = 0; bool directed = true;
    std::vector<std::vector<std::pair<int,int>>> graph;
    std::vector<int> in_deg, out_deg, deg;
    std::vector<int> path;
    std::vector<bool> used_edge;
    std::vector<int>  paired_edge;
    int eid = 0;
    bool solved = false;

    /* ── helpers ───────────────────────────────────────────────── */
    void init(int _n, bool is_dir) {
        n = _n; directed = is_dir;
        graph.assign(n + 1, {});
        in_deg.assign(n + 1, 0);
        out_deg.assign(n + 1, 0);
        deg.assign(n + 1, 0);
        path.clear();
        used_edge.clear();
        paired_edge.clear();
        eid = 0; solved = false;
    }
    bool eulerian_start(int& st) {
        int odd = 0, start_nodes = 0, end_nodes = 0;
        st = 1;
        if (directed) {
            for (int i = 1; i <= n; ++i) {
                const int diff = out_deg[i] - in_deg[i];
                if (diff == 1)  { start_nodes++; st = i; }
                else if (diff == -1) end_nodes++;
                else if (diff != 0) return false;
            }
            return (start_nodes == 0 && end_nodes == 0) ||
                   (start_nodes == 1 && end_nodes == 1);
        } else {
            for (int i = 1; i <= n; ++i)
                if (deg[i] & 1) { ++odd; st = i; }
            return odd == 0 || odd == 2;
        }
    }
    void dfs(int u) {
        while (!graph[u].empty()) {
            auto [v, id] = graph[u].back();
            graph[u].pop_back();
            if (used_edge[id]) continue;
            used_edge[id] = true;
            if (!directed) used_edge[paired_edge[id]] = true;
            dfs(v);
        }
        path.push_back(u);
    }
};