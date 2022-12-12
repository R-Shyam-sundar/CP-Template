template<typename T>
struct node{
    T val;
    node<T>* left = NULL;
    node<T>* right = NULL;
};
template<typename T>
struct persistent_segment_tree{
    function<T(const T&,const T&)> join;
    int n;
    T base;
    vector<node<T>*> roots;
    persistent_segment_tree(int _n, function<T(const T&,const T&)> join, T base) : n(_n), join(join), base(base){
        n = 32 - __builtin_clz(n-1);
        n = (1<<n);
        roots.push_back(build(0,n));
    }
    persistent_segment_tree(vector<T> v, function<T(const T&,const T&)> join, T base) : n(v.size()), join(join), base(base){
        n = 32 - __builtin_clz(n-1);
        n = (1<<n);
        roots.push_back(build(0,n,v));
    }
    node<T>* build(int l,int r){
        node<T> *root = new node<T>;
        if(l+1==r){
            root->val = base;
            return root;
        } 
        root->left = build(l,(l+r)/2);
        root->right = build((l+r)/2, r);
        root->val = join(root->left->val, root->right->val);
        return root;
    }
    node<T>* build(int l,int r, vector<T> &v){
        node<T> *root = new node<T>;
        if(l+1==r){
            root->val = l < v.size() ? v[l] : base;
            return root;
        } 
        root->left = build(l,(l+r)/2, v);
        root->right = build((l+r)/2, r, v);
        root->val = join(root->left->val, root->right->val);
        return root;
    }
    void set(int pos, T val){
        node<T>* currnew = new node<T>;
        node<T>* currold = roots.back();
        set(0, n, currnew, currold, pos, val);
        roots.push_back(currnew);
    }
    void set(int l,int r, node<T>* currnew, node<T>* currold, int pos, T val){
        if(l+1==r){
            currnew->val = val;
            return;
        }
        if(pos<(l+r)/2){
            currnew->right = currold->right;
            currnew->left = new node<T>;
            set(l,(l+r)/2, currnew->left, currold->left, pos, val);
            currnew->val = join(currnew->left->val, currnew->right->val);
        }
        else{
            currnew->left = currold->left;
            currnew->right = new node<T>;
            set((l+r)/2, r, currnew->right, currold->right, pos, val);
            currnew->val = join(currnew->left->val, currnew->right->val);
        }
    }
    void increment(int pos, T val){
        node<T>* currnew = new node<T>;
        node<T>* currold = roots.back();
        increment(0,n, currnew, currold, pos, val);
        roots.push_back(currnew);
    }
    void increment(int l,int r, node<T>* currnew, node<T>* currold, int pos, T val){
        if(l+1==r){
            currnew->val = join(currold->val, val);
            return;
        }
        if(pos<(l+r)/2){
            currnew->right = currold->right;
            currnew->left = new node<T>;
            increment(l,(l+r)/2, currnew->left, currold->left, pos, val);
            currnew->val = join(currnew->left->val, currnew->right->val);
        }
        else{
            currnew->left = currold->left;
            currnew->right = new node<T>;
            increment((l+r)/2, r, currnew->right, currold->right, pos, val);
            currnew->val = join(currnew->left->val, currnew->right->val);
        }
    }
    T query(int l,int r,int time){
        if(l > r) return base;
        return query(0,n,l,r+1,roots[time]);
    }
    T query(int l,int r,int ql, int qr, node<T>* curr){
        if(l>=qr || r<=ql){
            return base;
        }
        if(l>=ql && r<=qr){
            return curr->val;
        }
        return join(query(l,(l+r)/2, ql, qr, curr->left), query((l+r)/2, r, ql, qr, curr->right));
    }
    pair<int, T> search(function<bool(T)> cmp, int t, int maxr){
        node<T>* curr = roots[t];
        int r = n;
        T currv = base;
        int ans = 0;
        while(curr->left != NULL){
            r >>= 1;
            if(ans + r <= maxr && !cmp(join(currv, curr->left->val))){
                currv = join(currv, curr->left->val);
                curr = curr->right;
                ans += r;
            }
            else{
                curr = curr->left;
            }
        }
        currv = join(currv, curr->val);
        if(!cmp(currv)) ans++;
        return {ans, currv};
    }
};

/*
  Source file:  https://codeforces.com/contest/1651/submission/149198871
*/

