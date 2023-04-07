ll lagrange_interpolation_arithmetic
    (const vector <ll> &y, ll T, ll a = 0, ll d = 1) {
    T = mod(T), a = mod(a), d = mod(d);
    int N = (int) y.size() - 1;
    if (a == 0 && d == 1 && T <= N) return y[T];
    vector <ll> dp(N + 1, 1), pd(N + 1, 1);
    for (int i = 0; i < N; i++)
        dp[i + 1] = dp[i] * (T + MOD - (a + d * i) % MOD) % MOD;
    for (int i = N; i > 0; i--)
        pd[i - 1] = pd[i] * (T + MOD - (a + d * i) % MOD) % MOD;
    vector <ll> fact(N + 1, 1), finv(N + 1, 1);
    for (int i = 1; i <= N; i++)
        fact[i] = fact[i - 1] * d % MOD * i % MOD;
    finv[N] = finv[N] * inv(fact[N]) % MOD;
    for (int i = N; i >= 1; i--)
        finv[i - 1] = finv[i] * d % MOD * i % MOD;
    ll ret = 0;
    for (int i = 0; i <= N; i++) {
        ll tmp = y[i] * dp[i] % MOD * pd[i] % MOD *
                finv[i] % MOD * finv[N - i] % MOD;
        if ((N - i) & 1)ret = (ret + MOD - tmp) % MOD;
        else ret = (ret + tmp) % MOD;
    }
    return ret;
}
ll lagrange_interpolation(vector <pair<ll, ll>> p, ll z) {
    int n = p.size(); ll l, val = 0;
    for (int i = 0; i < n; i++) {
        p[i].first = mod(p[i].first);
        p[i].second = mod(p[i].second);
    }
    z = mod(z);
    for (int i = 0; i < n; i++) {
        l = p[i].second;
        for (int j = 0; j < n; j++)
            if (i != j)
                l = l * (z + MOD - p[j].first) % MOD *
                    inv(p[i].first + MOD - p[j].first) % MOD;
        val = (val + l) % MOD;
    }
    return val;
}