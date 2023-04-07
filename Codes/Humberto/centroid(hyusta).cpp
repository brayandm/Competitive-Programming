/**  Centroid Descomposition of a given tree (or forest).
     The graph must be 1-indexed, vertex 0 will be an imaginary root.
     Author: humbertoyusta
     Tested: Codeforces Ciel the Commander https://codeforces.com/problemset/problem/321/C */
typedef vector<vector<int>> graph;
struct centroid{
    graph G, T;
    vector<int> subt;
    vector<bool> mk;
    int size_subt, n, root;

    centroid(graph _G) {
        G = _G; n = G.size();
        subt.resize(n); mk.resize(n); T.resize(n);
        for(int i=1; i<n; i++)
            if( !mk[i] )
                build_centroid(i,0);
    }

    void dfs_prec(int u,int p){
        subt[u] = 1;
        for( auto v : G[u] )
            if( !mk[v] && v != p ){
                dfs_prec(v,u);
                subt[u] += subt[v];
            }
    }

    int find_centroid(int u,int p){
        for( auto v : G[u] )
            if( !mk[v] && subt[v] > size_subt / 2 && v != p )
                return find_centroid(v,u);
        return u;
    }

    void build_centroid(int nod,int p){
        dfs_prec(nod,nod);
        size_subt = subt[nod];
        int centroid = find_centroid(nod,nod);
        T[p].push_back(centroid);
        mk[centroid] = 1;
        for( auto u : G[centroid] ){
            if( !mk[u] ){
                build_centroid(u,centroid);
            }
        }
    }
};
