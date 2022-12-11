#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
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
void solve(){
    int n;
    cin>>n;
    LCA<20> lca(n);
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        --u;--v;
        lca.addedge(u, v);
    }
    lca.computeLCA(0);
    vector<int> d(n);
    {
        auto& g = lca.adj;
        auto dfs = [&](int u, int par, auto&& self) -> void {
            for(auto &v : g[u]){
                if(v == par) continue;
                d[v] = d[u] + 1;
                self(v, u, self);
            }
        };
        dfs(0, 0, dfs);
    }
    auto dist__ = [&](int x, int y){
        return d[x] + d[y] - 2 * d[lca.getLCA(x, y)];
    };
    int max_dep = *max_element(d.begin(), d.end());
    vector<int> fin(n + 1, max_dep);
    for(int u=0;u<n;u++){
        vector<int> dist(n);
        for(int i=0;i<n;i++) dist[i] = dist__(u, i);
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int x,int y){
            return d[x] - dist[x] > d[y] - dist[y];
        });
        vector<int> smax(n + 1);
        for(int i=n-1;i>=0;--i) smax[i] = max(d[ord[i]], smax[i+1]);
        auto it = ord.begin();
        int lmax = 0;
        for(int x=n;x>=1;--x){
            while(it != ord.end() && d[*it] - dist[*it] > x){
                lmax = max(lmax, dist[*it]);
                ++it;
            }
            int lhs = smax[it - ord.begin()];
            int rhs = lmax + x;
            fin[x] = min(fin[x], max(lhs, rhs));
        }
    }
    for(int i=1;i<=n;i++) cout<<fin[i]<<" ";
    cout<<"\n";
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin>>t;
    while(t--){
        solve();
    }
}
