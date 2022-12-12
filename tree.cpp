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

/*
  The Tree class is initialized with a single integer n,
  which specifies the number of nodes in the tree. 
  The Tree class has a member variable adj that stores the adjacency list of the tree,
  and the addedge method is used to add edges to the tree.
*/
