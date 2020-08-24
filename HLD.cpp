const int N = 1e5 + 100;
const int LOGN = ceil(log2(N)) + 1;
int subtree[N], nxt[N], tin[N], tout[N], rtin[N], level[N], par[LOGN][N], tim;
vector <int> g[N];
void dfsHLD1(int u, int p = 0) {
	subtree[u] = 1;
	for(int &v : g[u]) {
		if(v == p) continue;
		dfsHLD1(v, u);
		subtree[u] += subtree[v];
		if(subtree[v] > subtree[g[u][0]]) swap(v, g[u][0]);
	}
}
void dfsHLD2(int u, int p = 0) {
	tin[u] = ++ tim;
	rtin[tim] = u;
	for(int v : g[u]) {
		if(v == p) continue;
		nxt[v] = (v == g[u][0] ? nxt[u] : v);
		dfsHLD2(v, u);
	}
	tout[u] = tim;
}
void dfsLCA(int u, int p = 0) {
	par[0][u] = p;
	for(int v : g[u]) {
		if(v != p) {
			level[v] = level[u] + 1;
			dfsLCA(v, u);
		}
	}
}
void precompute() {
	for(int i = 1; i < LOGN; i ++) {
		for(int j = 1; j < N; j ++) {
			if(par[i - 1][j]) par[i][j] = par[i - 1][par[i - 1][j]];
		}
	}
}
int LCA(int u, int v) {
	if(level[u] < level[v]) swap(u, v);
	int diff = level[u] - level[v];
	for(int i = LOGN - 1; i >= 0; i --) {
		if((1 << i) & diff) u = par[i][u];
	}
	if(u == v) return u;
	for(int i = LOGN - 1; i >= 0; i --) {
		if(par[i][u] && par[i][u] != par[i][v]) u = par[i][u], v = par[i][v];
	}
	return par[0][u];
}
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
SegTree <ll> seg;
void update(int l, int r, ll val) {
	seg.update(l, r, val);
}
ll query(int l, int r) {
	return seg.query(l, r);
}
ll _query(int x, int y) {
	ll res = 0;
	while(nxt[x] != nxt[y]) {
		res += query(tin[nxt[x]], tin[x]);
		x = par[0][nxt[x]];
	}
	res += query(tin[y] + 1, tin[x]); // use tin[y] to include y
	return res;
}
ll queryHLD(int x, int y) {
	ll lca = LCA(x, y);
	return _query(x, lca) + _query(y, lca);
}
void _update(int x, int y, ll val) {
	while(nxt[x] != nxt[y]) {
		update(tin[nxt[x]], tin[x], val);
		x = par[0][nxt[x]];
	}
	update(tin[y] + 1, tin[x], val); // use tin[y] to include y
}
void updateHLD(int x, int y, ll val) {
	int lca = LCA(x, y);
	_update(x, lca, val);
	_update(y, lca, val);
}
void HLD(int n) {
	for(int i = 1; i <= n; i ++) {
		subtree[i] = 0, nxt[i] = 0, tin[i] = 0, tout[i] = 0, rtin[i] = 0, level[i] = 0;
		for(int j = 0; j < LOGN; j ++) par[j][i] = 0;
	}
	tim = 0;
	dfsHLD1(1);
	dfsHLD2(1);
	dfsLCA(1);
	precompute();
	seg.init(n);
}
