vector <int> manacher(string &s) {
	string s1 = "@";
	for(int i = 0; i < (int) s.size(); i ++) {
		s1 += s[i]; s1 += "#";
	}
	s1.back() = '&';
	int sz = s1.size() - 1, l = 0, r = 0;
	vector <int> m(sz, 0);
	for(int i = 1; i < sz; i ++) {
		if(i != 1) m[i] = min(r - i, m[r - i + l]);
		while(s1[i - m[i] - 1] == s1[i + m[i] + 1]) m[i] ++;
		if(i + m[i] > r) l = i - m[i], r = i + m[i];
	}
	m.erase(begin(m));
	sz --;
	for(int i = 0; i < sz; i ++) {
		if((i & 1) == (m[i] & 1)) m[i] ++;
	}
	return m;
}
