template <typename Tnode,typename Tup>
struct ST{
    vector<Tnode> st;
    int sz;

    ST(int n){
        sz = n;
        st.resize(4*n);
    }

    Tnode merge_(Tnode a, Tnode b){
        Tnode c;
        /// Merge a and b into c
        return c;
    }

    void update_node(int nod,Tup v){
        /// how v affects to st[nod]
    }

    void build(vector<Tnode> &arr){ build(1,0,sz-1,arr); }

    void build(int nod,int l,int r,vector<Tnode> &arr){
        if( l == r ){
            st[nod] = arr[l];
            return;
        }
        int mi = ( l + r ) >> 1;
            build((nod<<1),l,mi,arr);
            build((nod<<1)+1,mi+1,r,arr);
        st[nod] = merge_( st[(nod<<1)] , st[(nod<<1)+1] );
    }

    void update(int id,Tup v){ update(1,0,sz-1,id,v); }

    void update(int nod,int l,int r,int id,Tup v){
        if( l == r ){
            update_node(nod,v);
            return;
        }
        int mi = ( l + r ) >> 1;
        if( id <= mi ) update((nod<<1),l,mi,id,v);
            else update((nod<<1)+1,mi+1,r,id,v);
        st[nod] = merge_( st[(nod<<1)] , st[(nod<<1)+1] );
    }

    Tnode query(int l,int r){ return query(1,0,sz-1,l,r); }

    Tnode query(int nod,int l,int r,int x,int y){

        if( l >= x && r <= y ) return st[nod];

        int mi = ( l + r ) >> 1;

        if( y <= mi ) return query((nod<<1),l,mi,x,y);

        if( x > mi ) return query((nod<<1)+1,mi+1,r,x,y);

        return merge_( query((nod<<1),l,mi,x,y), query((nod<<1)+1,mi+1,r,x,y) );
    }
};

/// Static build


    void build(Tnode *arr){ build(1,0,sz-1,arr); }

    void build(int nod,int l,int r,Tnode *arr){
        if( l == r ){
            st[nod] = arr[l];
            return;
        }
        int mi = ( l + r ) >> 1;
            build((nod<<1),l,mi,arr);
            build((nod<<1)+1,mi+1,r,arr);
        st[nod] = merge_( st[(nod<<1)] , st[(nod<<1)+1] );
    }
