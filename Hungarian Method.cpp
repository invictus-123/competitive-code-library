// Source : https://www.topcoder.com/community/competitive-programming/tutorials/assignment-problem-and-hungarian-algorithm/
// Time Complexity : O(N^3)
// Verification : https://codeforces.com/contest/491/submission/82311594
// Declaration : Build the cost matrix (for min weight matching use negative costs)
// 		 hungarian(N);
// 		 xmatch[i] -> cost[i][xmatch[i]] is chosen
// 		 ymatch[j] -> cost[ymatch[j]][j] is chosen
const int N = 62, INF = 1e9;
int cost[N][N], max_match, lx[N], ly[N], xmatch[N], ymatch[N], slack[N], slackx[N], pre[N];
bool S[N], T[N];
void add(int x, int prevx, int n) {
	S[x] = true, pre[x] = prevx;
	for(int y = 0; y < n; y ++) {
		if(lx[x] + ly[y] - cost[x][y] < slack[y]) {
			slack[y] = lx[x] + ly[y] - cost[x][y];
			slackx[y] = x;
		}
	}
}
void update(int n) {
	int delta = INF;
	for(int i = 0; i < n; i ++) if(!T[i]) delta = min(delta, slack[i]);
	for(int i = 0; i < n; i ++) {
		if(T[i]) ly[i] += delta;
		else slack[i] -= delta;
		if(S[i]) lx[i] -= delta;
	}
}
void augment(int n) {
	if(max_match == n) return;
	int x, y, root, wr = 0, rd = 0, q[N];
	memset(S, false, sizeof(S)), memset(T, false, sizeof(T)), memset(pre, -1, sizeof(pre));
	for(x = 0; x < n; x ++) {
		if(xmatch[x] == -1) {
			q[wr ++] = x, root = x;
			pre[x] = -2;
			S[x] = true;
			break;
		}
	}
	for(y = 0; y < n; y ++) {
		slack[y] = lx[root] + ly[y] - cost[root][y];
		slackx[y] = root;
	}
	while(true) {
		while(rd < wr) {
			x = q[rd ++];
			for(y = 0; y < n; y ++) {
				if(cost[x][y] == lx[x] + ly[y] && !T[y]) {
					if(ymatch[y] == -1) break;
					T[y] = true;
					q[wr ++] = ymatch[y];
					add(ymatch[y], x, n);
				}
			}
			if(y < n) break;
		}
		if(y < n) break;
		update(n);
		wr = 0, rd = 0;
		for(y = 0; y < n; y ++) {
			if(!T[y] && slack[y] == 0) {
				if(ymatch[y] == -1) {
					x = slackx[y];
					break;
				}
				T[y] = true;
				if(!S[ymatch[y]]) {
					q[wr ++] = ymatch[y];
					add(ymatch[y], slackx[y], n);
				}
			}
		}
		if(y < n) break;
	}
	if(y < n) {
		max_match ++;
		for(int cx = x, cy = y, ty; cx != -2; cx = pre[cx], cy = ty) {
			ty = xmatch[cx];
			ymatch[cy] = cx;
			xmatch[cx] = cy;
		}
		augment(n);
	}
}
int hungarian(int n) {
	int ans = 0;
	memset(xmatch, -1, sizeof(xmatch)), memset(ymatch, -1, sizeof(ymatch));
	for(int i = 0; i < n; i ++) for(int j = 0; j < n; j ++) lx[i] = max(lx[i], cost[i][j]);
	augment(n);
	for(int i = 0; i < n; i ++) ans += cost[i][xmatch[i]];
	return ans;
}
