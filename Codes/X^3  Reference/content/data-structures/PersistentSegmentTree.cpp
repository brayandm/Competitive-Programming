typedef int T;
struct node{
    int l, r;T v;
    node () {}
};
vector<node> pool; int actual;
int next() {
    pool.push_back(node());
    return actual ++;
}
struct pst {
    vector<int> versions; int n;
    pst(vector<T> &a) : n(a.size()) {
        versions.push_back(build(0, n - 1, a));
    }
    T merge(T v1, T v2) { /*Merge v1 and v2*/ }
    void up(int p, T v) { /*How v affects pool[p].v*/ }
    int build(int l, int r, vector<T> &a){
        int ans = next();
        if (l == r){
            pool[ans].v = a[l];
            return ans;
        }
        int mid = (l + r) >> 1;
        pool[ans].l = build(l, mid, a);
        pool[ans].r = build(mid + 1, r, a);
        pool[ans].v = merge(pool[pool[ans].l].v, pool[pool[ans].r].v);
        return ans;
    }
    int clone(int p){
        int ans = next();
        pool[ans] = pool[p];
        return ans;
    }
    void update(int ver, int pos, T v) {
        versions.push_back(update(versions[ver], 0, n - 1, pos, v));
    }
    void update(int pos, T v) {
        versions.push_back(update(versions.back(), 0, n - 1, pos, v));
    }
    int update(int p, int l, int r, int pos, T v){
        p = clone(p);
        if (r == l){
            up(p, v);
            return p;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) pool[p].l = update(pool[p].l, l, mid, pos, v);
        else pool[p].r = update(pool[p].r, mid + 1, r, pos, v);
        pool[p].v = merge(pool[pool[p].l].v, pool[pool[p].r].v);
        return p;
    }
    T query(int t, int l, int r) {
        return query(versions[t], 0, n - 1, l, r);
    }
    T query(int p, int l, int r, int L, int R){
        if (L <= l && r <= R) return pool[p].v;
        int mid = (l + r) >> 1;
        if (R <= mid) return query(pool[p].l, l, mid, L, R);
        if (L > mid) return query(pool[p].r, mid + 1, r, L, R);
        return merge(query(pool[p].l, l, mid, L, R),
                     query(pool[p].r, mid + 1, r, L, R));
    }
};