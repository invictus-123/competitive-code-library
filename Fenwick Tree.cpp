struct FenwickTree {
	int n;
	vector <ll> BIT;
	FenwickTree(int n):
		n(n), BIT(2 * n) {}
	void update(int x, ll val) {
		for(; x <= n; x += x & (-x)) BIT[x] += val;
	}
	ll get(int x) {
		ll sum = 0;
		for(; x > 0; x -= x & (-x)) sum += BIT[x];
		return sum;
	}
	int SearchPrefix(ll val) {
		ll sum = 0;
		int x = 0;
		for(int i = 19; i >= 0; i --) {
			if(x + (1 << i) <= n && sum + BIT[x + (1 << i)] < val) {
				sum += BIT[x + (1 << i)];
				x += (1 << i);
			}
		}
		return x + 1;
	}
};
