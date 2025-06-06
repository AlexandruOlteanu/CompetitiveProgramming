/*
    Template created by Alexandru Olteanu {AlexandruINV}
*/
struct DirectedGraphSCC {
    int N;
    vector<vector<int>> in, out, in_component;
    vector<int> used, visited, component;
    int scc_nr = -1;
 
    DirectedGraphSCC(int n) {
        N = n;
        in.resize(n + 1);
        out.resize(n + 1);
        in_component.resize(n + 1);
        component.resize(n + 1);
    }
 
    void dfs(int x) {
        used[x] = true;
        for (auto u : out[x]) {
            if (!used[u]) {
                dfs(u);
            }
        }
        visited.push_back(x);
    }

    void reversed_dfs(int x, int nr) {
        used[x] = true;
        component[x] = nr;
        in_component[nr].push_back(x);
        for (auto u : in[x]) {
            if (!used[u]) {
                reversed_dfs(u, nr);
            }
        }
    }
 
    void add_edge(int x, int y) {
        out[x].push_back(y);
        in[y].push_back(x);
    }
 
    int FindStronglyConnectedComponents() {
        used.assign(N + 1, false);
        visited.clear();
        for (int i = 1; i <= N; ++i) {
            if (!used[i]) {
                dfs(i);
            }
        }
        scc_nr = 1;
        used.assign(N + 1, false);
        for (int i = (int) visited.size() - 1; i >= 0; --i) {
            if (!used[visited[i]]) {
                reversed_dfs(visited[i], scc_nr++);
            }
        }
        --scc_nr;
        in_component.resize(scc_nr + 1);
        return scc_nr;
    }
 
    int c, init;
    vector<int> ret_cycle;
    bool detectcycle(int now, bool b0) {
        if (now == init and b0) {
            return true;
        }
        for (auto nxt : out[now])
            if (component[nxt] == c and !used[nxt]) {
                ret_cycle.emplace_back(nxt), used[nxt] = 1;
                if (detectcycle(nxt, true)) {
                    return true;
                }
                ret_cycle.pop_back();
            }
        return false;
    }
    
    vector<int> DetectCycle() {
        int ns = FindStronglyConnectedComponents();
        if (ns == N) {
            return {};
        }
        vector<int> cnt(ns + 1, 0);
        for (int i = 0; i < (int) component.size(); ++i) {
            ++cnt[component[i]];
        }
        c = find_if(cnt.begin(), cnt.end(), [](int x) { return x > 1; }) - cnt.begin();
        init = find(component.begin(), component.end(), c) - component.begin();
        used.assign(N + 1, false);
        ret_cycle.clear();
        detectcycle(init, false);
        return ret_cycle;
    }
 
    // After calling `FindStronglyConnectedComponents()`, generate a new graph by uniting all vertices
    // belonging to the same component(The resultant graph is DAG).
    DirectedGraphSCC GenerateTopologicalGraph() {
        DirectedGraphSCC newgraph(scc_nr);
        for (int i = 1; i <= N; ++i) {
            for (auto u : out[i]) {
                if (component[i] != component[u]) {
                    newgraph.add_edge(component[i], component[u]);
                }
            }
        }
        for (int i = 1; i <= scc_nr; ++i) {
            sort(newgraph.in[i].begin(), newgraph.in[i].end());
            sort(newgraph.out[i].begin(), newgraph.out[i].end());
            newgraph.in[i].erase(unique(newgraph.in[i].begin(), newgraph.in[i].end()), newgraph.in[i].end());
            newgraph.out[i].erase(unique(newgraph.out[i].begin(), newgraph.out[i].end()), newgraph.out[i].end());
        }
        newgraph.in_component = in_component;
        
        return newgraph;
    }
};