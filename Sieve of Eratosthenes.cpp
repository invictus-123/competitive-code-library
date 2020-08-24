const int MAX = 1e6 + 1;
bool prime[MAX];
void sieve() {
	memset(prime, true, sizeof(prime));
	prime[0] = prime[1] = false;
	for(int i = 2; i * i < MAX; i ++) {
		if(prime[i]) {
			for(int j = i * i; j < MAX; j += i) prime[j] = false;
		}
	}
}
