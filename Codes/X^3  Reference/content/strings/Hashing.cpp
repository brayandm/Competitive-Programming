// Hashing mod 2^64-1 (Approved by kactl and errichto and tested)
// Use using H = unsigned long long; instead of H for mod 2^64
// Two hashes modulo primes below
// Use .get() instead of actual values to get the hashes
typedef unsigned long long ull;
struct H {
    ull x; H(ull x = 0) : x(x) {}
    H operator +(H o) { return x + o.x + (x + o.x < x); }
    H operator -(H o) { return *this + ~o.x; }
    H operator *(H o) { auto m = (__uint128_t)x * o.x;
        return H((ull)m) + (ull)(m >> 64); }
    ull get() const { return x + !~x; }
    bool operator ==(H o) const { return get() == o.get(); }
    bool operator <(H o) const { return get() < o.get(); }
};
static const H BASE = (ll)1e11+3; // (order ~ 3e9; random also ok)

struct HashInterval {
    vector<H> ha, pw;
    HashInterval(string& str) : ha(str.size()+1), pw(ha) {
        pw[0] = 1;
        for (int i = 0; i < str.size(); i ++) {
            ha[i + 1] = ha[i] * BASE + str[i];
            pw[i + 1] = pw[i] * BASE;
        }
    }
    H hashInterval(int a, int b) { // hash [a, b]
        return ha[b + 1] - ha[a] * pw[b - a + 1];
    }
};
H hashString(string& s){ H h;
    for(char c : s) h = h * BASE + c;
    return h;
}
// struct H for two hashes mod 2 primes
// use ull() to get values of hash in unsigned long long
template<int M, class B>
struct HA {
    int x; B b; HA(int x=0) : x(x), b(x) {}
    HA(int x, B b) : x(x), b(b) {}
    HA operator+(HA o){int y = x+o.x; return{y - (y>=M)*M, b+o.b};}
    HA operator-(HA o){int y = x-o.x; return{y + (y< 0)*M, b-o.b};}
    HA operator*(HA o) { return {(int)(1LL*x*o.x % M), b*o.b}; }
    explicit operator ull() { return x ^ (ull) b << 21; }
    bool operator==(HA o) const { return (ull)*this == (ull)o; }
    bool operator<(HA o) const { return (ull)*this < (ull)o; }
};
typedef HA<1000000007, HA<1000000009, unsigned>> H;
static const H BASE(311, HA<1000000009, unsigned>(20003));