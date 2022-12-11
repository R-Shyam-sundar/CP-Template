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

/*
Code explanation:
  This code defines a class called EulerTour, which extends the Tree class.
  The EulerTour class has several private and public methods.

  The private dfs method is used to traverse the tree and compute the Euler tour of the tree. 
  It takes as arguments a node u and its parent p. 
  The method updates the tin and tout arrays, 
  which store the times when a node is first visited and last visited during the Euler tour, respectively. 
  The method also adds each visited node to the eulertour vector.

  The public ComputeEulerTour method can be called to compute the Euler tour of the tree. 
  It takes an optional argument root which specifies the root of the tree. 
  By default, the root is set to 0. 
  This method initializes the t, tin, tout, and eulertour vectors and 
  then calls the private dfs method to perform the tree traversal and compute the Euler tour.

  The isanc method can be used to determine whether a node u is an ancestor of another node v. 
  It returns true if u is an ancestor of v, and false otherwise. 
  This method uses the tin and tout arrays to determine whether node u appears in the Euler tour before or after node v.

  The EulerTour class constructor takes an argument n, which specifies the number of nodes in the tree. 
  It uses this value to initialize the base Tree class and then allocates space for the tin, tout, and eulertour vectors.
*/

/*
  Usage:
  The EulerTour class is intended to compute the Euler tour of a tree, 
  which is a sequence of nodes that traverses the tree in such a way that each edge is visited exactly twice. 
  The isanc method can be used to determine whether a node is an ancestor of another node in the tree.

  Once the Euler tour has been computed, it can be used to solve a variety of problems on trees.
  For example, it can be used to efficiently answer queries such as:

  Given two nodes u and v, find the lowest common ancestor of u and v.
  Given a node u and an integer k, find the kth ancestor of u.
  Given a node u and an integer k, find the kth descendant of u.
  These and other similar problems can be solved more efficiently using the Euler tour than with other tree traversal methods.
*/
