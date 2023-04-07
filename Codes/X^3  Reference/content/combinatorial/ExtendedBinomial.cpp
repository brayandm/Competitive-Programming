// Solve sum 0 <= i <= n comb(n, i) * x^n * i^k
// if x = mod-1 then when N > K the ans is always 0 
// otherwise just try bruteforce
ll extended_binomial(ll n, ll x, int k) {
    //x != (MOD-1)
    x = mod(x);
    if(x == 0 && k == 0)return 1;
    x = (inv(x)+1ll)%MOD;
    ll val = inv(x), res = 0, pw = 1;
    for(int i = 0 ; i <= k ; i++) {
        res = (res + stirling2_dp(k,i)*pw)%MOD;
        pw = (pw*(n-i)%MOD)*val%MOD;
    }
    res = res*qpow(x*inv((x+MOD-1)%MOD)%MOD,n)%MOD;
    return res;
}
