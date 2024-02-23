/*
    Programmer : Alexandru Olteanu
    Problem : https://codeforces.com/contest/1547/problem/G
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// GCC Optimizations
// #pragma GCC optimize("Ofast")
// #pragma GCC target("fma,sse,sse2,sse3,ssse3,sse4,popcnt")
// #pragma GCC target("abm,mmx,avx,avx2,tune=native")
// #pragma GCC optimize(3)
// #pragma GCC optimize("inline")
// #pragma GCC optimize("-fgcse")
// #pragma GCC optimize("-fgcse-lm")
// #pragma GCC optimize("-fipa-sra")
// #pragma GCC optimize("-ftree-pre")
// #pragma GCC optimize("-ftree-vrp")
// #pragma GCC optimize("-fpeephole2")
// #pragma GCC optimize("-ffast-math")
// #pragma GCC optimize("-fsched-spec")
// #pragma GCC optimize("unroll-loops")
// Useful
mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
#define FastEverything  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define HighPrecision cout<<fixed<<setprecision(17);
typedef long long ll;
typedef pair<int,int> pii;
ll const mod=1000000007LL;
ll const mod2 = 100000000LL;
ll const md=998244353LL;
ll mypowr(ll a,ll b, ll mod1) {ll res=1;if(b<0)b=0;a%=mod1; assert(b>=0);
for(;b;b>>=1){if(b&1)res=res*a%mod1;a=a*a%mod1;}return res;}
ll mypow(ll a,ll b) {ll res=1;if(b<0)b=0;assert(b>=0);
for(;b;b>>=1){if(b&1)res=res*a;a=a*a;}return res;}
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(), x.rend()

// ifstream in("input.txt");
// ofstream out("output.txt");
// #define cin in
// #define cout out

const ll infll = 9e18;
const int inf = 2e9;
const ll maxn = 2e5 + 5;

/*
    Template created by Alexandru Olteanu
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

int main() {

    FastEverything
    HighPrecision
    int test = 1;
    cin>>test;
    for (int tt = 1; tt <= test; ++tt) {

        int n, m;
        cin >> n >> m;
        DirectedGraphSCC graph(n);
        vector<bool> cycle(n + 1, false);
        for (int i = 1; i <= m; ++i) {
            int x, y;
            cin >> x >> y;
            if (x == y) {
                cycle[x] = true;
            }
            else {
                graph.add_edge(x, y);
            }
        }

        int nr_scc = graph.FindStronglyConnectedComponents();
        auto newg = graph.GenerateTopologicalGraph();

        vector<int> ways(nr_scc + 1, 0);
        queue<int> q;
        q.push(graph.component[1]);
        ways[graph.component[1]] = 1;
        while (!q.empty()) {
            int top = q.front();
            q.pop();
            for (auto u : newg.out[top]) {
                if (ways[u] <= 2) {
                    ++ways[u];
                    q.push(u);
                }
            }

        }

        for (int i = 1; i <= nr_scc; ++i) {
            if (ways[i] > 2) ways[i] = 2;
            if (ways[i] != 0 && (newg.in_component[i].size() > 1 || cycle[newg.in_component[i][0]])) {
                ways[i] = -1;
            }
        }

        for (int i = 1; i <= nr_scc; ++i) {
            if (ways[i] == -1) {
                q.push(i);
                while (!q.empty()) {
                    int top = q.front();
                    q.pop();
                    for (auto u : newg.out[top]) {
                        if (ways[u] == -1) continue;
                        ways[u] = -1;
                        q.push(u);
                    }
                }
            }
        }

        for (int i = 1; i <= n; ++i) {
            cout << ways[graph.component[i]] << " ";
        }

        cout << "\n";
    
        
    }

    return 0;
} 
