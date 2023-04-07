//Count permutations with at least K fixed points:
//comb(n,k)*(n-k)! * f(k,k) +
//comb(n,k+1)*(n-(k+1))! * f(k+1,k) +
//comb(n,k+1)*(n-(k+2))! * f(k+2,k) ...
ll intersection_value(ll N, ll K) {
    if(N < K)return 0;
    if(K == 0) {
        if(N == 0)return 1;
        return 0;
    }
    if((N-K)&1)return mod(-comb(N-1,K-1));
    return comb(N-1,K-1);
}