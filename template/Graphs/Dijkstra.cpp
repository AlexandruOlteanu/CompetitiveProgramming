/*
 *  ───────────────────────────────────────────────────────────────────────
 *  |                   DIJKSTRA (Single-Source / Multi-Source)            |
 *  |         1-indexed, undirected or directed, handles UNREACHABLES      |
 *  ───────────────────────────────────────────────────────────────────────
 *
 *  HOW TO USE
 *  ───────────────────────────────────────────────────────────────────────
 *
 *      Dijkstra sp(n);                     // vertices are 1 … n
 *
 *      sp.addEdge(u, v, w);                // undirected by default
 *      sp.addEdge(u, v, w, true);          // directed edge
 *
 *      sp.run(src);                        // classic single-source
 *      sp.run({s1, s2, …});                // multi-source (all start at 0)
 *
 *      /* if you already have an adjacency list:
 *      sp.run(adj, src);                   //   adj = vector< vector< {to, w} > >
 *      sp.run(adj, {s1, …});
 *
 *      sp.dist(v)            → shortest distance or −1 if unreachable
 *      sp.distVector()       → vector with −1 for unreachable vertices
 *      sp.rawDistVector()    → same data but with big +INF for unreachable
 *      sp.path(v)            → list of vertices on a shortest path (empty if −1)
 *
 *      sp.reset();           // reuse same object, keep n
 *      sp.reset(new_n);      // reuse, resize
 *
 *  COMPLEXITIES
 *      run(...)              O((n + m) log n)      (binary heap)
 *      dist(v) / path(v)     O(length of path)     (O(1) for plain distance)
 *      memory                O(n + m)
 *
 *  IMPORTANT
 *  • All edge weights must be **non-negative**.  For negative edges use
 *    Bellman–Ford, SPFA, or Johnson’s algorithm.
 *  • Calling addEdge() *after* run(), or queries *before* run(), trips an assert.
 *  • Internally we keep a big +INF (≈ 2.3 × 10¹⁸) to avoid overflow; the public
 *    API maps it to −1 for convenience.
 *  ───────────────────────────────────────────────────────────────────────
 */

struct Dijkstra {
    using ll = long long;
    static constexpr ll INF = std::numeric_limits<ll>::max() / 4;   // safe sentinel

    bool direct;
    /* ── construction ───────────────────────────────────────────── */
    explicit Dijkstra(int _n = 0, bool _direct = false) { init(_n, _direct); }

    /* ── edge insertion ─────────────────────────────────────────── */
    void addEdge(int u, int v, ll w) {
        assert(!ran && "addEdge() must precede run()");
        g[u].push_back({v, w});
        if (!direct) g[v].push_back({u, w});
    }

    /* ── run Dijkstra ───────────────────────────────────────────── */
    void run(int src = 1)                          { run(vector<int>{src}); }
    void run(const vector<int>& srcs) {
        assert(!ran && "run() called twice; call reset() first");
        prepare();
        using State = pair<ll,int>;
        priority_queue<State, vector<State>, greater<State>> pq;

        for (int s : srcs) if (validVertex(s)) {
            dist_[s] = 0;
            pq.push({0, s});
        }
        while (!pq.empty()) {
            auto [du, u] = pq.top(); pq.pop();
            if (du != dist_[u]) continue;          // stale entry
            for (auto [v, w] : g[u])
                if (dist_[v] > du + w) {
                    dist_[v] = du + w;
                    parent_[v] = u;
                    pq.push({dist_[v], v});
                }
        }
        ran = true;
    }

    /* overloads that accept a ready adjacency list */
    void run(const vector<vector<pair<int,ll>>>& adj, int src)              { g = adj; run(src); }
    void run(const vector<vector<pair<int,ll>>>& adj, const vector<int>& s) { g = adj; run(s);   }

    /* ── queries ────────────────────────────────────────────────── */
    /** shortest distance or −1 if unreachable */
    ll dist(int v) const { assertRan(); return dist_[v] == INF ? -1 : dist_[v]; }

    /** vector with −1 for unreachable vertices */
    vector<ll> distVector() const {
        assertRan();
        vector<ll> out(dist_.size());
        for (size_t i = 1; i < dist_.size(); ++i)
            out[i] = (dist_[i] == INF ? -1 : dist_[i]);
        return out;
    }

    /** one shortest path (empty if unreachable) */
    vector<int> path(int v) const {
        assertRan();
        if (dist_[v] == INF) return {};
        vector<int> p;
        while (v) { p.push_back(v); v = parent_[v]; }
        reverse(p.begin(), p.end());
        return p;
    }

    /* ── reuse across test cases ───────────────────────────────── */
    void reset(bool _direct = false)          { init(n, _direct); }
    void reset(int new_n, bool _direct = false) { init(new_n, _direct); }

private:
    int n = 0;
    vector<vector<pair<int,ll>>> g;   // adjacency list
    vector<ll>  dist_;
    vector<int> parent_;
    bool ran = false;

    /* ── helpers ───────────────────────────────────────────────── */
    void init(int _n, bool _direct) {
        n = _n;
        direct = _direct;
        g.assign(n + 1, {});
        dist_.assign(n + 1, INF);
        parent_.assign(n + 1, 0);
        ran = false;
    }
    void prepare() {
        fill(dist_.begin(),   dist_.end(),   INF);
        fill(parent_.begin(), parent_.end(), 0);
    }
    bool validVertex(int v) const { return 1 <= v && v <= n; }
    void assertRan()       const { assert(ran && "run() must be called first"); }
};