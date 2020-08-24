void dijkstra(int src) {
	for(int i = 0; i < MAX; i++) d[i] = INF;
	d[src] = 0;
	set <pair <ll, int>> s;
	s.insert({0LL, src});
	while(s.size()) {
		int u = s.begin()->second;
		s.erase(s.begin());
		for(auto e : g[u]) {
			int v = e.first; ll w = e.second;
			if(d[v] > d[u] + w) {
				s.erase({d[v], v});
				d[v] = d[u] + w;
				s.insert({d[v], v});
			}
		}
	}
}
