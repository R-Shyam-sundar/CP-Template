template<typename T>
struct PrimeBasis{
    void reduce_pair(T& x, T& y){
        bool to_swap = 0;
        if(x > y){
            to_swap ^= 1;
            swap(x, y);
        } 
        while(x > 1 && y % x == 0){
            y /= x;
            if(x > y){
                to_swap ^= 1;
                swap(x, y);
            }
        }
        if(to_swap) swap(x, y);
    }
    vector<T> basis;
    void solve_inner(int pos, T &val){
        while(basis[pos] % val == 0) basis[pos] /= val;
        vector<T> curr_basis = {basis[pos], val};
        int c_ptr = 1;
        while(c_ptr < curr_basis.size()){
            for(int i=0;i<c_ptr;i++){
                reduce_pair(curr_basis[i], curr_basis[c_ptr]);
                if(curr_basis[c_ptr] == 1) break;
                if(curr_basis[i] == 1) continue;
                T g = gcd(curr_basis[c_ptr], curr_basis[i]);
                if(g > 1){
                    curr_basis[c_ptr] /= g;
                    curr_basis[i] /= g;
                    curr_basis.push_back(g);
                }
            }
            ++c_ptr;
        }
        basis[pos] = curr_basis[0];
        val = curr_basis[1];
        for(int i=2;i<curr_basis.size();i++) if(curr_basis[i] > 1) basis.push_back(curr_basis[i]);
        if(basis[pos] == 1){
            swap(basis[pos], basis.back());
            basis.pop_back();
        }
    }
    void add_element(T val){
        for(int i=0;i<basis.size();i++){
            reduce_pair(val, basis[i]);
            if(basis[i] == 1){
                swap(basis[i], basis.back());
                basis.pop_back();
                continue;
            }
            if(val == 1) return;
            if(gcd(basis[i], val) > 1) solve_inner(i, val);
        }
        if(val > 1) basis.push_back(val);
    }
    void verify_basis(){
        for(int i=0;i<basis.size();i++){
            for(int j=i+1;j<basis.size();j++){
                assert(gcd(basis[i], basis[j]) == 1);
            }
        }
    }
    void verify_element(T ele){
        for(auto &x : basis){
            while(ele % x == 0) ele /= x;
        }
        assert(ele == 1);
    }
    auto factorisation(T ele){
        vector<int> factors(basis.size());
        for(int i=0;i<basis.size();i++){
            while(ele % basis[i] == 0){
                factors[i]++;
                ele /= basis[i];
            }
        }
        return factors;
    }
};

int main() {
    // read input
    int n;
    ll p;
    cin >> n >> p;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // initialize the prime basis
    PrimeBasis<ll> pb;
    pb.add_element(p);

    // check if each number is divisible by p
    for (int i = 0; i < n; ++i) {
        cout << (pb.verify_element(a[i]) ? "YES" : "NO") << endl;
    }

    return 0;
}


/*
  Source code:  https://codeforces.com/contest/1656/submission/159590539
*/

/*
  Prime Basis:
  The PrimeBasis class can be useful in competitive programming for solving problems 
  that involve working with large prime numbers or numbers that can be represented as products of primes. 
  For example, it could be used to implement an efficient algorithm for finding the prime factorization of a large number, 
  or for checking if a number is divisible by a specific set of prime numbers. 
  It could also be useful for implementing efficient algorithms for modular arithmetic, 
  where the modulus is a product of prime numbers.
  
  Problem: Given a list of prime numbers and a list of numbers, 
           determine which of the numbers are divisible by the primes in the list.

  Input: The first line of the input contains an integer n and a prime number p, 
         where 1 <= n <= 10^6 and 2 <= p <= 10^9. 
         The next n lines each contain a number a_i where 1 <= a_i <= 10^9.

  Output: For each number a_i in the input, 
          output "YES" if a_i is divisible by p, and "NO" otherwise.
*/

/*
  Usage:
  
  
*/
