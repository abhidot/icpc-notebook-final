struct centroid {
  vvi adj; int n; 
  vi vis,par,sz;
  void init(int s){
    n=s; adj=vvi(n,vi());
    vis=vi(n,0); par=sz=vi(n);}
  void addEdge(int a,int b){
    adj[a].pb(b); adj[b].pb(a);}
  int findSize(int v,int p=-1){
    if(vis[v]) return 0;
    sz[v]=1;
    for(int x:adj[v]){
      if(x!=p) sz[v]+=findSize(x,v);}
    return sz[v];}
  int findCentroid(int v,int p,int n){
    for(int x:adj[v])
      if(x!=p && !vis[x] && sz[x]>n/2)
        return findCentroid(x,v,n);
    return v;}
  void initCentroid(int v=0,int p=-1){
    findSize(v);
    int c=findCentroid(v,-1,sz[v]);
    vis[c]=true; par[c] = p;
    for(int x:adj[c])
      if(!vis[x]) initCentroid(x,c);}
};