bool isPrime(int x){
    if(x == 2 || x == 3) return true;
    if(x % 2 == 0 || x % 3 == 0){
        return false;
    }
    for(int i=5;i*i<=x;i+=4){
        if(x > i && x % i == 0) return false;
        i += 2;
        if(x > i && x % i == 0) return false;
    }
    return true;
}

/*
  Function to check whether a number is prime number in O(sqrt(n))
*/
