using node = array<int,CNT> ;
node comb(node a, node b) {
    node c;
    rep(i,0,CNT) c[i] = a[i] ^ b[i];
    return c; 
}
// 0-indexed
template<class T> struct basic_segment_tree { // comb(ID,b) = b
    const T ID =  {0}; 
    int n; vector<T> seg;
    void init(int _n) { 
        n = _n; seg.assign(2*n,ID); 
    }
    void pull(int p) { 
        seg[p] = comb(seg[2*p], seg[2*p + 1]); 
    }
    void upd(int p, T val) { // update val at position p
        seg[p += n] = val; 
        for (p /= 2; p; p /= 2) pull(p); 
    }
    T query(int l, int r) { // query on interval [l, r]
        T ra = ID, rb = ID;
        for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
            if (l&1) ra = comb(ra,seg[l++]);
            if (r&1) rb = comb(seg[--r],rb);
        }
        return comb(ra,rb);
    }
};
//  0-indexed
template<bool VALS_IN_EDGES> struct HLD { 
    int N;
    int timer;
    vector<vector<int>> adj;
    vector<int> par, root, depth, sz,  pos;
    vector<int> rpos; // rpos not used, but could be useful
    basic_segment_tree<node> tree; // segment tree 
    void init(int _N){
        N = _N;
        adj.assign(N,{});
        par.assign(N,-1);
        root.assign(N,-1);
        depth.assign(N,-1);
        sz.assign(N,-1);
        pos.assign(N,-1);
        tree.init(N);
    }
    void ae(int x, int y) { 
        adj[x].push_back(y), adj[y].push_back(x); 
    }
    void dfs_sz(int x) { 
        sz[x] = 1; 
        for(auto& y : adj[x]) {
            par[y] = x; depth[y] = depth[x] + 1;
            adj[y].erase(find(adj[y].begin() ,adj[y].end(),x)); // remove parent from adj list
            dfs_sz(y); 
            sz[x] += sz[y];
            if (sz[y] > sz[adj[x][0]]) swap(y,adj[x][0]); // store the heavy child at first vertex
        }
    }
    void dfs_hld(int x) {
        pos[x] = timer++; rpos.push_back(x);
        for(auto& y : adj[x]) {
            root[y] = (y == adj[x][0] ? root[x] : y);
            dfs_hld(y); 
        }
    }
    void gen(int R = 0) { 
        par[R] = depth[R] = timer = 0; 
        dfs_sz(R); 
        root[R] = R;
        dfs_hld(R); 
    }
    int lca(int x, int y) {
        for (; root[x] != root[y]; y = par[root[y]]){
            if (depth[root[x]] > depth[root[y]]) swap(x,y);
        }
        return depth[x] < depth[y] ? x : y;
    }
    int dist(int x, int y) { // # edges on path
         return depth[x] + depth[y] - 2 * depth[lca(x,y)]; 
    }
    void process_path(int x, int y, auto op) {
        for (; root[x] != root[y]; y = par[root[y]]) {
            if (depth[root[x]] > depth[root[y]]) swap(x,y);
            op(pos[root[y]],pos[y]); 
        }
        if (depth[x] > depth[y]) swap(x,y);
        op(pos[x]+VALS_IN_EDGES,pos[y]); 
    }
    void modify_path(int x, int y, node v) { 
        process_path(x,y,[this,&v](int l, int r) {
            assert(l == r); 
            tree.upd(l,v); 
        });
    }
    node query_path(int x, int y) { 
        node res = {0}; 
        process_path(x,y,[this,&res](int l, int r) { 
            res = comb(res,tree.query(l,r)); 
        });
        return res; 
    }
     /*
      * this is for range update.
    void modify_subtree(int x, int v) { 
        tree.upd(pos[x] + VALS_IN_EDGES, pos[x] + sz[x] - 1, v); 
    }
    */
};
