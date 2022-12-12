#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
#include<immintrin.h>
using namespace std;
using ll = long long int;
template<typename T>
ostream& operator+(ostream& out, const vector<T> &vec){
    for(const auto &x : vec){
        out<<x<<" ";
    }
    out<<"\n";
    return out;
}
template<typename T>
ostream& operator*(ostream& out, const vector<T> &vec){
    for(const auto &x : vec){
        out+x;
    }
    return out;
}
template<typename T>
istream& operator>>(istream& in, vector<T> &vec){
    for(auto &x : vec){
        in>>x;
    }
    return in;
}
typedef unsigned int v8u __attribute__((vector_size(32)));
template<typename T>
struct segment_tree_simd{
    int n;
    vector<T> segtree;
    T base = T();
    segment_tree_simd(int n, T base = T()) : n(n), base(base){
        segtree.resize(n << 1, base);
    }
    void build() {
        for (int i = n - 1; i > 0; --i) {
            segtree[i] = segtree[(i << 1)] + segtree[(i << 1) | 1];
        }
    }
    segment_tree_simd(vector<T> seq, T base = T()) : n(seq.size()), base(base){
        segtree.resize(n << 1, base);
        for (int i = 0; i < n; i++) {
            segtree[n + i] = seq[i];
        }
        build();
    }
    void calc(int pos){
        pos >>= 1;
        while (pos) {
            segtree[pos] = segtree[pos << 1] + segtree[(pos << 1) | 1];
            pos >>= 1;
        }
    }
    void set(int pos, T val){
        pos += n;
        for(int i=0;i<8;i++) segtree[pos][i] = val[i];
        calc(pos);
    }
    void increment(int pos, T val){
        pos+=n;
        segtree[pos] = segtree[pos] + val;
        calc(pos);
    }
    T query(int l, int r) {
        T ansl = base;
        T ansr = base;
        l += n;
        r += n + 1;
        while (l < r) {
            if (l & 1) {
                ansl = ansl + segtree[l++];
            }
            if (r & 1) {
                ansr = segtree[--r] + ansr;
            }
            l >>= 1;
            r >>= 1;
        }
        return ansl + ansr;
    }
};
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
uint64_t xorshift(const uint64_t& n,int i){
  return n^(n>>i);
}
uint64_t my_hash2(const uint64_t& n){
  uint64_t p = 0x5555555555555555ull; // pattern of alternating 0 and 1
  uint64_t c = 17316035218449499591ull;// random uneven integer constant; 
  return c*xorshift(p*xorshift(n,32),32);
}
unsigned int my_hash(unsigned int x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}
void solve(){
    int n,q;
    cin>>n>>q;
    vector<int> a(n);
    cin>>a;
    vector<v8u> mapped_to(3 * n);
    srand(7827);
    for(int i=0;i<3*n;i++){
        for(int j=0;j<8;j++) mapped_to[i][j] = rand() / 3;
    }
    v8u base;
    for(int i=0;i<8;i++) base[i] = 0;
    segment_tree_simd<v8u> st1(n, base);
    segment_tree_simd<v8u> st2(n, base);
    segment_tree_simd<v8u> st3(n, base);
    segment_tree<unsigned long long> st_xor(n, [&](unsigned long long x, unsigned long long y){
        return x ^ y;
    }, 0);
    for(int i=0;i<n;i++) st1.segtree[n + i] = mapped_to[my_hash(a[i]) % (3 * n)];
    for(int i=0;i<n;i++) st2.segtree[n + i] = mapped_to[my_hash(my_hash(a[i])) % (3 * n)];
    for(int i=0;i<n;i++) st3.segtree[n + i] = mapped_to[my_hash(my_hash(my_hash(a[i]))) % (3 * n)];
    for(int i=0;i<n;i++) st_xor.segtree[n + i] = my_hash2(a[i]);
    st1.build();
    st2.build();
    st3.build();
    st_xor.build();
    for(int i=0;i<q;i++){
        int t;
        cin>>t;
        if(t == 1){
            int i, x;
            cin>>i>>x;
            --i;
            st1.set(i, mapped_to[my_hash(x) % (3 * n)]);
            st2.set(i, mapped_to[my_hash(my_hash(x)) % (3 * n)]);
            st3.set(i, mapped_to[my_hash(my_hash(my_hash(x))) % (3 * n)]);
            st_xor.set(i, my_hash2(x));
        }
        else{
            int l,r,k;
            cin>>l>>r>>k;
            --l;--r;
            bool ans = 1;
            if(k == 1){
                cout<<"YES\n";
                continue;
            }
            if(k == 2){
                cout<<(st_xor.query(l, r) == 0 ? "YES" : "NO")<<"\n";
                continue;
            }
            auto hash1 = st1.query(l, r);
            auto hash2 = st2.query(l, r);
            auto hash3 = st3.query(l, r);
            for(int i=0;i<8;i++){
                ans &= (hash1[i] % k == 0);
                ans &= (hash2[i] % k == 0);
                ans &= (hash3[i] % k == 0);
            }
            cout<<(ans ? "YES" : "NO")<<"\n";
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}

/*
  The key difference between a regular segment tree and a segment tree with SIMD instructions is in how the query() function is implemented. 
  In a regular segment tree, the query() function would sum the values in the range one by one, 
  which can be slow if the array is large. 
  However, in a segment tree with SIMD instructions, 
  the query() function uses SIMD instructions to sum multiple values simultaneously,
  which can improve performance.

  The specific SIMD instructions used in the code you provided are the + and += operators,
  which are overloaded to use SIMD instructions when applied to objects of type v8u. 
  These operators are used in the query() function to sum the values in the range, 
  and they use SIMD instructions to perform the summing operation more efficiently.

  Overall, the use of SIMD instructions in the query() function 
  is the key difference between a regular segment tree and a segment tree with SIMD instructions, 
  and it is what allows the segment tree with SIMD instructions to perform better in certain scenarios.
  
  v8u is a typedef (short for "type definition") that defines a new type that represents a vector of 8 unsigned integers. 
  This type is used to store the values in the segment tree, 
  and it allows the query() function to use SIMD instructions to operate on multiple values simultaneously.
  
  The typedef keyword is used to define a new type called v8u that is based on the existing unsigned int type. 
  The __attribute__((vector_size(32))) part is a compiler hint that tells the compiler to treat objects of type v8u as vectors of 8 unsigned integers, 
  with a total size of 32 bytes. This allows the compiler to generate SIMD instructions for operations on v8u objects.

  The v8u type is used throughout the segment_tree_simd class, 
  and it allows the class to use SIMD instructions to perform operations on multiple values simultaneously. 
  This can improve performance by taking advantage of the parallelism available in modern CPUs.

  Overall, v8u is a type that represents a vector of 8 unsigned integers, 
  and it is used in the segment_tree_simd class to allow the use of SIMD instructions in the query() function.
*/
