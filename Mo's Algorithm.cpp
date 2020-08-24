struct Query {
	int l, r, id;
	void read(int _i) {
		cin >> l >> r;
		id = _i;
	}
	bool operator < (Query a) {
		if(l / BLK != a.l / BLK) return l / BLK < a.l / BLK;
		return ((l / BLK) & 1 ? r < a.r : r > a.r);
	}
} Q[MAX];
ll ans[MAX], cur = 0;
void add(int x) {
	
}
void remove(int x) {
	
}
void mos_algorithm() {
	sort(Q, Q + q);
	int l = Q[0].l, r = Q[0].l - 1;
	for(int i = 0; i < q; i ++) {
		while(l < Q[i].l) remove(p[l ++]);
		while(l > Q[i].l) add(p[-- l]);
		while(r < Q[i].r) add(p[++ r]);
		while(r > Q[i].r) remove(p[r --]);
		ans[Q[i].id] = cur;
	}
}
