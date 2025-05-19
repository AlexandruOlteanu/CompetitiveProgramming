/*********************************************************************
 * Floyd–Warshall All-Pairs Shortest Paths • Competitive Template
 * -------------------------------------------------------------------
 *  • Graph size:   n  (0-indexed vertices)
 *  • Complexity:   Time  O(n³)   |   Memory  O(n²)
 *  • Handles:      negative edges (no negative cycles)
 *
 * Usage pattern
 * --------------
 *  int n, m;               // vertices, edges
 *  cin >> n >> m;
 *  Floyd fw(n);
 *  loop m times { cin >> u >> v >> w; fw.addEdge(u,v,w); }
 *  fw.run();
 *  cout << fw.d[u][v];     // distance or INF
 *  auto path = fw.getPath(u,v);   // full path (may be empty)
 *********************************************************************/

const long long INF = 4e18;

struct Floyd {
    int n;
    vector<vector<long long>> d;
    vector<vector<int>> nxt;        

    explicit Floyd(int N) : n(N), d(N + 1, vector<long long>(N + 1, INF)),
                            nxt(N + 1, vector<int>(N + 1, -1)) {
        for (int i = 1; i <= n; ++i) d[i][i] = 0;
    }

    // directed edge u → v
    void addEdge(int u, int v, long long w) {
        if (w < d[u][v]) {
            d[u][v] = w;
            nxt[u][v] = v;
        }
    }

    void run() {
        for (int k = 1; k <= n; ++k)
            for (int i = 1; i <= n; ++i) if (d[i][k] < INF)
                for (int j = 1; j <= n; ++j) {
                    if (d[k][j] == INF) continue;
                    long long cand = d[i][k] + d[k][j];
                    if (cand < d[i][j]) {
                        d[i][j] = cand;
                        nxt[i][j] = nxt[i][k];
                    }
                }
        // negative–cycle check: d[i][i] < 0  (1..n)
    }

    vector<int> getPath(int u, int v) const {
        if (nxt[u][v] == -1) return {};
        vector<int> path{u};
        while (u != v) {
            u = nxt[u][v];
            path.push_back(u);
        }
        return path;
    }

    bool isPath(int u, int v) {
        if (d[u][v] == INF) return false;
        return true;
    }

    long long getDist(int u, int v) {
        return d[u][v];
    }
};