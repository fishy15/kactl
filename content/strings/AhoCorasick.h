/**
 * Author: Dylan Smith
 * Date: 2024-11-13
 * License: CC0
 * Source: idk
 * Description: Constructs Aho-Corasick automaton for given list of words
 * Time: Construction is $O(N)$, move() is amortized $O(N)$.
 * Status: Used in Yandex Semifinal 2024 Problem F
 */
#pragma once

struct AhoCorasick {
	struct Node {
		map<char, int> nxt;
		int lnk = 0, cnt = 0;
	};
	vector<Node> t;
	AhoCorasick(vector<string> words) {
		t.pb({});
		for (string s : words) {
			int cur = 0;
			for (char c : s) {
				if (!t[cur].nxt[c]) {
					t[cur].nxt[c] = sz(t);
					t.pb({});
				}
				cur = t[cur].nxt[c];
			}
			t[cur].cnt++;
		}
		queue<int> q; q.push(0);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			assert(0 <= u && u < sz(t));
			for (auto &p : t[u].nxt) {
				if (u) t[p.second].lnk = move(t[u].lnk, p.first);
				q.push(p.second);
			}
		}
	}
	int move(int u, int c) {
		if (t[u].nxt[c]) return t[u].nxt[c];
		return u == 0 ? 0 : t[u].nxt[c] = move(t[u].lnk, c);
	}
};
