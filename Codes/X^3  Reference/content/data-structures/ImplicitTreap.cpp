struct Node {
    int prio, sz;
    Node *l, *r;
    ll val, sum;
    ll lazy;
    Node (ll _val) : l(NULL), r(NULL), sz(1),
        prio(rng()), val(_val), lazy(0), sum(_val) {}
};
struct Treap {
    inline int size(Node *u) { return u ? u->sz : 0; }
    inline void push(Node *u) {
        if (u && u->lazy) {
            // How u->lazy affects u
            u->val += u->lazy;
            u->sum += u->lazy * u->sz;
            if (u->l) u->l->lazy += u->lazy;
            if (u->r) u->r->lazy += u->lazy;
            u->lazy = 0;
        }
    }
    Node* update(Node *u){
        // Recompute u based on merging its children
        u->sum = u->val, u->sz = 1;
        if (u->l) u->sum += u->l->sum, u->sz += u->l->sz;
        if (u->r) u->sum += u->r->sum, u->sz += u->r->sz;
        return u;
    }
    pair<Node*, Node*> split(Node* u, int k){
        if (!u) return { u, u };
        push(u);
        if (size(u->l) >= k){
            auto s = split(u->l, k);
            u->l = s.second;
            return { s.first, update(u) };
        }
        auto s = split(u->r, k - size(u->l) - 1);
        u->r = s.first;
        return { update(u), s.second };
    }
    Node* merge(Node *u, Node *v){
        if (!u || !v) return u ? u : v;
        if (u->prio > v->prio){
            push(u);
            u->r = merge(u->r, v);
            return update(u);
        }
        push(v);
        v->l = merge(u, v->l);
        return update(v);
    }
    Node* kth(Node *u, int k) {
        while (u && size(u->l) + 1 != k){
            push(u);
            if (size(u->l) >= k) u = u->l;
            else k -= size(u->l) + 1, u = u->r;
        }
        push(u);
        return u;
    }
};
