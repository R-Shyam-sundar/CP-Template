template<typename T>
struct LineTree{
    struct DSU{
        vector<int> parent;
        vector<int> sizof;
        vector<array<int, 2>> line;
        vector<int> nxt;
        vector<T> nxtw;
        int n;
        DSU(int n) : n(n){
            parent.resize(n);
            sizof.resize(n);
            line.resize(n);
            nxt.resize(n);
            nxtw.resize(n);
            for(int i=0;i<n;i++){
                parent[i]=i;
                sizof[i]=1;
                line[i] = {i,i};
                nxt[i] = i;
                nxtw[i] = 0;
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
        void join_sets(int a, int b, T w) {
            a = find_set(a);
            b = find_set(b);
            if (a != b) {
                if (sizof[a] < sizof[b]){
                    swap(a, b);
                }
                parent[b] = a;
                sizof[a] += sizof[b];
                nxt[line[b][1]] = line[a][0];
                nxtw[line[b][1]] = w;
                line[a] = {line[b][0], line[a][1]};
            }
        }
    };
    vector<tuple<T,int,int>> edges;
    DSU dsu;
    int n;
    function<bool(T, T)> cmp;
    LineTree(int n, function<bool(T, T)> cmp) : dsu(n), n(n), cmp(cmp) {}
    void add_edge(int u, int v, T w){
        edges.emplace_back(w, u, v);
    }
    tuple<vector<int>, vector<int>, vector<T>> computeLineTree(){
        sort(edges.begin(), edges.end(), [&](tuple<T, int, int> x, tuple<T, int, int> y){
            return cmp(get<0>(y), get<0>(x));
        });
        for(auto &[w,u,v] : edges){
            dsu.join_sets(u, v, w);
        }
        int root = dsu.find_set(0);
        vector<int> ord(n);
        ord[0] = dsu.line[root][0];
        for(int i=1;i<n;i++) ord[i] = dsu.nxt[ord[i-1]];
        vector<int> id(n);
        for(int i=0;i<n;i++) id[ord[i]] = i;
        vector<int> wts(n - 1);
        for(int i=0;i+1<n;i++) wts[i] = dsu.nxtw[ord[i]];
        return {ord, id, wts};
    }
};

/*
  Source code:  https://codeforces.com/contest/1628/submission/154790085
*/

/*
  LineTree:
  The LineTree class represents a data structure for storing a line tree, 
  a type of tree data structure in which the leaves form a line. 
  The class is parameterized by the type of the edge weights, T, 
  which can be any type for which a cmp function is provided. 
  The cmp function should take two T values and return a bool indicating whether the first value is "less than" the second value. 
  This is used to sort the edges when building the line tree.

  The LineTree class has the following member functions:

  add_edge: Adds an edge to the line tree, with a given weight and two endpoints.
 
  computeLineTree: Builds the line tree by sorting the edges according to their weights 
  and using a disjoint set data structure to track connected components. 
  Returns a tuple containing three vectors: the order of the leaves in the line, 
  a mapping from each node to its position in the line, and the weights of the edges in the line tree.
  
  In the LineTree class, the disjoint set data structure is used to track connected components in the line tree. 
  Each disjoint set represents a connected component, 
  and the join_sets function is used to merge two sets when adding an edge to the line tree. 
  The computeLineTree function uses the cmp function to sort the edges in descending order by weight,
  and then adds the edges to the line tree in that order. 
  It then constructs the three vectors that are returned by the function.
  
  A line tree is a type of tree data structure in which the leaves form a line. 
  This means that the leaves of the tree are arranged in a linear order, 
  and each internal node in the tree has exactly two children. 
  Line trees are often used in computational geometry to represent the topology of a set of points in the plane. 
  They can be used to answer queries about the connectivity and relative positions of the points in the set.
*/

/*
  Code Explanation:
  
*/

/*
  Problem types:
  --------------------------------------------------------------------------------------------------------------------------------
  Problem: Given a set of points in the plane and a set of weighted edges connecting pairs of points, 
           find the minimum spanning tree of the point set such that the leaves of the tree form a line.
  Solution: 
          To solve this problem using this code, you would first create a LineTree object 
          and add each edge to the line tree using the add_edge function. 
          Then, you would call the computeLineTree function to build the line tree. 
          The returned vectors would give you the information you need to answer queries about the minimum spanning tree.
  --------------------------------------------------------------------------------------------------------------------------------
  Problem: Given a set of points in the plane and a set of weighted edges connecting pairs of points, 
           find the minimum spanning tree of the point set such that the leaves of the tree form a line 
           and the maximum edge weight is minimized.
  Solution: 
           To solve this problem using this code, you would first create a LineTree object 
           and add each edge to the line tree using the add_edge function. 
           Then, you would call the computeLineTree function to build the line tree. 
           The returned vectors would give you the information you need to answer queries 
           about the minimum spanning tree with minimum maximum edge weight.
  --------------------------------------------------------------------------------------------------------------------------------
           
*/
