struct scc_graph {
  public:
    scc_graph(int n) : _n(n) {}
 
    int num_vertices() { return _n; }
 
    void add_edge(int from, int to) { edges.push_back({from, {to}}); }
 
    // @return pair of (# of scc, scc id)
    std::pair<int, std::vector<int>> scc_ids() {
        auto g = csr<edge>(_n, edges);
        int now_ord = 0, group_num = 0;
        std::vector<int> visited, low(_n), ord(_n, -1), ids(_n);
        visited.reserve(_n);
        auto dfs = [&](auto self, int v) -> void {
            low[v] = ord[v] = now_ord++;
            visited.push_back(v);
            for (int i = g.start[v]; i < g.start[v + 1]; i++) {
                auto to = g.elist[i].to;
                if (ord[to] == -1) {
                    self(self, to);
                    low[v] = std::min(low[v], low[to]);
                } else {
                    low[v] = std::min(low[v], ord[to]);
                }
            }
            if (low[v] == ord[v]) {
                while (true) {
                    int u = visited.back();
                    visited.pop_back();
                    ord[u] = _n;
                    ids[u] = group_num;
                    if (u == v) break;
                }
                group_num++;
            }
        };
        for (int i = 0; i < _n; i++) {
            if (ord[i] == -1) dfs(dfs, i);
        }
        for (auto& x : ids) {
            x = group_num - 1 - x;
        }
        return {group_num, ids};
    }
 
    std::vector<std::vector<int>> scc() {
        auto ids = scc_ids();
        int group_num = ids.first;
        std::vector<int> counts(group_num);
        for (auto x : ids.second) counts[x]++;
        std::vector<std::vector<int>> groups(ids.first);
        for (int i = 0; i < group_num; i++) {
            groups[i].reserve(counts[i]);
        }
        for (int i = 0; i < _n; i++) {
            groups[ids.second[i]].push_back(i);
        }
        return groups;
    }
 
  private:
    int _n;
    struct edge {
        int to;
    };
    std::vector<std::pair<int, edge>> edges;
};

/*
This code defines a class scc_graph which represents a directed graph. The class has several methods:

num_vertices() returns the number of vertices in the graph.
add_edge(from, to) adds an edge from the vertex from to the vertex to.
scc_ids() returns a pair of the number of strongly connected components (SCCs) in the graph and a vector containing the SCC ids of each vertex.
scc() returns a vector of strongly connected components (SCCs), where each SCC is represented as a vector of vertex indices.
The scc_graph class uses the csr function, which is not defined in this code, to represent the graph internally. 
It is likely that the csr function is used to create a compressed sparse row representation of the graph, 
which is a space-efficient way of storing the graph. The scc method uses depth-first search (DFS) to compute the SCCs of the graph.
It first assigns each vertex an SCC id and a low-link value and then performs DFS on the vertices. 
When the DFS reaches a vertex that has not been visited before, it explores the vertex's neighbors and updates their low-link values accordingly. 
If the low-link value of a vertex is equal to its DFS order, 
it indicates that the vertex is the root of an SCC and all the vertices in the current DFS path form a strongly connected component. 
The scc method then returns a vector of the SCCs of the graph, where each SCC is represented as a vector of vertex indices.






*/
