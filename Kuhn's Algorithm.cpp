struct Kuhn {
	vector <vector <int>> g;
	vector <int> L, R; vector <bool> vis;
	Kuhn(int n, int m) :
	g(n), L(n, -1), R(m, -1), vis(n) {}
	void addEdge(int a, int b) { g[a].push_back(b); }
	bool dfs(int u) {
		if(vis[u]) return false;
		vis[u] = true;
		for(int v : g[u]) {
			if(R[v] == -1) {
				L[u] = v, R[v] = u;
				return true;
			}
		}
		for(int v : g[u]) {
			if(dfs(R[v])) {
				L[u] = v, R[v] = u;
				return true;
			}
		}
		return false;
	}
	int solve() {
		bool flag = true;
		while(flag) {
			flag = false;
			fill(vis.begin(), vis.end(), false);
			for(int i = 0; i < (int) L.size(); ++ i) if(L[i] == -1) flag |= dfs(i);
		}
		int ret = 0;
		for(int i = 0; i < (int) L.size(); ++ i) ret += (L[i] != -1);
		return ret;
	}
};
