int par[N], siz[N], op[N];
// DON'T TAKE 0 AS A NODE
int findset(int a) {
    if(par[a]==a)
    return a;
    return par[a]=findset(par[a]);}
void unionset(int a, int b) {
    if(a==0 || b==0)
    return;
    a=findset(a);
    b=findset(b);
    if(a==b)
    return;
    if(siz[a]>siz[b])
    swap(a, b);
    par[a]=b;
    siz[b]+=siz[a];
    unionset(op[a], op[b]);
    op[b]=max(op[b], op[a]);}