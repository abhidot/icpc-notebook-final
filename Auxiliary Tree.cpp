// Global      
void dfs(int u, int p, int d)
{
    dep[u]=d;
    for(auto to:v[u])
    {
        if(to.ff==p)
        continue;
        dfs(to.ff, u, d+1);
        par[0][to.ff]=u;
    }
    out[u]=tim++;
}
void pre()
{
    for(int i=1;i<lg;i++)
    {
        for(int j=1;j<=n;j++)
        {
            par[i][j]=par[i-1][par[i-1][j]];
        }
    }
}
int lca(int a, int b)
{
    if(dep[a]>dep[b])
    swap(a, b);
    int diff=dep[b]-dep[a];
    for(int i=0;i<lg;i++)
    {
        if(diff&(1 << i))
        b=par[i][b];
    }
    if(a==b)
    return b;
    for(int i=lg-1;i>=0;i--)
    {
        if(par[i][a] && par[i][a]!=par[i][b])
        {
            a=par[i][a];
            b=par[i][b];
        }
    }
    return par[0][a];
}

//     Inside Function
            vector<pair <int, pii> > compressedEdges;
            while((int)vertSet.size() > 1)
            {
                int u = vertSet.begin()->second;
                vertSet.erase({out[u], u});
                int v = vertSet.begin()->second;
                int lca2 = lca(u, v);
//                 Yaha diffrence in depth ke jagah jo property ban raha ho voh dal dena
                compressedEdges.push_back({abs(dep[lca2]-dep[u]), {u, lca2}});
                vertSet.insert({out[lca2], lca2});
            }