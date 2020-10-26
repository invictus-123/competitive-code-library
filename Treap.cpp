mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
struct Treap {
	int data, p; Treap *c[2];
	int sz; ll sum;
	bool flip;
	Treap(int val) {
		p = rng(); sum = val, data = val, sz = 1;
		c[0] = NULL, c[1] = NULL;
	}
};
int getSize(Treap *root) {
	return !root ? 0 : root->sz;
}
ll getSum(Treap *root) {
	return !root ? 0 : root->sum;
}
void prop(Treap *root) {
	if(!root || !root->flip) return;
	swap(root->c[0], root->c[1]);
	root->flip = 0;
	for(auto t : root->c) if(t != NULL) t->flip ^= 1;
}
Treap* calc(Treap *root) {
	Treap *l = root->c[0], *r = root->c[1];
	prop(l), prop(r);
	root->sz = 1 + getSize(l) + getSize(r);
	root->sum = root->data + getSum(l) + getSum(r);
	return root;
}
void inorder(Treap *root, vector <int> &v) {
	if(!root) return;
	prop(root);
	inorder(root->c[0], v);
	v.push_back(root->data);
	inorder(root->c[1], v);
}
vector <Treap*> splitCnt(Treap *root, int cnt) {
	// cnt nodes go to the left
	if(!root) return {root, root};
	prop(root);
	if(getSize(root->c[0]) >= cnt) {
		auto l = splitCnt(root->c[0], cnt);
		root->c[0] = l[1];
		return {l[0], calc(root)};
	}
	else {
		auto r = splitCnt(root->c[1], cnt - getSize(root->c[0]) - 1);
		root->c[1] = r[0];
		return {calc(root), r[1]};
	}
}
vector <Treap*> splitVal(Treap *root, int val) {
	// < val goes to left
	if(!root) return {root, root};
	prop(root);
	if(root->data >= val) {
		auto p = splitVal(root->c[0], val);
		root->c[0] = p[1];
		return {p[0], calc(root)};
	}
	else {
		auto p = splitVal(root->c[1], val);
		root->c[1] = p[0];
		return {calc(root), p[1]};
	}
}
Treap* merge(Treap *l, Treap *r) {
	if(!l) return r;
	if(!r) return l;
	prop(l), prop(r);
	Treap *ret;
	if(l->p > r->p) l->c[1] = merge(l->c[1], r), ret = l;
	else r->c[0] = merge(l, r->c[0]), ret = r;
	return calc(ret);
}
Treap* insert(Treap *root, int val) {
	auto p1 = splitVal(root, val);
	auto p2 = splitVal(p1[1], val + 1);
	Treap *cur = new Treap(val);
	return merge(p1[0], merge(cur, p2[1]));
}
