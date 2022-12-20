#define v64 vector <ll>
#define sz(a) (int)a.size()
pair<ll, v64> hungarian(const vector<v64> &a) {
 if (a.empty()) return {-1e17, {}};
 int n = sz(a) + 1;
 int m = sz(a[0]) + 1;
 vi u(n), v(m), p(m), ans(n - 1);
 rep(i,1,n) {
  p[0] = i;
  int j0 = 0; // add "dummy" worker 0
  vector<ll> dist(m, 1e17), pre(m, -1);
  vector<bool> done(m + 1);
  do { // dijkstra
   done[j0] = true;
   int i0 = p[j0], j1, delta = 1e17;
   rep(j,1,m) if (!done[j]) {
    auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
    if (cur < dist[j]) dist[j] = cur, pre[j] = j0;
    if (dist[j] < delta) delta = dist[j], j1 = j;
   }
   rep(j,0,m) {
    if (done[j]) u[p[j]] += delta, v[j] -= delta;
    else dist[j] -= delta;
   }
   j0 = j1;
  } while (p[j0]);
  while (j0) { // update alternating path
   int j1 = pre[j0];
   p[j0] = p[j1], j0 = j1;
  }
 }
 rep(j,1,m) if (p[j]) ans[p[j] - 1] = j - 1;
 return {-v[0], ans}; // min cost
}