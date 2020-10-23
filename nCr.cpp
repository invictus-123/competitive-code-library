// don't forget to call calculate in main
ll fact[MAX], invfact[MAX];
ll modExp(ll b, ll p) {
	ll res = 1;
	while(p > 0) {
		if(p & 1) res = (res * b) % MOD;
		b = (b * b) % MOD, p >>= 1;
	}
	return res;
}
ll modInverse(ll n) {
	return modExp(n, MOD - 2); 
}
void calculate() {
	fact[0] = 1;
	for(int i = 1; i < MAX; i ++) {
		fact[i] = (fact[i - 1] * i) % MOD;
	}
	invfact[MAX - 1] = modInverse(fact[MAX - 1]);
	for(int i = MAX - 2; i >= 0; i --) {
		invfact[i] = ((i + 1) * invfact[i + 1]) % MOD;
	}
}
ll nCr(ll n, ll r) {
	if(n < 0 || r < 0 || n < r) return 0;
	ll ret = fact[n];
	ret = (ret * invfact[n - r]) % MOD;
	ret = (ret * invfact[r]) % MOD;
	return ret;
}
