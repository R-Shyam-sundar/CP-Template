template<typename T>
struct merge_sort_tree{
    int n;
    int cnt = 0;
    vector<indexed_set<pair<T, int>>> mt;
    merge_sort_tree(int _n) : n(_n), mt(_n << 1) {}
    void add_element(int pos, T val){
        pos += n;
        while(pos){
            mt[pos].insert(make_pair(val, cnt));
            pos >>= 1;
        }
        cnt++;
    }
    int query_node(int u,int l,int r){
        return mt[u].order_of_key(make_pair(r, 1e9)) - mt[u].order_of_key(make_pair(l, -1));
    }
    int query(int l,int r, int vl, int vr){
        if(r < 0) return 0;
        int ans = 0;
        l += n;
        r += n + 1;
        while(l < r){
            if(l & 1){
                ans += query_node(l++, vl, vr);
            }
            if(r & 1){
                ans += query_node(--r, vl, vr);
            }
            l >>= 1;
            r >>= 1;
        }
        return ans;
    }
};

int main()
{
    // This creates a merge sort tree for an array of size 10.
    merge_sort_tree<int> tree(10);
  
    // Once you have created the tree, you can add elements to it using the add_element() method. 
    // This method takes as input the position in the array where the element should be added, as well as the value of the element to be added. 
    // This adds the value 5 to the array at position 0.
    tree.add_element(0, 5);
  
    // This returns the number of values in the range [3, 7] within the sub-array [0, 5] of the original array.
    int num_values = tree.query(0, 5, 3, 7); 
}

/*
  Source file:  https://codeforces.com/contest/1010/submission/153844103
*/

/*
  This code defines a class merge_sort_tree that implements a data structure called a merge sort tree. 
  This data structure allows for efficient range queries over an array.
  It is similar to a binary indexed tree or a segment tree, but instead of storing a single value at each node, 
  it stores a sorted set of the values that appear in the sub-array represented by that node. 
  This allows for efficient queries that return the number of values in a given range within the sub-array.

  To use this data structure, you first need to create an instance of merge_sort_tree 
  and pass it the size of the array you want to create the tree for. For example:
  
  Time complexity:
    The time complexity of adding an element to the tree is O(log n), 
    where n is the size of the array. 
    This is because the element needs to be inserted into each of the nodes 
    in the tree that represent sub-arrays containing the position where the element was added. 
    Since there are log n levels in the tree, this operation takes O(log n) time.

    The time complexity of performing a range query is also O(log n). 
    This is because the query needs to be performed at each of the nodes 
    in the tree that represent sub-arrays that overlap with the query range. 
    Since there are log n levels in the tree, this operation also takes O(log n) time.
*/
