const int MAX = 1e5 + 10;
struct edge {
	int u, v;
	ll w;
	bool operator < (edge const & other) {
		return w < other.w;
	}
};
vector <edge> edges, result;
int par[MAX], sz[MAX];
void init(int v) {
	par[v] = v;
	sz[v] = 1;
}
int find(int v) {
	return v == par[v] ? v : par[v] = find(par[v]);
}
void join(int u, int v) {
	u = find(u), v = find(v);
	if(u != v) {
		if(sz[u] < sz[v]) swap(u, v);
		par[v] = u;
		sz[u] += sz[v];
	}
}
ll kruskal(int n) {
	ll cost = 0;
	for(int i = 1; i <= n; i ++) init(i);
	sort(edges.begin(), edges.end());
	for(edge e : edges) {
		if(find(e.u) != find(e.v)) {
			cost += e.w;
			result.push_back(e);
			join(e.u, e.v);
		}
	}
	return cost;
}
