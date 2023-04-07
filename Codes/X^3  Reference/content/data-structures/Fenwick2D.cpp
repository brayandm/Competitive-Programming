//Complexity (O(nlog^2)) first call fakeUpdate, prepare, and
//then start with real updates and queries. Computes sums
//a[i,j] for all i<I, j<J, and increases single elements a[i,j]
struct FT {
    vector<ll> ft;
    FT () {}
    FT(int n) : ft(n + 1) {}
    void update(int id, ll val){
        for (id ++; id < ft.size(); id += (id&-id)) ft[id] += val;
    }
    ll query(int id) { if (id < 0) return 0;
        ll res = 0;
        for (id ++; id > 0; id -= (id&-id))
            res += ft[id];
        return res; }
};
struct FT2D {
    vector<FT> fts; vector<vector<int>> ys; int szx;
    FT2D (int _szx) : szx(_szx + 1), ys(_szx + 1), fts(_szx + 1) {}
    void fakeUpdate(int x,int y) {
        for (x ++; x < szx; x += (x&-x))
            ys[x].push_back(y);
    }
    int index(int x,int y) {
        return lower_bound(ys[x].begin(), ys[x].end(), y) - ys[x].begin();
    }
    int index2(int x,int y) {
        return upper_bound(ys[x].begin(), ys[x].end(), y) - ys[x].begin();
    }
    void prepare () { int count = 0;
        for (auto& vy : ys) {
            sort(vy.begin(), vy.end());
            fts[count++].ft.resize(vy.size() + 2);
        }
    }
    void update (int x,int y, ll val) {
        for (x ++; x < szx; x += (x&-x))
            fts[x].update(index(x, y), val);
    }
    ll query(int x,int y) { ll res = 0;
        for (x ++; x > 0; x -= (x&-x))
            res += fts[x].query(index2(x, y) - 1);
        return res;
    }
};