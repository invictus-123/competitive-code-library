const int N = 1e5 + 100;
const int LOGN = ceil(log2(N)) + 1;
int level[N], par[LOGN][N];
vector <int> g[N];
void dfs(int u, int p) {
	par[0][u] = p;
	for(int v : g[u]) {
		if(v != p) {
			level[v] = level[u] + 1;
			dfs(v, u);
		}
	}
}
void precompute() {
	for(int i = 1; i < LOGN; i ++) {
		for(int j = 1; j <= N; j ++) {
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
