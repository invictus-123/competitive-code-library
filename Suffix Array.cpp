// Time Complexity : O(nlogn)
// Verification : https://codeforces.com/contest/128/submission/91634452
// Declaration : To build the suffix array and LCP array for string s -
// 		Suffix Array(s);
// 		SA.buildSA();
// 		SA.buildLCP();
// SA.n -> size of string, SA.p -> suffix array, SA.lcp -> LCP array
void countSort(vector <int> &p, vector <int> &c) {
	int n = p.size();
	vector <int> cnt(n), pos(n);
	for(int x : c) cnt[x] ++;
	pos[0] = 0;
	for(int i = 1; i < n; i ++) pos[i] = pos[i - 1] + cnt[i - 1];
	vector <int> p_new(n);
	for(int x : p) {
		int idx = c[x];
		p_new[pos[idx] ++] = x;
	}
	p = p_new;
}
struct SuffixArray {
	string s; int n;
	vector <int> p, c, lcp;
	SuffxArray(string &cur) {
		s = cur + "$"; n = s.size();
		p.resize(n), c.resize(n), lcp.resize(n);
	}
	void buildSA() {
		vector <pair <int, int>> v(n);
		for(int i = 0; i < n; i ++) v[i] = {s[i], i};
		sort(v.begin(), v.end());
		for(int i = 0; i < n; i ++) p[i] = v[i].second;
		c[p[0]] = 0;
		for(int i = 1; i < n; i ++) {
			c[p[i]] = v[i].first == v[i - 1].first ? c[p[i - 1]] : c[p[i - 1]] + 1;
		}
		int k = 0;
		while((1 << k) < n) {
			for(int i = 0; i < n; i ++) p[i] = (p[i] - (1 << k) + n) % n;
			countSort(p, c);
			vector <int> c_new(n);
			c_new[p[0]] = 0;
			for(int i = 1; i < n; i ++) {
				pair <int, int> a = {c[p[i]], c[(p[i] + (1 << k)) % n]}, b = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
				c_new[p[i]] = a == b ? c_new[p[i - 1]] : c_new[p[i - 1]] + 1;
			}
			c = c_new;
			k ++;
		}
	}
	void buildLCP() {
		int k = 0;
		for(int i = 0; i < n - 1; i ++) {
			int pi = c[i]; int j = p[pi - 1];
			while(s[i + k] == s[j + k]) k ++;
			lcp[pi] = k;
			k = max(k - 1, 0);
		}
	}
};
