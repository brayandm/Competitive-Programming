/** Heavy light descomposition of a given (0-indexed) tree
    written by humbertousta, tested on SPOJ QTREE */
typedef vector<vector<int>> graph;
template<typename T>
struct HLD{
    int n, cur_pos;
    vector<int> par, lv, heavy, head, pos, ipos, r_pos;
    graph adj;
    T Neutral;

    int dfs(int v) {
        int size_ = 1;
        int max_c_size = 0;
        for (int c : adj[v]) {
            if (c != par[v]) {
                par[c] = v, lv[c] = lv[v] + 1;
                int c_size = dfs(c);
                size_ += c_size;
                if (c_size > max_c_size)
                    max_c_size = c_size, heavy[v] = c;
            }
        }
        return size_;
    }

    void decompose(int v, int h) {
        head[v] = h; ipos[cur_pos] = v; pos[v] = cur_pos++; r_pos[v] = pos[v];
        if (heavy[v] != -1){
            decompose(heavy[v], h);
            r_pos[v] = max( r_pos[v] , r_pos[heavy[v]] );
        }
        for (int c : adj[v]) {
            if (c != par[v] && c != heavy[v]){
                decompose(c, c);
                r_pos[v] = max( r_pos[v] , r_pos[heavy[v]] );
            }
        }
    }

    HLD(const graph& _adj, T _Neutral) {
        adj = _adj;
        n = adj.size();
        par = vector<int>(n);
        lv = vector<int>(n);
        heavy = vector<int>(n, -1);
        head = vector<int>(n);
        pos = vector<int>(n);
        ipos = vector<int>(n);
        r_pos = vector<int>(n);
        cur_pos = 0;
        Neutral = _Neutral;

        dfs(0);
        decompose(0, 0);
    }

    T path_query(int a, int b,ST<T> &st) {
        T res = Neutral;
        for (; head[a] != head[b]; b = par[head[b]]) {
            if (lv[head[a]] > lv[head[b]])
                swap(a, b);
            T cur_heavy_path = st.query(pos[head[b]], pos[b]);
            res = st.merge_(res, cur_heavy_path);
        }
        if (lv[a] > lv[b])
            swap(a, b);
        T last_heavy_path = st.query(pos[a], pos[b]);
        res = st.merge_(res, last_heavy_path);
        return res;
    }

    T subt_query(int a,ST<T> &st){
        return st.query(pos[a],r_pos[a]);
    }

    int lca(int a, int b) {
        for (; head[a] != head[b]; b = par[head[b]]) {
            if (lv[head[a]] > lv[head[b]])
                swap(a, b);
        }
        if (lv[a] > lv[b])
            swap(a, b);
        return a;
    }

    int go_up(int u, int k){
        // The kth node (0 indexed) in the path from (u to root)
        for (;pos[u] - pos[head[u]] < k; u = par[head[u]])
            k -= pos[u] - pos[head[u]] + 1;
        return ipos[pos[u] - k];
    }
};
