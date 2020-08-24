ll kadane(vector <ll> &v, int st = 0, int en = -1) {
	if(en == -1) en = v.size() - 1;
	ll cur_sum = 0, mx_sum = 0;
	for(int i = st; i <= en; i ++) {
		cur_sum = max(0LL, cur_sum + v[i]);
		mx_sum = max(mx_sum, cur_sum);
	}
	return mx_sum;
}
