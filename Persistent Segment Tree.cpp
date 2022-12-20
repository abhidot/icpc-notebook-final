struct PST {
#define lc t[cur].l
#define rc t[cur].r
  struct node {
    int l = 0, r = 0, val = 0;
  } t[20 * N];
  int T = 0;
  int build(int b, int e) {
    int cur = ++T;
    if(b == e) return cur;
    int mid = b + e >> 1;
    lc = build(b, mid);
    rc = build(mid + 1, e);
    t[cur].val = t[lc].val + t[rc].val;
    return cur;
  }
  int upd(int pre, int b, int e, int i, int v) {
    int cur = ++T;
    t[cur] = t[pre];
    if(b == e) {
      t[cur].val += v;
      return cur;
    }
    int mid = b + e >> 1;
    if(i <= mid) {
      rc = t[pre].r;
      lc = upd(t[pre].l, b, mid, i, v);
    } else {
      lc = t[pre].l;
      rc = upd(t[pre].r, mid + 1, e, i, v);
    }
    t[cur].val = t[lc].val + t[rc].val;
    return cur;
  }
  int query(int pre, int cur, int b, int e, int k) {
    if(b == e) return b;
    int cnt = t[lc].val - t[t[pre].l].val;
    int mid = b + e >> 1;
    if(cnt >= k) return query(t[pre].l, lc, b, mid, k);
    else return query(t[pre].r, rc, mid + 1, e, k - cnt);
  }
} t;
