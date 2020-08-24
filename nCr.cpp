ll fact[MAX];
void calculate() {
	fact[0] = 1;
	for(int i = 1; i < MAX; i ++) {
		fact[i] = (fact[i - 1] * i) % MOD;
	}
}
// call calculate() in main function!!!
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
ll nCr(ll n, ll r) {
	return (fact[n] * modInverse(fact[n - r]) % MOD * modInverse(fact[r]) % MOD) % MOD;
}
