struct item{
	int val;
	bool operator==(const item& b){
		return val==b.val;
	}
};


// calc = min, modify = add
struct segtree{
	int size;
	vector<item> tree, ops;
	
	item NEUTRAL = {INF};
	item NO_OP = {0};
	
	item single(int v){return {v};}
	item calc_op(item a, item b){return single(min(a.val, b.val));}
	
	item modify_op(item a, item b, int len){
		if(b==NO_OP) return a;
		return single(a.val + b.val);
	}
	
	void apply_mod_op(item& a, item b, int len){
		a = modify_op(a, b, len);
	}
	
	void init(int n){
		size=1;
		while(size<n) size*=2;
		ops.assign(2*size, NO_OP);
		tree.assign(2*size, NEUTRAL);
	}
	
	//Each node stores the answer for [lx, rx)
	void build(vector<int>&a, int x, int lx, int rx){
		if(rx-lx==1){
			if(lx<(int)(a.size())){
				tree[x] = single(a[lx]); 
			}
			
			return;
		}
		
		int m = (lx + rx)/2;
		build(a, 2*x+1, lx, m);
		build(a, 2*x+2, m, rx);
		
		tree[x] = calc_op(tree[2*x+1] , tree[2*x+2]);
	}
	
	segtree(int n){
		init(n);
	}
	
	segtree(vector<int>& a):segtree(a.size()){
		build(a, 0, 0, size);
	}
	
	void propagate(int x, int lx, int rx){
		if(rx-lx==1) return;
		
		int m = (lx+rx)/2;
		
		apply_mod_op(ops[2*x + 1], ops[x], 1);
		apply_mod_op(tree[2*x + 1], ops[x], m - lx);
		
		apply_mod_op(ops[2*x + 2], ops[x], 1);
		apply_mod_op(tree[2*x + 2], ops[x], rx - m);
		
		ops[x] = NO_OP;
	}
	
	void modify(int l, int r, int v, int x, int lx, int rx){
		propagate(x, lx, rx);
		if(lx>=r || rx<=l) return;
		if(lx>=l && rx<=r){
			apply_mod_op(ops[x], single(v), 1);
			apply_mod_op(tree[x], single(v), rx-lx);
			return;
		}
		
		int m = (lx + rx)/2;
		
		modify(l, r, v, 2*x+1, lx, m);
		modify(l, r, v, 2*x+2, m, rx);
		
		tree[x] = calc_op(tree[2*x+1] , tree[2*x+2]);
	}
	
	void modify(int l, int r, int v){
		modify(l, r, v, 0, 0, size);
	}
	
	item query(int l, int r, int x, int lx, int rx){
		propagate(x, lx, rx);
		if(lx>=r || rx<=l) return NEUTRAL;
		if(lx>=l && rx<=r) return tree[x];
		
		int m = (lx + rx)/2;
		item q1 = query(l, r, 2*x +1, lx, m);
		item q2 = query(l, r, 2*x +2, m, rx);
		
		return calc_op(q1 , q2);
	}
	
	item query(int l, int r){
		return query(l, r, 0, 0, size);
	}
};