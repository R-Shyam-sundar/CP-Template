template<typename T, int lgn>
struct sparse_table{
    int n;
    array<vector<int>, lgn> bt;
    vector<T> a;
    sparse_table() {}
    sparse_table(vector<T> _a) : n(_a.size()), a(_a){
        build();
    }
    void set_array(vector<T> _a){
        a = _a;
        n = _a.size();
        build();
    }
    void build(){
        for(int i=0;i<lgn;i++) bt[i].assign(n, 0);
        for(int i=0;i<n;i++) bt[0][i] = i;
        for(int lg=0;lg+1<lgn;lg++){
            for(int i=0;i<n;i++){
                if(i + (1<<lg) < n){
                    bt[lg+1][i] = a[bt[lg][i]] < a[bt[lg][i + (1<<lg)]] ? bt[lg][i] : bt[lg][i + (1<<lg)];
                }
            }
        }
    }
    int query(int l,int r){
        ++r;
        int lg = 31 - __builtin_clz(r - l);
        return a[bt[lg][l]] < a[bt[lg][r - (1<<lg)]] ? bt[lg][l] : bt[lg][r - (1<<lg)];
    }
};
