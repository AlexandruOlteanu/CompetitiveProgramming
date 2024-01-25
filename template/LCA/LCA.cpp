/*
    Template created by Alexandru Olteanu (Source: Topcoder)

    Initialize lvl starting from 0

    How to use: 
        1. LCA<int> lca(n);
        1. populate parrent, level
        2. Call lca.build()
        3. Call lca.query(a, b) whenever needed
*/
template<typename A>
struct LCA {

    vector<A> parrent;
    vector<A> level;
    vector<vector<A>> V;
    int n;
    LCA(int length){
        parrent.resize(length + 1);
        level.resize(length + 1);
        V.resize(length + 1);
        n = length;
        int logMax = 0;
        int p = 1;
        while (p <= n) ++logMax, p *= 2;
        for (int i = 1; i <= n; ++i) {
            V[i].resize(logMax + 1, -1);
        }
    }

    void buildLCA() {
        for (int i = 1; i <= n; ++i) {
            V[i][0] = parrent[i];
        }
        for (int j = 1; 1 << j <= n; j++) {
            for (int i = 1; i <= n; i++) {
                if (V[i][j - 1] != -1) {
                    V[i][j] = V[V[i][j - 1]][j - 1];
                }
            }
        }
    }

    int query(int a, int b) {
        int log, i;

        //if a is situated on a higher level than b then we swap them
        if (level[a] < level[b])
            swap(a, b);

        //we compute the value of [log(level[a)]
        for (log = 1; 1 << log <= level[a]; ++log);
        --log;

        //we find the ancestor of node a situated on the same level
        //with b using the values in V
        for (i = log; i >= 0; --i) {
            if (level[a] - (1 << i) >= level[b]) {
                a = V[a][i];
            }
        }

        if (a == b)
            return a;

        //we compute LCA(a, b) using the values in V
        for (i = log; i >= 0; --i) {
            if (V[a][i] != -1 && V[a][i] != V[b][i]) {
                a = V[a][i], b = V[b][i];
            }
        }

        return parrent[a];
    }
};