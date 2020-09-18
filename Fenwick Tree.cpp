struct FenwickTree {
	int n;
	vector <ll> BIT;
	FenwickTree(int n):
		n(n), BIT(2 * n) {}
	void update(int x, ll val) {
		while(x <= n) {
			BIT[x] += val;
			x += x & (-x);
		}
	}
	ll get(int x) {
		ll sum = 0;
		while(x > 0) {
			sum += BIT[x];
			x -= x & (-x);
		}
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
