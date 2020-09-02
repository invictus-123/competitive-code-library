// Credits : Benq
// Time Complexity : O(FMlog(M)), where F is the max flow
// Verification : https://codeforces.com/contest/362/submission/91194818
// Declaration : MCMF <SZ> Network;
// 		 Add edges -> Network.addEdge(from, to, cap, cost);
// 		 pair {flow, cost} = Network.calc(src, sink);
template <int SZ> struct MCMF { 
	int N = 0, s, t;
	typedef int F; typedef int C; // define type of flow and cost
	struct Edge {int to, rev; F flow, cap; C cost; int id;};
	vector <Edge> adj[SZ];
	void addEdge(int u, int v, F cap, C cost, int id = 0) {
		N = max(N, max(u, v) + 1);
		Edge a = {v, (int) adj[v].size(), 0, cap, cost, id}, b = {u, (int) adj[u].size(), 0, 0, -cost, 0};
		adj[u].push_back(a), adj[v].push_back(b);
	}
	pair <int, int> pre[SZ];
	pair <C, F> cost[SZ];
	C totCost = 0, curCost = 0; F totFlow = 0;
	bool SPFA() {
		for(int i = 0; i < SZ; i ++) cost[i] = {numeric_limits <C>::max(), 0};
		cost[s] = {0, numeric_limits <F>::max()};
		typedef pair <C, int> T;
		priority_queue <T, vector <T>, greater <T>> pq;
		pq.push({0, s});
		while(!pq.empty()) {
			T cur = pq.top(); pq.pop();
			if(cur.first > cost[cur.second].first) continue;
			for(auto &e : adj[cur.second]) {
				if(e.flow == e.cap) continue;
				if(cost[e.to].first > cur.first + e.cost) {
					cost[e.to] = {cur.first + e.cost, min(e.cap - e.flow, cost[cur.second].second)};
					pre[e.to] = {cur.second, e.rev};
					pq.push({cost[e.to].first, e.to});
				}
			}
		}
		return cost[t].second;
	}
	void backTrack() {
		F df = cost[t].second; totFlow += df;
		curCost += cost[t].first; totCost += curCost * df;
		for(int u = t; u != s; u = pre[u].first) {
			adj[u][pre[u].second].flow -= df;
			adj[pre[u].first][adj[u][pre[u].second].rev].flow += df;
		}
		for(int i = 0; i < SZ; i ++) for(auto &e : adj[i]) e.cost += cost[i].first - cost[e.to].first;
	}
	pair <F, C> calc(int _s, int _t) {
		s = _s, t = _t;
		while(SPFA()) backTrack();
		return {totFlow, totCost};
	}
};
