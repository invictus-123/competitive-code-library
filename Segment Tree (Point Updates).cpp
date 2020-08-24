template <class T> struct SegTree {
	const T ID = 0;
	int n; vector <T> seg;
	T comb(T a, T b) { return a | b; }
	SegTree(int _n) { n = _n; seg.assign(2 * n, ID); }
	void pull(int p) { seg[p] = comb(seg[2 * p], seg[2 * p + 1]); }
	void update(int idx, T val) {
		seg[idx += n] = val;
		for(idx /= 2; idx; idx /= 2) pull(idx);
	}
	T query(int l, int r) {
		T lnode = ID, rnode = ID;
		for(l += n, r += n + 1; l < r; l /= 2, r /= 2) {
			if(l & 1) lnode = comb(lnode, seg[l ++]);
			if(r & 1) rnode = comb(seg[-- r], rnode);
		}
		return comb(lnode, rnode);
	}
};
