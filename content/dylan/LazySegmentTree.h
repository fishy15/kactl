/**
 * Author: Dylan Smith
 * Date: 2024-11-13
 * License: CC0
 * Source: idk
 * Description: Segment tree that performs lazy operations
 * The Node struct, Upd struct, apply(), combine(), and merge() may be customized
 * apply() should apply update u to node v, and l and r represent the range corresponding to node v
 * combine() should merge update b into update a
 * merge() should merge nodes a and b and return the result
 * by default this supports range addition, range set, range multiply, and range sum queries
 * Time: Construction is $O(N)$, queries and updates are all $O(\log N)$
 * Status: Used many times successfully
 */
#pragma once

struct SegTree {
	struct Node {
		ll sum = 0;
	};
	struct Upd {
		ll a = 1, b = 0;
	};
	void apply(Node &v, Upd &u, int l, int r) {
		v.sum = v.sum * u.a + u.b * (r - l + 1);
	}
	void combine(Upd &a, Upd &b) {
		a.b = a.b * b.a + b.b;
		a.a = a.a * b.a;
	}
	Node merge(Node &a, Node &b) {
		return {a.sum + b.sum};
	}
	vector<Node> tree; vector<Upd> upd;
	void push(int i, int l, int r) {
		apply(tree[i], upd[i], l, r);
		if (i * 2 < sz(tree)) {
			combine(upd[i * 2], upd[i]);
			combine(upd[i * 2 + 1], upd[i]);
		}
		upd[i] = {};
	}
	SegTree(vector<Node> arr) {
		int M = 1; while (M < sz(arr)) M <<= 1;
		tree = vector<Node>(M * 2);
		upd = vector<Upd>(M * 2);
		for (int i = 0; i < sz(arr); i++)
			tree[i + M] = arr[i];
		for (int i = M - 1; i > 0; i--)
			tree[i] = merge(tree[i * 2], tree[i * 2 + 1]);
	}
	void updateRec(int L, int R, Upd k, int i, int l, int r) {
		if (l > r) return;
		push(i, l, r);
		if (r < L || R < l) return;
		if (L <= l && r <= R) { combine(upd[i], k); push(i, l, r); return; }
		updateRec(L, R, k, i * 2, l, (l + r) / 2);
		updateRec(L, R, k, i * 2 + 1, (l + r) / 2 + 1, r);
		tree[i] = merge(tree[i * 2], tree[i * 2 + 1]);
	}
	void rangeUpdate(int l, int r, Upd k) { updateRec(l, r, k, 1, 0, sz(tree) / 2 - 1); }
	Node queryRec(int L, int R, int i, int l, int r) {
		if (l > r) return {};
		push(i, l, r);
		if (r < L || R < l) return {};
		if (L <= l && r <= R) return tree[i];
		Node left = queryRec(L, R, i * 2, l, (l + r) / 2);
		Node right = queryRec(L, R, i * 2 + 1, (l + r) / 2 + 1, r);
		return merge(left, right);
	}
	Node rangeQuery(int l, int r) { return queryRec(l, r, 1, 0, sz(tree) / 2 - 1); }
	/*int kthRec(int K, int i, int l, int r) {
		if (l > r) return {};
		push(i, l, r);
		if (tree[i].sum < K) return -1;
		if (l == r) return l;
		int m = kthRec(K, i * 2, l, (l + r) / 2);
		if (m == -1) return kthRec(K - tree[i * 2].sum, i * 2 + 1, (l + r) / 2 + 1, r);
		return m;
	}
	int kth(int K) { return kthRec(K, 1, 0, sz(tree) / 2 - 1); }*/
};
