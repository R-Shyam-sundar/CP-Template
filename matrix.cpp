template<int n, int m>
struct matrix{
    array<array<ll, m>, n> mat;
    matrix(){
        for(int i=0;i<n;i++) for(int j=0;j<m;j++) mat[i][j] = 0;
    }
    matrix operator*=(matrix<m, m> a){
        matrix<m, m> ans;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                for(int k=0;k<m;k++){
                    ans[i][j] += mat[i][k] * a[k][j];
                    ans[i][j] %= p;
                }
            }
        }
        return *this = ans;
    }
    matrix operator+=(matrix a){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                mat[i][j] += a[i][j];
                if(mat[i][j] >= p) mat[i][j] -= p;
            }
        }
        return *this;
    }
    matrix operator-=(matrix a){
        assert(mat.size() == a.size());
        assert(mat[0].size() == a.size());
        for(int i=0;i<mat.size();i++){
            for(int j=0;j<mat[0].size();j++){
                mat[i][j] -= a[i][j];
                if(mat[i][j] < 0) mat[i][j] += p;
            }
        }
        return *this;
    }
    matrix operator+(matrix a){return matrix(*this) += a;}
    matrix operator-(matrix a){return matrix(*this) -= a;}
    template<int l>
    matrix<n, l> operator*(matrix<m, l> a){
        matrix<n, l> ans;
        for(int i=0;i<n;i++){
            for(int j=0;j<l;j++){
                for(int k=0;k<m;k++){
                    ans[i][j] += mat[i][k] * a[k][j];
                    ans[i][j] %= p;
                }
            }
        }
        return ans;
    }
    matrix pow(int pw){
        assert(n == m);
        matrix ans = matrix::identity();
        matrix base = *this;
        while(pw){
            if(pw & 1){
                ans *= base;
            }
            base *= base;
            pw >>= 1;
        }
        return ans;
    }
    int size(){
        return mat.size();
    }
    array<ll, m>& operator[](int x){
        return mat[x];
    }
    static matrix identity(){
        matrix ans;
        for(int i=0;i<n;i++){
            ans[i][i] = 1;
        }
        return ans;
    }
};

matrix<n, m> mat;
