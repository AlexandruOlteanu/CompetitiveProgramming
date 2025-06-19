/*
*  ───────────────────────────────────────────────────────────────────────
 *  |        DISJOINT-SET UNION (Union-Find, size heuristic + path-comp)   |
 *  |        0-indexed, fully reusable across test-cases                   |
 *  ───────────────────────────────────────────────────────────────────────
 *
 *  HOW TO USE
 *  ───────────────────────────────────────────────────────────────────────
 *
 *      DSU uf(n);                   // vertices are 0 … n-1
 *
 *      uf.merge(a, b);              // join the sets containing a and b
 *      uf.same(a, b);               // true if a and b already in same set
 *      uf.size(a);                  // size of the set containing a
 *
 *      uf.reset();                  // reuse (keep n)
 *      uf.reset(new_n);             // reuse & resize
 *
 *  COMPLEXITIES
 *      merge / same / size     O(α(n))   (inverse Ackermann, “effectively” O(1))
 *      memory                  O(n)
 *
 *  IMPORTANT
 *  • All indices are **0-based**.  Passing an invalid vertex id triggers
 *    an `assert`.  If you need 1-based, just subtract 1 on every call.
 *  • `merge()`, `same()`, and `size()` must be called **after** construction
 *    (or after `reset()`/`init()`), otherwise an `assert` trips.
 *  ───────────────────────────────────────────────────────────────────────
 */

// https://github.com/AlexandruOlteanu/CompetitiveProgramming/blob/main/template/Graphs/DSU.cpp
struct DSU {
    /* ── construction ───────────────────────────────────────────── */
    explicit DSU(int _n = 0) { init(_n); }

    /* ── initialise / reset ─────────────────────────────────────── */
    void reset()              { init(n); }
    void reset(int _n)        { init(_n); }

    /* ── queries & updates ──────────────────────────────────────── */
    /** return root of x */
    int find(int x) {
        assertReady(); assertValid(x);
        while (x != parent[x]) x = parent[x] = parent[parent[x]];
        return x;
    }
    /** true iff x and y are already in the same set */
    bool same(int x, int y) { return find(x) == find(y); }

    /** union by size; returns false if already same set */
    bool merge(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (sz[x] < sz[y]) std::swap(x, y);
        parent[y] = x; sz[x] += sz[y];
        return true;
    }

    /** size of the set containing x */
    int size(int x) { return sz[find(x)]; }

private:
    int n = 0;
    std::vector<int> parent, sz;

    /* ── helpers ───────────────────────────────────────────────── */
    void init(int _n) {
        n = _n;
        parent.resize(n);
        std::iota(parent.begin(), parent.end(), 0);
        sz.assign(n, 1);
    }
    void assertReady() const { assert(n > 0 && "DSU must be initialised first"); }
    void assertValid(int v) const { assert(0 <= v && v < n && "vertex id out of range"); }
};