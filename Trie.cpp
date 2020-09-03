// Time Complexity : O(bits)
// Verification : https://codeforces.com/contest/923/submission/91750294
// Modifications : Tarun Singhania (bhayia)
// Declaration : Wrtie root = new TrieNode() in main. 
struct TrieNode {
	TrieNode *bit[2];
	int cnt;
	TrieNode() {
		bit[0] = bit[1] = NULL;
		cnt = 0;
	}
};
TrieNode *root;
void add(int x) {
	TrieNode* cur = root;
	for(int i = 30; i >= 0; i --) {
		int b = (x >> i) & 1;
		if(!cur->bit[b]) cur->bit[b] = new TrieNode();
		cur->cnt ++;
		cur = cur->bit[b];
	}
	cur->cnt ++;
}
void remove(int x) {
	TrieNode *cur = root;
	for(int i = 30; i >= 0; i --) {
		int b = (x >> i) & 1;
		TrieNode *temp = cur->bit[b];
		if(cur->bit[b]->cnt - 1 == 0) cur->bit[b] = NULL;
		cur->cnt --;
		if(cur && cur->cnt == 0) free(cur);
		cur = temp;
	}
}
int query(int x) {
	TrieNode *cur = root;
	int ans = 0;
	for(int i = 30; i >= 0; i --) {
		int b = (x >> i) & 1;
		if(cur->bit[b] != NULL && cur->bit[b]->cnt > 0) {
			
		}
		else {
			
		}
	}
	return ans;
}
