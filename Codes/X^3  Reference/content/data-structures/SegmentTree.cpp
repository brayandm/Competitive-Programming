//Must implement merge_ function and push
//For use without lazy, remove stuff that contains if-lazy
template <typename Tnode,typename Tlazy>
struct ST{
    vector<Tnode> st; int sz;
    vector<Tlazy> lazy; Tlazy neutraL; // if-lazy
    ST (int n,Tlazy _neutraL) : sz(n), st(2*n),
                                lazy(2*n), neutraL(_neutraL) {} // if-lazy
    Tnode merge_(Tnode a, Tnode b) {}
    void push (int nod,int l,int r){ /** IF-LAZY */
        int mi = (l + r) >> 1;
        /// how lazy[nod] affects st[nod]
        if( l != r ){
            /// how lazy[nod] affects lazy[nod+1] and lazy[nod+2*(mi-l+1)]
        }
        lazy[nod] = neutraL;
    }
    void build (vector<Tnode> &arr){build(0, 0, sz-1, arr);}
    void build (int nod,int l,int r,vector<Tnode> &arr){
        if (l == r) {
            st[nod] = arr[l];
            lazy[nod] = neutraL; // if-lazy
            return;
        }
        int mi = (l + r) >> 1;
        build(nod+1,l,mi,arr);
        build(nod+((mi-l+1)<<1), mi+1, r, arr);
        st[nod] = merge_(st[nod+1], st[nod+((mi-l+1)<<1)]);
        lazy[nod] = neutraL; // if-lazy
    }
    void updateRange (int x,int y,Tlazy v) { /** IF-LAZY */
        updateRange(0, 0, sz-1, x, y, v);
    }
    void updateRange (int nod,int l,int r,int x,int y,Tlazy v){
        push(nod, l, r);
        if (l >= x && r <= y) {
            lazy[nod] = v;
            push(nod, l, r); return;
        }
        int mi = (l + r) >> 1;
        if (x <= mi) updateRange(nod+1, l, mi, x, y, v);
        else push(nod+1, l, mi);
        if (y > mi) updateRange(nod+((mi-l+1)<<1), mi+1, r, x, y, v);
        else push(nod+((mi-l+1)<<1), mi+1, r);
        st[nod] = merge_(st[nod+1] , st[nod+((mi-l+1)<<1)]);
    }
    void updatePoint(int id, Tnode val) {
        updatePoint(0, 0, sz - 1, id, val);
    }
    void updatePoint(int nod,int l,int r,int id, Tnode val) {
        push(nod, l, r); // if-lazy
        if (l == r) {
            st[nod] = val; return;
        }
        int mi = (l + r) >> 1;
        if (id <= mi) {
            updatePoint(nod+1, l, mi, id, val);
            push(nod+((mi-l+1)<<1), mi+1, r); // if-lazy
        } else {
            updatePoint(nod+((mi-l+1)<<1), mi+1, r, id, val);
            push(nod+1, l, mi); // if-lazy
        }
        st[nod] = merge_(st[nod+1], st[nod+((mi-l+1)<<1)]);
    }
    Tnode query (int l,int r) {return query(0, 0, sz-1, l, r);}
    Tnode query (int nod,int l,int r,int x,int y) {
        push(nod, l, r); // if-lazy
        if (l >= x && r <= y) return st[nod];
        int mi = (l + r) >> 1;
        if (y <= mi) return query(nod+1, l, mi, x, y);
        if (x > mi) return query(nod+((mi-l+1)<<1), mi+1, r, x, y);
        return merge_(query(nod+1, l, mi, x, y),
                      query(nod+((mi-l+1)<<1), mi+1, r, x, y));
    }
};