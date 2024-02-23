/**
 * Author: cp-algos
 * Date: 2024-02-23
 * Source: Unknown
 * Description: 
 * License: Unknown
 * Time: "Tree" of all palindromic substrings (there are two roots).
 * Also has suffix links.
 * Status: not tested
 */
#pragma once

struct Node {
	int nxt[26], sufflink;
	ll len, cnt;
	vector<int> edges;
} tree[303030];

string s;
int suff, num;
ll ans = 0;

void add_letter(int pos) {
	int curr = suff, curr_len = 0;
	int letter = s[pos] - 'a';

	while (true) {
		curr_len = tree[curr].len;
		if (pos - 1 - curr_len > -1 && s[pos - 1 - curr_len] == s[pos]) break;
		curr = tree[curr].sufflink;
	}

	if (tree[curr].nxt[letter]) {
		suff = tree[curr].nxt[letter];
		tree[suff].cnt++;
		return;
	}

	suff = ++num;
	tree[num].len = tree[curr].len + 2;
	tree[num].cnt = 1;
	tree[curr].nxt[letter] = num;

	if (tree[num].len == 1) {
		tree[num].sufflink = 2;
		tree[2].edges.push_back(num);
		return;
	}

	while (true) {
		curr = tree[curr].sufflink;
		curr_len = tree[curr].len;
		if (pos - 1 - curr_len > -1 && s[pos - 1 - curr_len] == s[pos]) {
			tree[num].sufflink = tree[curr].nxt[letter];
			tree[tree[curr].nxt[letter]].edges.push_back(num);
			break;
		}
	}
}

void init() {
	num = 2, suff = 2;
	tree[1].len = -1, tree[1].sufflink = 1;
	tree[2].len = 0, tree[2].sufflink = 1;
	tree[1].edges.push_back(2);
}