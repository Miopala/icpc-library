class edge{
    public:
    int to,cap,rev; // vertex, capacity, label of corresponding edge in residual network
};

class dinic { // implementation for dinic's algorithm which solves maximum flow problem
    public:
    const int inf = (int)1e18+9;
    vector <int> iter; // last edge when iterating over augmenting paths
    vector <int> lvl; // level in bfs
    vector <vector<edge>> P; // vector of edges
    int n; // number of vertices
    dinic () {}
    dinic (int _n) {
        n = _n;
        iter.resize(n+1);
        lvl.resize(n+1);
        P.resize(n+1);
    }

    void bfs (int s) {
        queue <int> q;
        q.push(s);
        lvl[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto it : P[u]) {
                if (lvl[it.to] == -1 && it.cap > 0) {
                    lvl[it.to] = lvl[u]+1;
                    q.push(it.to);
                }
            }
        }
    }

    int dfs (int u, int t, int f) {
        if (u == t) return f;
        for (int &i = iter[u]; i<sz(P[u]); i++) {
            auto &it = P[u][i];
            if (it.cap == 0 || lvl[it.to] != lvl[u]+1) continue;
            int flow = dfs(it.to, t, min(f, it.cap));
            if (flow == 0) continue;
            it.cap -= flow;
            P[it.to][it.rev].cap += flow;
            return flow;
        }
    }

    int maximum_flow (int s, int t) { 
        int ans = 0;
        while (true) {
            memset(lvl, -1, sizeof(lvl));
            bfs(s);
            if (lvl[t] == -1) break;
            memset(iter, 0, sizeof(iter));
            while (true) {
                int f = dfs(s, t, inf);
                if (f == 0) break;
                ans += f;
            }
        }
        return ans;
    }
};