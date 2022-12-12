struct DSU{
    vector<int> parent;
    vector<int> sizof;
    int n;
    DSU(int N){
        n=N;
        parent.resize(n);
        sizof.resize(n);
        for(int i=0;i<n;i++){
            parent[i]=i;
            sizof[i]=1;
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
    void join_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (sizof[a] < sizof[b]){
                swap(a, b);
            }
            parent[b] = a;
            sizof[a] += sizof[b];
        }
    }
};

/*
  Code Explanation:
  This code appears to define a class called DSU, which stands for "disjoint set union."
  The class represents a data structure that can be used to track sets of elements that are disjoint (i.e., have no elements in common) 
  and support the operations of union (joining two sets together) and find (determining which set a given element belongs to).

  The class is initialized with an integer N, 
  which specifies the number of elements in the set. 
  It maintains two instance variables: parent, which is an array of size N that stores the parent of each element, 
  and sizof, which is an array of size N that stores the size of each set (i.e., the number of elements in the set).

  The class has several methods:
  find_set(v): returns the identifier of the set that the element v belongs to. 
  This is done by following the chain of parent pointers from v to the root of the tree until the root is found. 
  Along the way, the parent pointers are updated using path compression, 
  which has the effect of making the tree "flat" and reducing the time complexity of future find_set operations.

  join_sets(a, b): combines the sets that contain elements a and b by setting the parent of one of the roots to be the other. 
  The choice of which root to set as the parent is determined by the relative sizes of the sets, 
  with the smaller set becoming a child of the larger set. 
  This operation also updates the sizof array to reflect the new sizes of the sets.

  get_size(x): returns the size of the set that contains element x. 
  This is done by calling find_set(x) to determine the root of the tree, 
  and then returning the size of that set from the sizof array.
  
  Usage:
  Disjoint set union is a useful data structure in competitive programming because it 
  supports efficient implementations of the union and find operations, 
  which are often used in algorithms for solving problems involving sets of elements. 
  Some examples of problems that can be solved using disjoint set union include:

  Kruskal's algorithm for finding the minimum spanning tree of a graph. 
  This algorithm repeatedly finds the cheapest edge that connects two distinct components of the graph and adds it to the tree, 
  using disjoint set union to efficiently keep track of the connected components as the tree grows.
 
  Finding the connected components of an undirected graph. 
  This can be done by iterating over the edges of the graph and using disjoint set union 
  to combine the sets of vertices that are connected by each edge.
  
  Dynamic connectivity problems, where we are given a sequence of operations 
  (e.g., "add an edge between vertex X and vertex Y" or "is vertex X connected to vertex Y?") 
  and must maintain an efficient data structure that allows us to quickly answer the queries. 
  Disjoint set union can be used to implement this data structure, 
  with each connected component of the graph represented by a distinct set.
  
  The Hopcroft-Karp algorithm for finding maximum matching in a bipartite graph, 
  which involves repeatedly finding augmenting paths (paths that increase the size of the matching) 
  and using disjoint set union to keep track of the unmatched vertices in the graph.

*/

/*
      Problems In which DSU can be used.
      -----------------------------------------------------------------------------------------------------------------------------
      1. Problem: Given an undirected graph with N vertices and M edges, determine the number of connected components in the graph.
      
      Solution:
      We can use disjoint set union to solve this problem as follows:

      1. Initialize a DSU object with N elements, where each element is initially in its own set.
      2. Iterate over the edges of the graph, and for each edge (u, v):
      3. Use the find_set method to determine the sets that u and v belong to.
      4. If the sets are different (i.e., u and v belong to different connected components), 
         use the join_sets method to combine them into a single set.
      5. After all the edges have been processed, count the number of sets that have more than one element 
         (i.e., count the number of non-trivial connected components). 
         This can be done by iterating over the elements of the parent array and using the find_set method 
         to determine the set that each element belongs to, then keeping a count of the number of sets that have been seen.
      6. The time complexity of this solution is O(N + M * log N), 
         where N is the number of vertices and M is the number of edges. 
         This is because each find_set and join_sets operation takes O(log N) time, and there are O(M) such operations in total.
      -----------------------------------------------------------------------------------------------------------------------------
      2. Problem: Given an undirected graph with N vertices and M edges, 
         and a list of K queries of the form "is vertex x connected to vertex y?", determine the answer to each query.
         
         Solution: 
         1. Initialize a DSU object with N elements, where each element is initially in its own set.
         2. Iterate over the edges of the graph, and for each edge (u, v):
         3. Use the find_set method to determine the sets that u and v belong to.
         4. If the sets are different (i.e., u and v belong to different connected components), 
            use the join_sets method to combine them into a single set.
         5. After the graph has been processed, iterate over the queries and for each query (x, y):
         6. Use the find_set method to determine the sets that x and y belong to.
         7. If the sets are the same (i.e., x and y belong to the same connected component), 
            output "YES" to indicate that x is connected to y. Otherwise, output "NO" to indicate that x and y are not connected.
         8. The time complexity of this solution is O(N + M * log N + K * log N), 
            where N is the number of vertices, M is the number of edges, and K is the number of queries. 
            This is because each find_set and join_sets operation takes O(log N) time, and there are O(M + K) such operations in total.
      -----------------------------------------------------------------------------------------------------------------------------
      3. Problem: Given an undirected graph with N vertices and M edges, find the minimum spanning tree of the graph 
         (i.e., a subset of the edges that connects all the vertices together, with the minimum possible total edge weight).
         
         Solution:
         1. Initialize a DSU object with N elements, where each element is initially in its own set.
         2. Sort the edges of the graph by ascending edge weight.
         3. Initialize an empty list to store the edges of the minimum spanning tree.
         4. Iterate over the edges in the sorted list, and for each edge (u, v, w) with weight w:
         5. Use the find_set method to determine the sets that u and v belong to.
         6. If the sets are different (i.e., u and v belong to different connected components), 
            use the join_sets method to combine them into a single set and add the edge (u, v, w) to the minimum spanning tree.
         7. After all the edges have been processed, the minimum spanning tree will be stored in the list that was initialized in step 3.
         8. The time complexity of this solution is O(N * log N + M * log M), 
            where N is the number of vertices and M is the number of edges. 
            This is because the sorting step takes O(M * log M) time, and each find_set and join_sets operation takes O(log N) time, 
            and there are O(M) such operations in total.
      -----------------------------------------------------------------------------------------------------------------------------
      4. Problem: Given a bipartite graph with N vertices on the left and M vertices on the right, and K edges between them, 
         find a maximum matching (i.e., a subset of the edges that includes the maximum number of edges such that no two edges share a vertex).
         
         Solution:
         We can use disjoint set union to solve this problem using the Hopcroft-Karp algorithm, as follows:
         
         1. Initialize a DSU object with N + M elements, where each element is initially in its own set. 
            This represents the unmatched vertices in the graph.
         2. Initialize a list of edges in the matching to be empty.
         3. While there are unmatched vertices on the left side of the graph:
         4. Pick an unmatched vertex u on the left side of the graph.
         5. Use breadth-first search to find an augmenting path starting at u, 
            which is a path of alternating unmatched and matched edges that ends at an unmatched vertex on the right side of the graph.
         6. If an augmenting path is found, use disjoint set union to "augment" the matching 
            by adding the unmatched edges on the path to the matching and removing the matched edges on the path. 
            This is done by calling join_sets on each edge in the path to combine the sets that the endpoints of the edge belong to.
         7. If no augmenting path is found, stop the search and return the current matching.
         8. After the search is finished, the list of edges in the matching will contain the maximum matching of the graph.
         9. The time complexity of this solution is O(K * sqrt(N)), 
            where N is the number of vertices on the left side of the graph and K is the number of edges in the graph. 
            This is because the breadth-first search is guaranteed to find an augmenting path in O(sqrt(N)) time, 
            and each find_set and join_sets operation takes O(log N) time, and there are O(K) such operations in total.
      -----------------------------------------------------------------------------------------------------------------------------
      5. Problem: Given a set of N points in the plane and a set of M line segments, 
         determine which points are inside the region bounded by the line segments.
         
         Solution:
         1. Initialize a DSU object with N elements, where each element is initially in its own set. 
            This represents the connected components of the points that are inside the region bounded by the line segments.
         2. Iterate over the line segments, and for each segment (u, v):
         3. Use the find_set method to determine the sets that the endpoints u and v belong to.
         4. If the sets are different (i.e., u and v belong to different connected components), 
            use the join_sets method to combine them into a single set. 
            This has the effect of connecting the two connected components and making them a single connected component.
         5. After all the line segments have been processed, 
            iterate over the points and use the find_set method to determine the set that each point belongs to. 
            A point is inside the region bounded by the line segments if and only if 
            it belongs to a set with more than one element (i.e., a non-trivial connected component).
         6. The time complexity of this solution is O(N + M * log N), 
            where N is the number of points and M is the number of line segments. 
            This is because each find_set and join_sets operation takes O(log N) time, and there are `O
      -----------------------------------------------------------------------------------------------------------------------------
      6. Problem: Given a list of N numbers and a list of M queries of the form "merge the numbers at indices x and y", 
         maintain a data structure that allows efficient answers to queries of the form 
         "what is the sum of all the numbers in the set containing the number at index x?"
         
         Solution:
         1. Initialize a DSU object with N elements, where each element is initially in its own set. This represents the sets of numbers in the list.
         2. Initialize an array sums of size N, where sums[i] is the sum of the numbers in the set containing the number at index i.
         3. Iterate over the queries and for each query (x, y):
         4. Use the find_set method to determine the sets that the numbers at indices x and y belong to.
         5. If the sets are different (i.e., the numbers at indices x and y belong to different sets), use the join_sets method to combine them into a single set. This has the effect of merging the two sets of numbers.
         6. After all the queries have been processed, to answer a query of the form "what is the sum of all the numbers in the set containing the number at index x?", use the find_set method to determine the set that the number at index x belongs to, and return the corresponding value from the sums array.
      -----------------------------------------------------------------------------------------------------------------------------
*/
