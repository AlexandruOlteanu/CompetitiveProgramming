
// https://github.com/AlexandruOlteanu/CompetitiveProgramming/blob/main/template/Graphs/TopoSort.cpp
// first build adjacent vector and that's it
vector<int> topoSort(int n, vector<vector<int>> adjacent) {
    vector<int> indeg(n + 1);
    for (int u = 1; u <= n; ++u)
        for (int v : adjacent[u]) ++indeg[v];

    queue<int> q;
    for (int v = 1; v <= n; ++v)
        if (indeg[v] == 0) q.push(v);

    vector<int> order;
    order.reserve(n);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : adjacent[u])
            if (--indeg[v] == 0) q.push(v);
    }
    return (order.size() == n) ? order : std::vector<int>{};  // empty ⇒ cycle
}