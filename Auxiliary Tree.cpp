set<pair<int, int> > vertSet;
for(int i = 0; i < k; i++)
vertSet.insert({out[a[i]], a[i]});
vector<pair <int, pii> > compressedEdges;
while((int)vertSet.size() > 1)
{
    int u = vertSet.begin()->second;
    vertSet.erase({out[u], u});
    int v = vertSet.begin()->second;
    int lca2 = lca(u, v);
    compressedEdges.push_back({cal(u, lca2), {u, lca2}});
    vertSet.insert({out[lca2], lca2});
}
sort(all(compressedEdges));
