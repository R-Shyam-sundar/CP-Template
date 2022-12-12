template<int mod,int... mods>
struct StringHash<mod, mods...>{
    StringHash(){}
    int modpow(ll x,ll p){
        ll ans = 1;
        while(p){
            if(p&1) ans*=x, ans%=mod;
            x*=x;
            x%=mod;
            p>>=1; 
        }
        return int(ans);
    }
    vector<int> hashvalues;
    vector<int> pows;
    vector<int> invpows;
    StringHash<mods...> ohash;
    const int AL = 26;
    StringHash(const string &s) : ohash(s){
        int n = s.size();
        hashvalues.resize(n+1);
        pows.resize(n+1);
        invpows.resize(n+1);
        pows[0] = 1;
        for(int i=1;i<=n;i++){
            pows[i] = ll(AL + 1) * pows[i-1] % mod;
        }
        invpows[n] = modpow(pows[n], mod-2);
        for(int i=n-1;i>=0;--i){
            invpows[i] = ll(AL + 1) * invpows[i+1] % mod;
        }
        for(int i=1;i<=n;i++){
            hashvalues[i] = (ll(AL + 1) * hashvalues[i-1] + (s[i-1] - 'a' + 1)) % mod;
        }
    }
    int hashval(int l1,int r1){ // 0 indexed
        ll ans = hashvalues[r1+1] - ll(hashvalues[l1]) * pows[r1-l1+1];
        ans%=mod;
        return ans >= 0 ? ans : ans+mod;
    }
    bool compare(int l1,int r1, int l2,int r2){
        return hashval(l1,r1) == hashval(l2, r2) && ohash.compare(l1,r1,l2,r2);
    }
};

/*
  Source file:  https://codeforces.com/contest/1657/submission/150499423
*/
