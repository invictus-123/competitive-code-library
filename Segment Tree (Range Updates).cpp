template <class T> struct SegTree {
	int n, N; vector <T> tree, lazy;
	const T ID = 0;
	void init(int _n) { n = _n, N = 4 * _n; tree.assign(N, ID), lazy.assign(N, ID); }
	T comb(T a, T b) { return a + b; }
	void prop(int i, int st, int en) {
		tree[i] += lazy[i];
		if(st != en) {
			lazy[2 * i] += lazy[i];
			lazy[2 * i + 1] += lazy[i];
		}
		lazy[i] = 0;
	}
	void _update(int i, int st, int en, int l, int r, T val) {
		if(lazy[i]) prop(i, st, en);
		if(en < l || st > r) return;
		if(l <= st && en <= r) {
			lazy[i] = val;
			prop(i, st, en);
			return;
		}
		int mid = (st + en) / 2;
		_update(2 * i, st, mid, l, r, val);
		_update(2 * i + 1, mid + 1, en, l, r, val);
		tree[i] = comb(tree[2 * i], tree[2 * i + 1]);
	}
	T _query(int i, int st, int en, int l, int r) {
		if(lazy[i]) prop(i, st, en);
		if(en < l || st > r) return ID;
		if(l <= st && en <= r) return tree[i];
		int mid = (st + en) / 2;
		return comb(_query(2 * i, st, mid, l, r), _query(2 * i + 1, mid + 1, en, l, r));
	}
	T query(int l, int r) { return _query(1, 1, n, l, r); }
	void update(int l, int r, T val) { _update(1, 1, n, l, r, val); }
};
