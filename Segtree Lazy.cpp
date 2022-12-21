void propogate(int node, int l, int r){
    if(l!=r){
        lazy[node*2]+=lazy[node];
        lazy[node*2+1]+=lazy[node];
    }
    st[node]+=lazy[node];
    lazy[node]=0;}
void build(int node, int l, int r){
    if(l==r){
        st[node]=ar[l];
	    lazy[node]=0;
        return;}
    int mid=(l+r)/2;
    build(node*2, l, mid);
    build(node*2+1, mid+1, r);
    st[node]=min(st[node*2], st[node*2+1]);
    lazy[node]=0;
    return;}
void update(int node, int l, int r, int x, int y, int val){
    if(lazy[node]!=0) propogate(node, l, r);
    if(y<x||x>r||y<l) return;
    if(l>=x&&r<=y){
        st[node]+=val;
        if(l!=r){
            lazy[node*2]+=val;
            lazy[node*2+1]+=val;
        }
        return;}
    int mid=(l+r)/2;
    update(node*2, l, mid, x, y, val);
    update(node*2+1, mid+1, r, x, y, val);
    st[node]=min(st[node*2], st[node*2+1]);
    return;}
int query(int node, int l, int r, int x, int y){
    if(lazy[node]!=0) propogate(node, l, r);
    if(y<x||y<l||x>r) return INF;
    if(l>=x&&r<=y) return st[node];
    int mid=(l+r)/2;
    return min(query(node*2, l, mid, x, y), query(node*2+1, mid+1, r, x, y));
}
