/*
    ================================
    Eulerian Path Template (C++)
    ================================

    Supports:
    - Directed graphs
    - Undirected graphs (with correct edge pairing)

    Nodes are 1-indexed.

    === How to use ===

    // Create the EulerianPath object:
    // Parameters: number of nodes, and directed flag (true = directed, false = undirected)
    EulerianPath ep(N, true); // for directed graph
    EulerianPath ep(N, false); // for undirected graph

    // Add edges:

    // Directed graph: add edges one way only
    ep.add_edge(u, v);

    // Undirected graph: add edges using add_undirected_edge,
    // which adds both directions and marks paired edges
    ep.add_undirected_edge(u, v);

    // After adding edges, get the Eulerian path/walk:
    std::vector<int> path = ep.get_path();

    if (path.empty()) {
        // No Eulerian path/cycle exists
    } else {
        // path contains the Eulerian path (list of nodes visited in order)
    }
*/

struct EulerianPath {
    int n;
    bool directed;
    std::vector<std::vector<std::pair<int, int>>> graph; // node -> (neighbor, edge id)
    std::vector<int> in_deg, out_deg, deg;
    std::vector<int> path;
    std::vector<bool> used_edge;
    std::vector<int> paired_edge; // For undirected edges, paired edge IDs
    int edge_id = 0;

    EulerianPath(int nodes, bool is_directed = true) : n(nodes), directed(is_directed) {
        graph.resize(n + 1);
        in_deg.assign(n + 1, 0);
        out_deg.assign(n + 1, 0);
        deg.assign(n + 1, 0);
        used_edge.clear();
        paired_edge.clear();
        edge_id = 0;
    }

    // For directed edge: single call
    void add_edge(int u, int v) {
        graph[u].emplace_back(v, edge_id);
        if (directed) {
            out_deg[u]++;
            in_deg[v]++;
        } else {
            deg[u]++;
        }
        used_edge.push_back(false);
        paired_edge.push_back(-1); // no pair for directed edges
        edge_id++;
    }

    // For undirected edge: add both directions at once, link paired edges
    void add_undirected_edge(int u, int v) {
        graph[u].emplace_back(v, edge_id);
        graph[v].emplace_back(u, edge_id + 1);

        deg[u]++;
        deg[v]++;

        used_edge.push_back(false);
        used_edge.push_back(false);

        paired_edge.push_back(edge_id + 1);
        paired_edge.push_back(edge_id);

        edge_id += 2;
    }

    bool is_eulerian_path(int& start) {
        int start_nodes = 0, end_nodes = 0;
        start = 1;

        if (directed) {
            for (int i = 1; i <= n; ++i) {
                int diff = out_deg[i] - in_deg[i];
                if (diff == 1) {
                    start_nodes++;
                    start = i;
                } else if (diff == -1) {
                    end_nodes++;
                } else if (diff != 0) {
                    return false;
                }
            }
            return (start_nodes == 0 && end_nodes == 0) || (start_nodes == 1 && end_nodes == 1);
        } else {
            for (int i = 1; i <= n; ++i) {
                if (deg[i] % 2 == 1) {
                    start_nodes++;
                    start = i;
                }
            }
            return start_nodes == 0 || start_nodes == 2;
        }
    }

    void dfs(int u) {
        while (!graph[u].empty()) {
            auto [v, id] = graph[u].back();
            graph[u].pop_back();

            if (used_edge[id]) continue;

            used_edge[id] = true;
            if (!directed && paired_edge[id] != -1)
                used_edge[paired_edge[id]] = true;

            dfs(v);
        }
        path.push_back(u);
    }

    std::vector<int> get_path() {
        int start;
        if (!is_eulerian_path(start)) return {};

        dfs(start);
        std::reverse(path.begin(), path.end());

        int expected_size = directed ? edge_id + 1 : (edge_id / 2) + 1;
        if ((int)path.size() != expected_size) return {};

        return path;
    }
};