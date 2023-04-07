template <typename Tnode,typename Tlazy>
struct ST{
    vector<Tnode> st;
    vector<Tlazy> lazy;
    int sz;
    Tlazy neutraL;

    ST(int n,Tlazy _neutraL){
        sz = n;
        st.resize(4*n);
        lazy.resize(4*n);
        neutraL = _neutraL;
    }

    Tnode merge_(Tnode a, Tnode b){
        Tnode c;
        /// Merge nodes a and b into c
        return c;
    }

    void push(int nod,int l,int r){
        /// how lazy[nod] affects st[nod]
        if( l != r ){
            /// how lazy[nod] affects lazy[2*nod] and lazy[2*nod+1]
        }
        lazy[nod] = neutraL;
    }

    void build(Tnode *arr){ build(1,0,sz-1,arr); }

    void build(int nod,int l,int r,Tnode *arr){
        if( l == r ){
            st[nod] = arr[l];
            lazy[nod] = neutraL;
            return;
        }
        int mi = ( l + r ) >> 1;
            build((nod<<1),l,mi,arr);
            build((nod<<1)+1,mi+1,r,arr);
        st[nod] = merge_( st[(nod<<1)] , st[(nod<<1)+1] );
        lazy[nod] = neutraL;
    }

    void build(vector<Tnode> &arr){ build(1,0,sz-1,arr); }

    void build(int nod,int l,int r,vector<Tnode> &arr){
        if( l == r ){
            st[nod] = arr[l];
            lazy[nod] = neutraL;
            return;
        }
        int mi = ( l + r ) >> 1;
            build((nod<<1),l,mi,arr);
            build((nod<<1)+1,mi+1,r,arr);
        st[nod] = merge_( st[(nod<<1)] , st[(nod<<1)+1] );
        lazy[nod] = neutraL;
    }

    void update(int x,int y,Tlazy v){ update(1,0,sz-1,x,y,v); }

    void update(int nod,int l,int r,int x,int y,Tlazy v){

        push(nod,l,r);

        if( l >= x && r <= y ){
            lazy[nod] = v;
            push(nod,l,r);
            return;
        }

        int mi = ( l + r ) >> 1;

        if( x <= mi ) update((nod<<1),l,mi,x,y,v);
            else push(nod<<1,l,mi);
        if( y > mi ) update((nod<<1)+1,mi+1,r,x,y,v);
            else push((nod<<1)+1,mi+1,r);

        st[nod] = merge_( st[(nod<<1)] , st[(nod<<1)+1] );
    }

    Tnode query(int l,int r){ return query(1,0,sz-1,l,r); }

    Tnode query(int nod,int l,int r,int x,int y){

        push(nod,l,r);

        if( l >= x && r <= y ) return st[nod];

        int mi = ( l + r ) >> 1;

        if( y <= mi ) return query((nod<<1),l,mi,x,y);

        if( x > mi ) return query((nod<<1)+1,mi+1,r,x,y);

        return merge_( query((nod<<1),l,mi,x,y), query((nod<<1)+1,mi+1,r,x,y) );
    }
};
