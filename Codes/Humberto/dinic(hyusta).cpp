/** maximum flow in a graph from s(given) to t(given) in O(V^2*E) or O(EsqrtV) for unit networks
    tested on spoj FASTFLOW (0.31s)
    initialize only with the number of vertices (plus one since they are 0-indexed)
    computes the flow from s to t with flow(s,t), you can call it multiple times
    after computing the flow edges will contain a vector with the edges and the flow that passes trough them
    Written by humbertoyusta */

struct flowedge{
    int u, v;
    long long cap, flow = 0;
    flowedge(int u,int v,long long cap) : u(u), v(v), cap(cap) {}
};

struct dinic{
    const long long flow_inf = 2000000000000000007ll;
    int V, E, s, t;
    vector<flowedge> edges;
    vector<vector<int>> adj;
    vector<int> lv, ptr;
    queue<int> q;

    dinic(int _V){
        V = _V; E = 0;
        adj.clear(); adj.resize(V);
        lv.clear(); lv.resize(V);
        ptr.clear(); ptr.resize(V);
    }

    void addedge(int u,int v,long long cap){
        edges.push_back(flowedge(u,v,cap));
        edges.push_back(flowedge(v,u,0));
        adj[u].push_back(E);
        adj[v].push_back(E+1);
        E += 2;
    }

    long long dfs(int u,int pushed){
        if( pushed == 0 ) return 0;
        if( u == t ) return pushed;
        for(int &cid = ptr[u]; cid < adj[u].size(); cid ++){
            int id = adj[u][cid];
            int v = edges[id].v;
            if( edges[id].cap - edges[id].flow <= 0 || lv[v] != lv[u] + 1 )
                continue;
            long long fl = dfs( v , min( pushed , edges[id].cap - edges[id].flow ) );
            if( fl == 0 )
                continue;
            edges[id].flow += fl;
            edges[id^1].flow -= fl;
            return fl;
        }
        return 0;
    }

    bool bfs(){
        q.push(s);
        lv[s] = 0;
        while( !q.empty() ){
            int u = q.front();
            q.pop();
            for(int v : adj[u]){
                if( edges[v].cap - edges[v].flow <= 0 || lv[edges[v].v] != -1 )
                    continue;
                lv[edges[v].v] = lv[u] + 1;
                q.push(edges[v].v);
            }
        }
        return lv[t] != -1;
    }

    long long flow(int _s,int _t){
    	for(int i=0; i<edges.size(); i++)
    	    edges[i].flow = 0;
        s = _s;
        t = _t;
        int ret_flow = 0;
        while( true ){
            fill( lv.begin() , lv.end() , -1 );
            if( !bfs() )
                break;
            fill( ptr.begin() , ptr.end() , 0 );
            while( true ){
                long long pushed = dfs(s,flow_inf);
                if( pushed == 0 ) break;
                ret_flow += pushed;
            }
        }
        return ret_flow;
    }

};

