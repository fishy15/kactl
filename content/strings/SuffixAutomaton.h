/**
 * Author: Dylan Smith
 * Date: 2024-11-13
 * License: CC0
 * Source: CP-Algorithms (probably)
 * Description: Constructs a suffix automaton on string s
 * cnt() constructs an array of equivalence class sizes
 * first() constructs an array of first occurences for each node
 * Time: All functions are $O(N)$.
 * Status: Tested on most CSES string problems
 */
#pragma once

struct SuffixAutomaton {
	struct Node {
		int len = 0, lnk = 0;
		int nxt[26];
	};
	string s;
	vector<Node> t; int last = 0;
	SuffixAutomaton(string s = "") {
		t.pb({0, -1, {}});
		for (char c : s) add(c);
	}
	void add(char c) { s += c; c -= 'a'; 
		int u = last; int v = last = sz(t);
		t.pb({t[u].len + 1, 0, {}});
		while (u >= 0 && !t[u].nxt[c])
			t[u].nxt[c] = v, u = t[u].lnk;
		if (u == -1) return;
		int q = t[u].nxt[c];
		if (t[u].len + 1 == t[q].len)
			{ t[v].lnk = q; return; }
		int cpy = sz(t); t.pb(t[q]);
		t[cpy].len = t[u].len + 1;
		while (u >= 0 && t[u].nxt[c] == q)
			t[u].nxt[c] = cpy, u = t[u].lnk;
		t[v].lnk = t[q].lnk = cpy;
	}
	vector<int> cnt() {
		vector<int> res(sz(t), 0);
		int cur = 0;
		for (char c : s)
			res[cur = t[cur].nxt[c - 'a']]++;
		vector<pair<int, int>> srt;
		for (int i = 1; i < sz(t); i++)
			srt.pb({-t[i].len, i});
		sort(all(srt));
		for (auto &p : srt)
			res[t[p.second].lnk] += res[p.second];
		return res;
	}
	vector<int> first() {
		vector<int> res(sz(t), sz(s));
		int cur = 0;
		for (int i = 0; i < sz(s); i++) {
			cur = t[cur].nxt[s[i] - 'a'];
			res[cur] = min(res[cur], i);
		}
		vector<pair<int, int>> srt;
		for (int i = 1; i < sz(t); i++)
			srt.pb({-t[i].len, i});
		sort(all(srt));
		for (auto &p : srt)
			res[t[p.second].lnk] = min(res[t[p.second].lnk], res[p.second]);
		return res;
	}
};
