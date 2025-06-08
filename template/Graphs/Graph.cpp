// ============================================================
// GraphAllInOne — Full Usage Guide and Module Instructions
// ============================================================
//
// STEP 1: DECLARE THE GRAPH
// --------------------------
// GraphAllInOne<int, false> g(n);       // Undirected graph
// GraphAllInOne<long long, true> g(n);  // Directed graph with long long weights
//
// STEP 2: ADD EDGES
// -----------------
// g.addEdge(u, v);                      // Defaults cost = 1, auto-ID
// g.addEdge(u, v, cost);                // Adds edge with specific weight
// DO NOT CALL addEdge() after g.build()
//
// STEP 3: BUILD THE GRAPH
// ------------------------
// g.build();                            // Must be called before using any module
//
// STEP 4: USE THE DESIRED MODULE (SEE BELOW)
// ==========================================
//
// -------------------------------------------
// 1. SHORTEST PATH ALGORITHMS
// -------------------------------------------
// • g.dijkstra(source);
//   → Returns vector of min distances (non-negative weights only)
//
// • g.bellmanFord(source);
//   → Returns vector of min distances (handles negative weights)
//   → Throws if a negative cycle is detected
//
// -------------------------------------------
// 2. STRONGLY CONNECTED COMPONENTS (SCC)
// -------------------------------------------
// • g.computeStronglyConnectedComponents();
//   → Returns component ID per node (only for directed graphs)
//
// -------------------------------------------
// 3. BRIDGES & ARTICULATION POINTS (UNDIRECTED ONLY)
// -------------------------------------------
// • g.computeBridgesAndArticulationPoints();
//   → Returns vector of bridge edges and articulation points
//
// -------------------------------------------
// 4. MAXIMUM FLOW (DINIC’S ALGORITHM)
// -------------------------------------------
// • g.maxFlow(source, sink);
//   → Only for directed graphs
//   → Returns the max flow value
//
// -------------------------------------------
// 5. BIPARTITE MATCHING (HOPCROFT-KARP)
// -------------------------------------------
// • g.bipartiteMatching(L, R);
//   → Total nodes must be L + R
//   → Left nodes: 0..L-1, Right nodes: L..L+R-1
//   → Returns number of matches and match for each left node
//
// -------------------------------------------
// 6. MINIMUM SPANNING TREE (KRUSKAL’S ALGORITHM)
// -------------------------------------------
// • g.kruskalMST();
//   → Works on undirected graphs
//   → Returns total cost and used edge IDs
//
// -------------------------------------------
// 7. EULERIAN PATH OR CIRCUIT
// -------------------------------------------
// • g.eulerianPath();
//   → Returns node path if an Eulerian trail/circuit exists
//
// -------------------------------------------
// 8. TOPOLOGICAL SORT (DAGs ONLY)
// -------------------------------------------
// • g.topologicalSort();
//   → Returns topological ordering or empty if cycle exists
//
// -------------------------------------------
// 9. TREE UTILITIES — LCA & HEAVY-LIGHT DECOMPOSITION
// -------------------------------------------
// • g.buildTreeStructure(root);
//   → REQUIRED before using LCA or HLD
//
// • g.lowestCommonAncestor(u, v);
//   → Requires: buildTreeStructure() called
//
// • g.buildHeavyLightDecomposition(root);
//   → Requires: buildTreeStructure() called
//
// • g.heavyLightPathQuery(u, v);
//   → Returns path as segments (positions in HLD base array)
//   → Requires: buildHeavyLightDecomposition()
//
// • g.getSubtreeSize(node);
//   → Requires: buildHeavyLightDecomposition() called
//   → Returns size of subtree rooted at `node` in the tree
//
// -------------------------------------------
// 10. ALL-PAIRS SHORTEST PATH (FLOYD-WARSHALL)
// -------------------------------------------
// • g.floydWarshall(); or
//   vector<vector<int>> path; g.floydWarshall(&path);
//
// • g.floydWarshallReconstructPath(u, v, path);
//   → Reconstructs full path from u to v using path matrix
//
// -------------------------------------------
// 11. LEAF NODES
// -------------------------------------------
// • g.findAllLeaves();
//   → For undirected: nodes with degree = 1
//   → For directed: nodes with out-degree = 0
//
// -------------------------------------------
// 12. DISJOINT SET UNION (DSU / UNION-FIND)
// -------------------------------------------
// • GraphAllInOne<>::DSU dsu(n);
// • dsu.find(x); dsu.unite(x, y);
//   → Useful inside Kruskal or custom tree/graph logic
//
// ============================================================
// REMINDERS:
// - Always call g.build() before running any algorithms
// - Do not call addEdge() after g.build()
// - For tree utilities, ensure the graph is a valid tree
// - Use correct template params: <int, false> or <long long, true>
// ============================================================

template <typename Weight = int, bool Directed = false>
class GraphAllInOne {
public:
    struct Edge {
        int from, to;
        Weight cost;
        int id;
    };

    int numberOfNodes, numberOfEdges;
    vector<Edge> edgeList;
    vector<int> indexPointer;
    vector<Edge> compressedEdges;
    bool isBuilt;

    GraphAllInOne() : numberOfNodes(0), numberOfEdges(0), isBuilt(false) { }
    GraphAllInOne(int n) : numberOfNodes(n), numberOfEdges(0), isBuilt(false) { }

    void initializeGraph(int n) {
        numberOfNodes = n;
        numberOfEdges = 0;
        isBuilt = false;
        edgeList.clear();
        indexPointer.clear();
        compressedEdges.clear();
    }

    void addEdge(int from, int to, Weight cost = 1, int id = -1) {
        assert(!isBuilt && "Do not add edges after calling build()");
        assert(from >= 0 && from < numberOfNodes && to >= 0 && to < numberOfNodes);
        if (id == -1) {
            id = numberOfEdges;
        }
        edgeList.push_back({from, to, cost, id});
        ++numberOfEdges;
    }

    void build() {
        assert(!isBuilt && "Graph is already built!");
        isBuilt = true;
        indexPointer.assign(numberOfNodes + 1, 0);
        for (const auto& e : edgeList) {
            indexPointer[e.from + 1]++;
            if (!Directed) indexPointer[e.to + 1]++;
        }
        for (int i = 0; i < numberOfNodes; i++)
            indexPointer[i + 1] += indexPointer[i];
        compressedEdges.resize(indexPointer.back());
        vector<int> counter = indexPointer;
        for (const auto& e : edgeList) {
            compressedEdges[counter[e.from]++] = e;
            if (!Directed)
                compressedEdges[counter[e.to]++] = {e.to, e.from, e.cost, e.id};
        }
    }

    pair<const Edge*, const Edge*> operator[](int node) const {
        assert(isBuilt && "Must call build() before accessing edges!");
        return make_pair(&compressedEdges[indexPointer[node]], &compressedEdges[indexPointer[node + 1]]);
    }

    vector<int> findAllLeaves() const {
        assert(isBuilt && "Graph must be built before finding leaves.");
        vector<int> leaves;
        for (int node = 0; node < numberOfNodes; ++node) {
            auto [begin, end] = (*this)[node];
            if (begin == end) continue; // isolated node, not a leaf
            int degree = 0;
            for (const Edge* it = begin; it != end; ++it) degree++;
            if ((!Directed && degree == 1) || (Directed && indexPointer[node + 1] - indexPointer[node] == 0)) {
                leaves.push_back(node);
            }
        }
        return leaves;
    }

    // The rest of the full implementation continues here...
    // All modules were previously trimmed for brevity.
    // The complete implementation with English comments is available and will now be inlined here.

    // ===============================
    // The rest of the algorithm modules are now inlined below.

    // ===============================
    // Module 1: Shortest Paths — Dijkstra
    vector<Weight> dijkstra(int source) const {
        const Weight INF = numeric_limits<Weight>::max();
        vector<Weight> distance(numberOfNodes, INF);
        distance[source] = 0;
        priority_queue<pair<Weight, int>, vector<pair<Weight, int>>, greater<pair<Weight, int>>> heap;
        heap.push({0, source});
        while (!heap.empty()) {
            auto [dist, node] = heap.top(); heap.pop();
            if (dist != distance[node]) continue;
            auto edgeRange = (*this)[node];
            for (const Edge* ptr = edgeRange.first; ptr != edgeRange.second; ++ptr) {
                int next = ptr->to;
                Weight newDist = dist + ptr->cost;
                if (newDist < distance[next]) {
                    distance[next] = newDist;
                    heap.push({newDist, next});
                }
            }
        }
        return distance;
    }

    // ===============================
    // ===============================
    // Module 1 (continued): Bellman-Ford
    vector<Weight> bellmanFord(int source) const {
        const Weight INF = numeric_limits<Weight>::max();
        vector<Weight> distance(numberOfNodes, INF);
        distance[source] = 0;
        for (int i = 0; i < numberOfNodes - 1; i++) {
            bool updated = false;
            for (const auto& e : edgeList) {
                if (distance[e.from] != INF && distance[e.from] + e.cost < distance[e.to]) {
                    distance[e.to] = distance[e.from] + e.cost;
                    updated = true;
                }
            }
            if (!updated) break;
        }
        for (const auto& e : edgeList) {
            if (distance[e.from] != INF && distance[e.from] + e.cost < distance[e.to]) {
                throw runtime_error("Negative cycle detected in Bellman-Ford.");
            }
        }
        return distance;
    }

    // ===============================
    // Module 2: Strongly Connected Components (Tarjan)
    vector<int> computeStronglyConnectedComponents() const {
        vector<int> component(numberOfNodes, -1);
        vector<int> low(numberOfNodes, -1), disc(numberOfNodes, -1);
        vector<bool> inStack(numberOfNodes, false);
        stack<int> nodeStack;
        int timeCounter = 0, componentCounter = 0;
        function<void(int)> tarjanDFS = [&](int node) {
            disc[node] = low[node] = timeCounter++;
            nodeStack.push(node);
            inStack[node] = true;
            auto edgeRange = (*this)[node];
            for (const Edge* ptr = edgeRange.first; ptr != edgeRange.second; ++ptr) {
                int next = ptr->to;
                if (disc[next] == -1) {
                    tarjanDFS(next);
                    low[node] = min(low[node], low[next]);
                } else if (inStack[next]) {
                    low[node] = min(low[node], disc[next]);
                }
            }
            if (low[node] == disc[node]) {
                while (true) {
                    int cur = nodeStack.top(); nodeStack.pop();
                    inStack[cur] = false;
                    component[cur] = componentCounter;
                    if (cur == node) break;
                }
                componentCounter++;
            }
        };
        for (int node = 0; node < numberOfNodes; node++) {
            if (disc[node] == -1) tarjanDFS(node);
        }
        return component;
    }

    // ===============================
    // ===============================
    // Module 2 (continued): Bridges and Articulation Points
    pair<vector<pair<int, int>>, vector<int>> computeBridgesAndArticulationPoints() const {
        assert(!Directed && "Only for undirected graphs.");
        vector<int> discovery(numberOfNodes, -1), low(numberOfNodes, -1);
        vector<bool> visited(numberOfNodes, false), isArticulation(numberOfNodes, false);
        vector<pair<int, int>> bridges;
        int timeCounter = 0;
        function<void(int, int)> dfsBridge = [&](int node, int parent) {
            visited[node] = true;
            discovery[node] = low[node] = timeCounter++;
            int children = 0;
            auto edgeRange = (*this)[node];
            for (const Edge* ptr = edgeRange.first; ptr != edgeRange.second; ++ptr) {
                int next = ptr->to;
                if (next == parent) continue;
                if (!visited[next]) {
                    children++;
                    dfsBridge(next, node);
                    low[node] = min(low[node], low[next]);
                    if (low[next] > discovery[node])
                        bridges.push_back({node, next});
                    if (parent != -1 && low[next] >= discovery[node])
                        isArticulation[node] = true;
                } else {
                    low[node] = min(low[node], discovery[next]);
                }
            }
            if (parent == -1 && children > 1)
                isArticulation[node] = true;
        };
        for (int i = 0; i < numberOfNodes; i++) {
            if (!visited[i]) dfsBridge(i, -1);
        }
        vector<int> articulationPoints;
        for (int i = 0; i < numberOfNodes; i++) {
            if (isArticulation[i]) articulationPoints.push_back(i);
        }
        return {bridges, articulationPoints};
    }

    // ===============================
    // ===============================
    // Module 3: Maximum Flow (Dinic's Algorithm)
    Weight maxFlow(int source, int sink) const {
        static const Weight INF = numeric_limits<Weight>::max();
        assert(Directed && "Max Flow only for directed graphs.");
        struct FlowEdge {
            int from, to; Weight capacity, flow;
        };
        vector<FlowEdge> flowEdges;
        vector<vector<int>> graph(numberOfNodes);
        auto addFlowEdge = [&](int u, int v, Weight cap) {
            graph[u].push_back(flowEdges.size());
            flowEdges.push_back({u, v, cap, 0});
            graph[v].push_back(flowEdges.size());
            flowEdges.push_back({v, u, 0, 0});
        };
        for (const auto& e : edgeList) addFlowEdge(e.from, e.to, e.cost);
        Weight totalFlow = 0;
        while (true) {
            vector<int> level(numberOfNodes, -1);
            queue<int> q; q.push(source); level[source] = 0;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int id : graph[u]) {
                    const auto& e = flowEdges[id];
                    if (e.flow < e.capacity && level[e.to] == -1) {
                        level[e.to] = level[u] + 1;
                        q.push(e.to);
                    }
                }
            }
            if (level[sink] == -1) break;
            vector<int> ptr(numberOfNodes);
            function<Weight(int, Weight)> dfs = [&](int u, Weight pushed) {
                if (u == sink) return pushed;
                for (; ptr[u] < (int)graph[u].size(); ptr[u]++) {
                    int id = graph[u][ptr[u]];
                    auto& e = flowEdges[id];
                    if (level[e.to] == level[u] + 1 && e.flow < e.capacity) {
                        Weight tr = dfs(e.to, min(pushed, e.capacity - e.flow));
                        if (tr) {
                            e.flow += tr;
                            flowEdges[id ^ 1].flow -= tr;
                            return tr;
                        }
                    }
                }
                return (Weight)0;
            };
            while (Weight pushed = dfs(source, INF)) totalFlow += pushed;
        }
        return totalFlow;
    }

    // ===============================
    // ===============================
    // Module 4: Bipartite Matching (Hopcroft-Karp)
    pair<int, vector<int>> bipartiteMatching(int leftSize, int rightSize) const {
        int totalNodes = leftSize + rightSize;
        assert(numberOfNodes == totalNodes);
        vector<int> match(totalNodes, -1), dist(totalNodes);
        auto bfs = [&]() -> bool {
            queue<int> q;
            for (int i = 0; i < leftSize; i++) {
                dist[i] = (match[i] == -1) ? 0 : -1;
                if (match[i] == -1) q.push(i);
            }
            bool found = false;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                auto edges = (*this)[u];
                for (const Edge* ptr = edges.first; ptr != edges.second; ++ptr) {
                    int v = ptr->to;
                    if (v < leftSize) continue;
                    if (match[v] == -1) found = true;
                    else if (dist[match[v]] == -1) {
                        dist[match[v]] = dist[u] + 1;
                        q.push(match[v]);
                    }
                }
            }
            return found;
        };
        function<bool(int)> dfs = [&](int u) {
            auto edges = (*this)[u];
            for (const Edge* ptr = edges.first; ptr != edges.second; ++ptr) {
                int v = ptr->to;
                if (v < leftSize) continue;
                if (match[v] == -1 || (dist[match[v]] == dist[u] + 1 && dfs(match[v]))) {
                    match[u] = v;
                    match[v] = u;
                    return true;
                }
            }
            dist[u] = -1;
            return false;
        };
        int matching = 0;
        while (bfs())
            for (int i = 0; i < leftSize; i++)
                if (match[i] == -1 && dfs(i)) matching++;
        vector<int> leftMatch(leftSize);
        for (int i = 0; i < leftSize; i++)
            leftMatch[i] = match[i];
        return {matching, leftMatch};
    }

    // ===============================
    // ===============================
    // Module 5: Minimum Spanning Tree (Kruskal)
    pair<Weight, vector<int>> kruskalMST() const {
        vector<int> parent(numberOfNodes), rank(numberOfNodes, 0);
        iota(parent.begin(), parent.end(), 0);
        function<int(int)> find = [&](int x) {
            return parent[x] == x ? x : parent[x] = find(parent[x]);
        };
        auto unite = [&](int x, int y) {
            int rx = find(x), ry = find(y);
            if (rx == ry) return false;
            if (rank[rx] < rank[ry]) swap(rx, ry);
            parent[ry] = rx;
            if (rank[rx] == rank[ry]) rank[rx]++;
            return true;
        };
        vector<Edge> sortedEdges = edgeList;
        sort(sortedEdges.begin(), sortedEdges.end(), [&](const Edge &a, const Edge &b) {
            return a.cost < b.cost;
        });
        Weight total = 0;
        vector<int> used;
        for (const auto &e : sortedEdges) {
            if (unite(e.from, e.to)) {
                total += e.cost;
                used.push_back(e.id);
            }
        }
        return {total, used};
    }

    // ===============================
    // Module 6: Eulerian Path / Circuit
    vector<int> eulerianPath() const {
        vector<vector<pair<int, int>>> tempGraph(numberOfNodes);
        for (int u = 0; u < numberOfNodes; u++) {
            auto edgeRange = (*this)[u];
            for (const Edge* ptr = edgeRange.first; ptr != edgeRange.second; ++ptr) {
                tempGraph[u].push_back({ptr->to, ptr->id});
            }
        }
        int odd = 0, start = 0;
        for (int i = 0; i < numberOfNodes; i++) {
            if (tempGraph[i].size() % 2) {
                odd++;
                start = i;
            }
        }
        if (odd != 0 && odd != 2) return {};
        vector<int> path;
        stack<int> stk;
        stk.push(start);
        while (!stk.empty()) {
            int u = stk.top();
            if (!tempGraph[u].empty()) {
                auto [v, id] = tempGraph[u].back(); tempGraph[u].pop_back();
                stk.push(v);
            } else {
                path.push_back(u);
                stk.pop();
            }
        }
        reverse(path.begin(), path.end());
        return path;
    }

    // ===============================
    // Module 7: Topological Sort
    vector<int> topologicalSort() const {
        assert(Directed);
        vector<int> inDeg(numberOfNodes, 0);
        for (const auto& e : edgeList) inDeg[e.to]++;
        queue<int> q;
        for (int i = 0; i < numberOfNodes; i++) if (inDeg[i] == 0) q.push(i);
        vector<int> order;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            order.push_back(u);
            auto edgeRange = (*this)[u];
            for (const Edge* ptr = edgeRange.first; ptr != edgeRange.second; ++ptr) {
                if (--inDeg[ptr->to] == 0)
                    q.push(ptr->to);
            }
        }
        if ((int)order.size() != numberOfNodes) return {};
        return order;
    }

    // ===============================
    // Module 8: LCA and Heavy-Light Decomposition
    bool treeStructureBuilt = false;
    vector<int> depth, parent;
    vector<vector<int>> parentJump;
    int logNumberOfNodes = 0;

    void buildTreeStructure(int root = 0) {
        depth.assign(numberOfNodes, -1);
        parent.assign(numberOfNodes, -1);
        function<void(int, int)> dfs = [&](int u, int p) {
            parent[u] = p;
            depth[u] = (p == -1 ? 0 : depth[p] + 1);
            for (auto [e, end] = (*this)[u]; e != end; ++e) {
                int v = e->to;
                if (v != p) dfs(v, u);
            }
        };
        dfs(root, -1);
        logNumberOfNodes = 32 - __builtin_clz(numberOfNodes);
        parentJump.assign(logNumberOfNodes, vector<int>(numberOfNodes, -1));
        for (int v = 0; v < numberOfNodes; v++)
            parentJump[0][v] = parent[v];
        for (int i = 1; i < logNumberOfNodes; i++)
            for (int v = 0; v < numberOfNodes; v++)
                if (parentJump[i - 1][v] != -1)
                    parentJump[i][v] = parentJump[i - 1][parentJump[i - 1][v]];
        treeStructureBuilt = true;
    }

    int lowestCommonAncestor(int u, int v) const {
        assert(treeStructureBuilt);
        if (depth[u] < depth[v]) swap(u, v);
        int d = depth[u] - depth[v];
        for (int i = 0; i < logNumberOfNodes; i++)
            if (d & (1 << i)) u = parentJump[i][u];
        if (u == v) return u;
        for (int i = logNumberOfNodes - 1; i >= 0; i--)
            if (parentJump[i][u] != parentJump[i][v]) {
                u = parentJump[i][u];
                v = parentJump[i][v];
            }
        return parent[u];
    }

    vector<int> heavyLightHead, heavyLightPosition, heavyLightSubtreeSize;
    int currentHLDPosition = 0;

    void buildHeavyLightDecomposition(int root = 0) {
        heavyLightHead.assign(numberOfNodes, -1);
        heavyLightPosition.assign(numberOfNodes, -1);
        heavyLightSubtreeSize.assign(numberOfNodes, 0);
        currentHLDPosition = 0;
        function<void(int, int)> dfsSize = [&](int u, int p) {
            heavyLightSubtreeSize[u] = 1;
            for (auto [e, end] = (*this)[u]; e != end; ++e) {
                int v = e->to;
                if (v == p) continue;
                dfsSize(v, u);
                heavyLightSubtreeSize[u] += heavyLightSubtreeSize[v];
            }
        };
        dfsSize(root, -1);
        function<void(int, int, int)> dfsHLD = [&](int u, int p, int h) {
            heavyLightHead[u] = h;
            heavyLightPosition[u] = currentHLDPosition++;
            int heavy = -1, maxSize = -1;
            for (auto [e, end] = (*this)[u]; e != end; ++e) {
                int v = e->to;
                if (v == p) continue;
                if (heavyLightSubtreeSize[v] > maxSize) {
                    maxSize = heavyLightSubtreeSize[v];
                    heavy = v;
                }
            }
            if (heavy != -1) dfsHLD(heavy, u, h);
            for (auto [e, end] = (*this)[u]; e != end; ++e) {
                int v = e->to;
                if (v != p && v != heavy) dfsHLD(v, u, v);
            }
        };
        dfsHLD(root, -1, root);
    }

    vector<pair<int, int>> heavyLightPathQuery(int u, int v) const {
        assert(treeStructureBuilt);
        vector<pair<int, int>> segments;
        while (heavyLightHead[u] != heavyLightHead[v]) {
            if (depth[heavyLightHead[u]] > depth[heavyLightHead[v]]) {
                segments.emplace_back(heavyLightPosition[heavyLightHead[u]], heavyLightPosition[u]);
                u = parent[heavyLightHead[u]];
            } else {
                segments.emplace_back(heavyLightPosition[heavyLightHead[v]], heavyLightPosition[v]);
                v = parent[heavyLightHead[v]];
            }
        }
        if (heavyLightPosition[u] > heavyLightPosition[v]) swap(u, v);
        segments.emplace_back(heavyLightPosition[u], heavyLightPosition[v]);
        return segments;
    }

    int getSubtreeSize(int node) const {
        assert(treeStructureBuilt && !heavyLightSubtreeSize.empty());
        return heavyLightSubtreeSize[node];
    }

    // ===============================
    // Module 9: Disjoint Set Union (DSU / Union-Find)
    struct DSU {
        vector<int> parent, rank;
        DSU(int n) {
            parent.resize(n);
            iota(parent.begin(), parent.end(), 0);
            rank.assign(n, 0);
        }
        int find(int x) {
            if (parent[x] != x)
                parent[x] = find(parent[x]);
            return parent[x];
        }
        bool unite(int x, int y) {
            x = find(x);
            y = find(y);
            if (x == y) return false;
            if (rank[x] < rank[y]) swap(x, y);
            parent[y] = x;
            if (rank[x] == rank[y]) rank[x]++;
            return true;
        }
    };

    // ===============================
    // Module 10: Floyd-Warshall (All-Pairs Shortest Paths)
    vector<vector<Weight>> floydWarshall(vector<vector<int>>* path = nullptr) const {
        const Weight INF = numeric_limits<Weight>::max() / 2;
        vector<vector<Weight>> dist(numberOfNodes, vector<Weight>(numberOfNodes, INF));
        if (path) path->assign(numberOfNodes, vector<int>(numberOfNodes, -1));
        for (int i = 0; i < numberOfNodes; i++) dist[i][i] = 0;
        for (const auto& e : edgeList) {
            if (e.cost < dist[e.from][e.to]) {
                dist[e.from][e.to] = e.cost;
                if (path) (*path)[e.from][e.to] = e.from;
            }
            if (!Directed && e.cost < dist[e.to][e.from]) {
                dist[e.to][e.from] = e.cost;
                if (path) (*path)[e.to][e.from] = e.to;
            }
        }
        for (int k = 0; k < numberOfNodes; k++) {
            for (int i = 0; i < numberOfNodes; i++) {
                for (int j = 0; j < numberOfNodes; j++) {
                    if (dist[i][k] < INF && dist[k][j] < INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        if (path) (*path)[i][j] = (*path)[k][j];
                    }
                }
            }
        }
        return dist;
    }

    vector<int> floydWarshallReconstructPath(int u, int v, const vector<vector<int>>& path) const {
        if (path[u][v] == -1) return {};
        vector<int> result = {v};
        while (v != u) {
            v = path[u][v];
            result.push_back(v);
        }
        reverse(result.begin(), result.end());
        return result;
    }
};
