struct SuffixAutomaton {
	struct state {
		int len, link;
		map <char, int> transitions;
	};
	int n, last, sz; vector <state> states;
	vector <ll> dp;
	vector <bool> terminal;
	SuffixAutomaton(int _n) {
		n = _n, sz = 1, last = 0; terminal.resize(2 * n); dp.assign(2 * n, -1);
		states.resize(2 * n); states[0].len = 0, states[0].link = -1;
	}
	void extend(char c) {
		int cur = sz ++;
		states[cur].len = states[last].len + 1;
		int p;
		for(p = last; p != -1 && !states[p].transitions.count(c); p = states[p].link){
			states[p].transitions[c] = cur;
		}
		if(p == -1) states[cur].link = 0;
		else {
			int q = states[p].transitions[c];
			if(states[p].len + 1 == states[q].len) states[cur].link = q;
			else {
				int clone = sz ++;
				states[clone].len = states[p].len + 1;
				states[clone].transitions = states[q].transitions;
				states[clone].link = states[q].link;
				for(; p != -1 && states[p].transitions[c] == q; p = states[p].link) {
					states[p].transitions[c] = clone;
				}
				states[q].link = states[cur].link = clone;
			}
		}
		last = cur;
	}
	void markTerminals() {
		int p = last;
		while(p) {
			terminal[p] = true;
			p = states[p].link;
		}
	}
};
