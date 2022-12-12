template<typename T>
struct segment_tree {
    int n;
    vector<T> segtree;
    function<T(const T&,const T&)> join;
    T base = T();
    segment_tree(int n, function<T(const T&,const T&)> join, T base = T()) : n(n), join(join), base(base){
        segtree.resize(n << 1, base);
    }
    void build() {
        for (int i = n - 1; i > 0; --i) {
            segtree[i] = join(segtree[(i << 1)], segtree[(i << 1) | 1]);
        }
    }
    segment_tree(vector<T> seq, function<T(const T&,const T&)> join, T base = T()) : n(seq.size()), join(join), base(base){
        segtree.resize(n << 1, base);
        for (int i = 0; i < n; i++) {
            segtree[n + i] = seq[i];
        }
        build();
    }
    void calc(int pos){
        pos >>= 1;
        while (pos) {
            segtree[pos] = join(segtree[pos << 1], segtree[(pos << 1) | 1]);
            pos >>= 1;
        }
    }
    void set(int pos, T val){
        pos+=n;
        segtree[pos] = val;
        calc(pos);
    }
    void increment(int pos, T val){
        pos+=n;
        segtree[pos] = join(segtree[pos], val);
        calc(pos);
    }
    T query(int l, int r) {
        T ansl = base;
        T ansr = base;
        l += n;
        r += n + 1;
        while (l < r) {
            if (l & 1) {
                ansl = join(ansl, segtree[l++]);
            }
            if (r & 1) {
                ansr = join(segtree[--r], ansr);
            }
            l >>= 1;
            r >>= 1;
        }
        return join(ansl, ansr);
    }
};

/*
  A segment tree is a data structure that allows efficient queries on intervals of an array. 
  It can be used to efficiently compute the sum, minimum, maximum, 
  or other aggregate value of a range of elements in an array.

  The code you provided uses a template, 
  so it can work with any data type that supports the operations specified in the template argument. 
  The segment tree is represented as a vector of elements, segtree, which is initialized to have a size of n times 2, 
  where n is the number of elements in the array. The vector is then filled with the elements of the array, 
  and the build() function is called to construct the segment tree.

  The build() function uses a loop to compute the values of the nodes in the segment tree 
  by applying the join function to the values of the child nodes. 
  The join function is specified as a function object in the constructor of the segment tree, 
  and it determines how the values of the nodes in the segment tree are computed from the values of the array elements.

  The set() and increment() functions can be used to modify the value of an element in the array 
  and update the segment tree accordingly. 
  The query() function can be used to efficiently compute the aggregate value of a range of elements in the array.

  Overall, this implementation of a segment tree is a useful and 
  efficient data structure for performing range queries on arrays.
*/
