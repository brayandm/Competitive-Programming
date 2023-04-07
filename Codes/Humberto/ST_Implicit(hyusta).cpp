template <typename Tnode,typename Tlazy>
struct ST{
    vector<Tnode> st;
    vector<Tlazy> lazy;
    vector<int> lft, rgt;
    int sz, limit;
    Tlazy neutraL;
    Tnode neutraN;

    void nwn(){
        st.pb(neutraN);
        lazy.pb(neutraL);
        lft.pb(-1);
        rgt.pb(-1);
        sz++;
    }

    ST(int _limit,Tnode _neutraN, Tlazy _neutraL){
        sz = 0;
        limit = _limit;
        neutraN = _neutraN;
        neutraL = _neutraL;
        nwn();
    }

    Tnode merge_(Tnode a, Tnode b){
        Tnode c;
        /// Merge nodes a and b into c

        return c;
    }

    void push(int nod,int l,int r){
        /// how lazy[nod] affects st[nod]

        if( l != r && lazy[nod] != neutraL ){
            if( lft[nod] == -1 ){ lft[nod] = sz; nwn(); }
            if( rgt[nod] == -1 ){ rgt[nod] = sz; nwn(); }
            /// how lazy[nod] affects lazy[l[nod]] and lazy[r[nod]]

        }
        lazy[nod] = neutraL;
    }

    void update(int x,int y,Tlazy v){ update(0,0,limit-1,x,y,v); }

    void update(int nod,int l,int r,int x,int y,Tlazy v){

        push(nod,l,r);

        if( l >= x && r <= y ){
            lazy[nod] = v;
            push(nod,l,r);
            return;
        }

        int mi = ( l + r ) >> 1;

        if( x <= mi ){
            if( lft[nod] == -1 ){ lft[nod] = sz; nwn(); }
            update(lft[nod],l,mi,x,y,v);
        }
        else{
            if( lft[nod] != -1 )
                push(lft[nod],l,mi);
        }

        if( y > mi ){
            if( rgt[nod] == -1 ){ rgt[nod] = sz; nwn(); }
            update(rgt[nod],mi+1,r,x,y,v);
        }
        else{
            if( rgt[nod] != -1 )
                push(rgt[nod],mi+1,r);
        }

        if( rgt[nod] == -1 ){ st[nod] = st[lft[nod]]; return; }

        if( lft[nod] == -1 ){ st[nod] = st[rgt[nod]]; return; }

        st[nod] = merge_( st[lft[nod]] , st[rgt[nod]] );
    }

    Tnode query(int l,int r){ return query(0,0,limit-1,l,r); }

    Tnode query(int nod,int l,int r,int x,int y){

        push(nod,l,r);

        if( l >= x && r <= y ){ return st[nod]; }

        int mi = ( l + r ) >> 1;

        Tnode ret = neutraN;

        if( ( x <= mi ) && ( lft[nod] != -1 ) ) ret = merge_( ret , query(lft[nod],l,mi,x,y) );

        if( ( y > mi ) && ( rgt[nod] != -1 ) ) ret = merge_( ret , query(rgt[nod],mi+1,r,x,y) );

        return ret;
    }
};
