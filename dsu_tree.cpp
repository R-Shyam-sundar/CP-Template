template<int lgn>
struct DSUtree{
    struct DSU{
        vector<int> parent;
        vector<int> sizof;
        vector<int> mergenum;
        set<int> roots;
        int n;
        int curr;
        DSU(int n) : n(n){
            curr = n;
            parent.resize(n);
            sizof.resize(n);
            mergenum.resize(n);
            for(int i=0;i<n;i++){
                parent[i]=i;
                sizof[i]=1;
                roots.insert(i);
                mergenum[i] = i;
            }
        }
        int get_size(int x){
            return sizof[find_set(x)];
        }
        int find_set(int v){
            if (v == parent[v])
                return v;
            return parent[v] = find_set(parent[v]);
        }
        int root_node(int u){
            return mergenum[find_set(u)];
        }
        void join_sets(int a, int b) {
            a = find_set(a);
            b = find_set(b);
            if (a != b) {
                if (sizof[a] < sizof[b]){
                    swap(a, b);
                }
                parent[b] = a;
                sizof[a] += sizof[b];
                roots.erase(b);
                mergenum[a] = curr;
                ++curr;
            }
        }
    };
    DSU dsu;
    LCA<lgn> lca;
    int n;
    DSUtree(int n) : n(n), dsu(n), lca(2 * n - 1) {}
    void add_edge(int u, int v){
        int ru = dsu.root_node(u);
        int rv = dsu.root_node(v);
        if(ru != rv) dsu.join_sets(u, v);
        lca.addedge(ru, dsu.root_node(u));
        lca.addedge(rv, dsu.root_node(v));
    }
    int root_node(int u){
        return dsu.root_node(u);
    }
    int find_set(int u){
        return dsu.find_set(u);
    }
    int get_size(int u){
        return dsu.get_size(u);
    }
    LCA<lgn> getDSUTree(){
        return lca;
    }
};


/*
 Source file:  https://codeforces.com/contest/1648/submission/148745210
*/

/*
  Application: 
    Finding the number of connected components in a graph
    Finding the size of the largest connected component in a graph
    Finding the minimum spanning tree of a graph
    Finding the shortest path between two nodes in a graph
    Finding the longest path between two nodes in a graph
    Finding the lowest common ancestor of two nodes in a tree
    Finding the diameter of a tree
*/
