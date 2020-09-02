// Time Complexity : O(nlogn) precomputation
// 		     O(1) per query
// Verification : https://codeforces.com/contest/475/submission/91093846
// Declaration : Creates a sparse table over array 'a'
// 			SparseTable <int> ST(sz);
// 		 To query : ST.query(l, r);
// 		 Modify comb function as per need
int a[MAX];
template <class T> struct SparseTable {
	int n, logn;
	vector <int> log; vector <vector <T>> dp;
	SparseTable(int _n) {
		n = _n; logn = ceil(log2(n)) + 1;
		log.assign(n + 1, 0); dp.assign(logn, vector <T> (n, 0));
	}
	T comb(T a, T b) { return __gcd(a, b); }
	void build() {
		log[1] = 0;
		for(int i = 0; i <= n; i ++) {
			if(i > 1) log[i] = log[i / 2] + 1;
			if(i < n) dp[0][i] = a[i];
		}
		for(int j = 1; j < logn; j ++) {
			for(int i = 0; i + (1 << j) <= n; i ++) {
				dp[j][i] = comb(dp[j - 1][i], dp[j - 1][i + (1 << (j - 1))]);
			}
		}
	}
	T query(int l, int r) {
		int ln = log[r - l + 1];
		return comb(dp[ln][l], dp[ln][r - (1 << ln) + 1]);
	}
};
