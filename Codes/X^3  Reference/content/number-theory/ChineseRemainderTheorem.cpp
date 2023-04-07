bool crt(ll k1, ll m1, ll k2, ll m2, ll &k, ll &m) {
    k1 %= m1;
    if (k1 < 0) k1 += m1;
    k2 %= m2;
    if (k2 < 0) k2 += m2;
    ll x, y, g;
    if (!find_any_solution(m1, -m2, k2 - k1, x, y, g)) {
        return false;
    }
    ll dx = m2 / g;
    ll delta = x / dx - (x % dx < 0);
    k = m1 * (x - dx * delta) + k1;
    m = m1 / g * m2;
    assert(0 <= k && k < m);
    return true;
}
long long chinese_remainder(vector<int> rem, vector<int> mod) {
    long long ans = rem[0],m = mod[0]; int n = rem.size();
    for(int i=1; i<n; ++i) {
        int a = modular_inverse(m,mod[i]);
        int b = modular_inverse(mod[i],m);
        ans = (ans*b*mod[i]+rem[i]*a*m)%(m*mod[i]);
        m *= mod[i];
    }
    return ans;
}