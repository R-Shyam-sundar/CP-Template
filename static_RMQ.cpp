template<typename T, int lgn>
struct static_RMQ{
    int n;
    array<vector<T>, lgn> spt;
    static constexpr int B = 60;
    vector<ll> msk;
    vector<T> a;
    static constexpr T INF = numeric_limits<T>::max();
    static_RMQ() {}
    static_RMQ(vector<T> _a) : n(_a.size()), msk(_a.size()), a(_a){
        build();
    }
    void set_array(vector<T> _a){
        a = _a;
        n = a.size();
        msk.assign(a.size(), 0);
        build();
    }
    void build(){
        for(int i=0;i<lgn;i++) spt[i] = vector<int>(n / B + 1, n);
        a.push_back(INF);
        for(int i=0;i*B<n;i++){
            vector<int> stk;
            msk[i*B] = 1;
            stk.push_back(i*B);
            for(int j=i*B+1;j<min(n, (i+1)*B);j++){
                msk[j] = msk[j-1];
                msk[j] |= (1ll<<(j - i*B));
                while(stk.size() > 0 && a[stk.back()] >= a[j]){
                    msk[j] ^= (1ll<<(stk.back() - i*B));
                    stk.pop_back();
                }
                stk.push_back(j);
            }
            spt[0][i] = stk[0];
        }
        for(int lg=0;lg+1<lgn;lg++){
            for(int j=0;j<spt[lg].size();j++){
                if(j + (1<<lg) < spt[lg].size()){
                    spt[lg+1][j] = a[spt[lg][j]] < a[spt[lg][j+(1<<lg)]] ? spt[lg][j] : spt[lg][j+(1<<lg)];
                }
                else{
                    spt[lg+1][j] = spt[lg][j];
                }
            }
        }
    }
    int spt_query(int l, int r){
        if(l > r) return n;
        ++r;
        int len = r - l;
        int lg = 31 - __builtin_clz(len);
        return a[spt[lg][l]] < a[spt[lg][r-(1<<lg)]] ? spt[lg][l] : spt[lg][r-(1<<lg)];
    }
    int small_query(int l, int r){
        assert(l / B == r / B);
        return l - l % B + __builtin_ctzll(msk[r] & ~((1ll<<(l % B)) - 1));
    }
    int query(int l, int r){
        if(l / B == r / B) return small_query(l, r);
        int mid = spt_query(l / B + 1, r / B - 1);
        int lft = small_query(l, (l / B * B) + B - 1);
        int rht = small_query(r / B * B, r);
        if(a[mid] < a[lft] && a[mid] < a[rht]) return mid;
        if(a[lft] < a[rht]) return lft;
        else return rht;
    }
};

/*
  Block Decomposition
*/
