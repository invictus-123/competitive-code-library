// Credits : Benq
// Time Complexity : O(N^2M) flow, O(Msqrt(N)) bipartite matching
// Verification : https://codeforces.com/contest/1139/submission/91487265
// Declaration : Dinic <SZ> Network;
// 		 Adding edges -> Network.addEdge(from, to, cap);
// 		 Max Flow = Network.maxFlow(src, sink);
template <int SZ> struct  Dinic {
	int N = 0, s, t;
	typedef ll F; // define type of flow
	struct Edge {int to, rev; F flow, cap; int id;};
	vector <Edge> adj[SZ];
	void addEdge(int u, int v, F cap, int id = 0) {
		N = max(N, max(u, v) + 1);
		Edge a = {v, (int) adj[v].size(), 0, cap, id}, b = {u, (int) adj[u].size(), 0, 0, 0};
		adj[u].push_back(a), adj[v].push_back(b);
	}
	int lvl[SZ]; typename vector <Edge>::iterator cur[SZ];
	bool bfs() {
		for(int i = 0; i < SZ; i ++) lvl[i] = -1, cur[i] = adj[i].begin();
		queue <int> q({s}); lvl[s] = 0;
		while(!q.empty()) {
			int u = q.front(); q.pop();
			for(auto &e : adj[u]) if(lvl[e.to] == -1 && e.flow < e.cap) {
				q.push(e.to);
				lvl[e.to] = lvl[u] + 1;
			}
		}
		return lvl[t] >= 0;
	}
	F dfs(int u, F flow) {
		if(u == t || !flow) return flow;
		for(; cur[u] != adj[u].end(); cur[u] ++) {
			Edge &e = *cur[u];
			if(lvl[e.to] != lvl[u] + 1 || e.flow == e.cap) continue;
			F df = dfs(e.to, min(flow, e.cap - e.flow));
			if(df) {
				e.flow += df; adj[e.to][e.rev].flow -= df;
				return df;
			}
		}
		return 0;
	}
	F maxFlow(int _s, int _t) {
		s = _s, t = _t;
		F totFlow = 0;
		while(bfs()) {
			F df = dfs(s, numeric_limits <F>::max());
			while(df) {
				totFlow += df;
				df = dfs(s, numeric_limits <F>::max());
			}
		}
		return totFlow;
	}
};
