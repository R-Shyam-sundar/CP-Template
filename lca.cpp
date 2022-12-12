struct Tree{ //0 indexed
    int n;
    vector<vector<int>> adj;
    Tree(int n) : n(n){
        adj.resize(n);
    }
    void addedge(int u,int v){
        adj[u].pb(v);
        adj[v].pb(u);
    }
};
struct EulerTour : Tree{
    private : 
    int t;
    void dfs(int u,int p){
        tin[u] = t++;
        eulertour.push_back(u);
        for(const auto &v : adj[u]){
            if(v!=p)
            dfs(v,u);
        }
        tout[u] = t++;
        eulertour.push_back(u);
    }
    public:
    vector<int> tin, tout, eulertour;
    void ComputeEulerTour(int root = 0){
        t = 0;
        tin.resize(n), tout.resize(n), eulertour.reserve(n<<1);
        dfs(root,root);
    }
    bool isanc(int u,int v){ //returns true if u is ancestor of v
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }
    EulerTour(int n) : Tree(n) {}
};
template<int lgn>
struct LCA : EulerTour{
    vector<array<int,lgn>> par;
    int root;
    private:
    void dfs(int u,int p){
        par[u][0] = p;
        for(int i=1;i<lgn;i++){
            par[u][i] = par[par[u][i-1]][i-1];
        }
        for(const auto &v : adj[u]){
            if(v==p) continue;
            dfs(v,u);
        }
    }
    public:
    LCA(int n) : EulerTour(n) {
        par.resize(n);
    }
    void computeLCA(int Root){
        root = Root;
        ComputeEulerTour(root);
        dfs(root,root);
    }
    int getLCA(int u,int v){
        if(isanc(u,v)) return u;
        if(isanc(v,u)) return v;
        for(int i=lgn-1;i>=0;--i){
            if(!isanc(par[u][i], v)) u = par[u][i];
        }
        return par[u][0];
    }
    int kthancestor(int u,int k){
        for(int i=0;i<lgn;i++){
            if(k&(1<<i)) u = par[u][i];
        }
        return u;
    }
};

/*
  This code defines a class called LCA that extends the EulerTour class. T
  he LCA class is used to compute the lowest common ancestor (LCA) of two nodes in a tree. 
  The LCA class has several private and public methods.

  The private dfs method is used to compute the LCA of each node in the tree.
  It takes as arguments a node u and its parent p. 
  For each node u, the method computes the LCA of u and its parent p, and stores this value in the par array. 
  The par array is a two-dimensional array that is used to store the ancestors of each node at different depths in the tree.

  The public computeLCA method is used to compute the LCA of the tree. 
  It takes as argument the root of the tree, which is used to initialize the EulerTour class and to compute the Euler tour of the tree. 
  The method then calls the private dfs method to compute the LCA of each node in the tree.

  The getLCA method is used to find the LCA of two nodes u and v. 
  It first checks whether one of the nodes is an ancestor of the other, and if so, it returns the ancestor node. 
  Otherwise, it uses the par array to find the LCA of the two nodes.

  The kthancestor method is used to find the kth ancestor of a given node u. 
  It uses the par array to efficiently compute the kth ancestor of u by moving up the tree in logarithmic time.

  The LCA class constructor takes an argument n, which specifies the number of nodes in the tree. 
  It uses this value to initialize the base EulerTour class and then allocates space for the par array.

*/

// Construct the LCA object with n nodes
LCA<20> lca(n);

// Compute the LCA of the tree
lca.computeLCA(0);  // Use the root node with index 0 as the root of the tree

// Answer each query
for (int i = 0; i < m; i++) {
  int u, v;
  cin >> u >> v;

  // Find the LCA of u and v
  int ans = lca.getLCA(u, v);
  cout << "The LCA of nodes " << u << " and " << v << " is " << ans << endl;
}

