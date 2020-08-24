struct TrieNode {
	TrieNode *bit[2];
	int cnt;
	TrieNode() {
		bit[0] = bit[1] = NULL;
		cnt = 0;
	}
};
TrieNode *root;
// write root = new TrieNode(); in main!!!
void add(int x) {
	TrieNode* cur = root;
	for(int i = 30; i >= 0; i --) {
		int b = (x >> i) & 1;
		if(!cur->bit[b]) cur->bit[b] = new TrieNode();
		cur = cur->bit[b];
		cur->cnt ++;
	}
}
void remove(int x) {
	TrieNode *cur = root;
	for(int i = 30; i >= 0; i --) {
		int b = (x >> i) & 1;
		cur = cur->bit[b];
		cur->cnt --;
	}
}
int query(int x) {
	TrieNode *cur = root;
	int ans = 0;
	for(int i = 30; i >= 0; i --) {
		int b = (x >> i) & 1;
		if(cur->bit[b ^ 1] != NULL && cur->bit[b ^ 1]->cnt > 0) {
			
		}
		else {
			
		}
	}
	return ans;
}
