/**
 * Author: Dylan Smith
 * Date: 2024-11-13
 * License: CC0
 * Source: idk
 * Description: Range K-th Smallest
 * Time: $O(n \log^2(n))$ I think
 * Status: Tested on https://judge.yosupo.jp/problem/range_kth_smallest
 */
#pragma once

struct WaveletTree {
	struct Node {
		vector<int> a, b;
		int l = -1, r = -1;
		bool leaf = 0;
	};
	int bits = 30;
	vector<int> arr;
	vector<Node> tree = {{}};
	void construct(int u, int lo, int hi) {
		if (lo == hi) { tree[u].leaf = 1; return; }
		int l = sz(tree); tree.pb({});
		int r = sz(tree); tree.pb({});
		tree[u].l = l; tree[u].r = r;
		int mid = (lo + hi) / 2;
		int pre = 0;
		for (int i = 0; i < sz(tree[u].a); i++) {
			if (arr[tree[u].a[i]] <= mid) {
				tree[l].a.pb(tree[u].a[i]);
				pre++;
			} else tree[r].a.pb(tree[u].a[i]);
			tree[u].b.pb(pre);
		}
		if (!tree[l].a.empty()) construct(l, lo, mid);
		if (!tree[r].a.empty()) construct(r, mid + 1, hi);
	}
	WaveletTree(vector<int> a) : arr(a) {
		for (int i = 0; i < sz(arr); i++) tree[0].a.pb(i);
		construct(0, 0, (1 << bits) - 1);
	}
	int query(int l, int r, int k, int u = 0) {
		if (u == -1) return 0;
		int lp = lb(tree[u].a, l), rp = lb(tree[u].a, r + 1) - 1;
		if (tree[u].leaf) return tree[u].a[lp + k - 1];
		int n = tree[u].b[rp] - (lp == 0 ? 0 : tree[u].b[lp - 1]);
		if (n >= k) return query(l, r, k, tree[u].l);
		return query(l, r, k - n, tree[u].r);
	}
};
