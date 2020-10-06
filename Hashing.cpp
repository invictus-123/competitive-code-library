mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rand(ll a, ll b) {
    return uniform_int_distribution<ll>(a, b)(rng);
}
const int K = 3;
struct Hash {
	ll a[K];
	Hash() : a() {}
	Hash operator ^ (const Hash &A) const {
		Hash ans = Hash();
		for(int i = 0; i < K; i ++) ans.a[i] = a[i] ^ A.a[i];
		return ans;
	}
	bool operator == (const Hash &A) const {
		for(int i = 0; i < K; i ++) if(a[i] != A.a[i]) return false;
		return true;
	}
	bool operator < (const Hash &A) const {
		for(int i = 0; i < K; i ++) if(a[i] != A.a[i]) return a[i] < A.a[i];
		return false;	
	}
};
Hash genHash() {
	Hash ret = Hash();
	for(int i = 0; i < K; i ++) ret.a[i] = rand(1, 1LL << 60);
	return ret;
}
