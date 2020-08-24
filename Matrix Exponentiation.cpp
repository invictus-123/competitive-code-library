const ll MOD = 1e9 + 7;
const int MAX = 2;
void MatMul(ll M1[MAX][MAX], ll M2[MAX][MAX]) {
	ll temp[MAX][MAX] = {0};
	for(int i = 0; i < MAX; i ++) {
		for(int j = 0; j < MAX; j ++) {
			for(int k = 0; k < MAX; k ++) {
				temp[i][j] = (temp[i][j] + M1[i][k] * M2[k][j]) % MOD;
			}
		}
	}
	for(int i = 0; i < MAX; i ++) for(int j = 0; j < MAX; j ++) M1[i][j] = temp[i][j];
}
void MatExp(ll mat[MAX][MAX], ll p) {
	ll I[MAX][MAX] = {0};
	for(int i = 0; i < MAX; i ++) I[i][i] = 1;
	while(p > 0) {
		if(p & 1) MatMul(I, mat);
		MatMul(mat, mat);
		p >>= 1;
	}
	for(int i = 0; i < MAX; i ++) for(int j = 0; j < MAX; j ++) mat[i][j] = I[i][j];
}
