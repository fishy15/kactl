/**
 * Author: fishy15
 * Date: 2025-05-20
 * License: CC0
 * Source: me
 * Description: Range set and add lazy segtree
 * Time: O(\log N).
 * Status: Tested on https://qoj.ac/contest/1924/problem/10119.
 */
#pragma once

struct segtree {
#define lc 2*v
#define rc 2*v+1
#define m (l + r) / 2
	int n;
	vector<ll> st;
	vector<bool> toset;
	vector<ll> lazy;
	segtree(int _n) : n(_n), st(4 * n), toset(4 * n), lazy(4 * n) {}
	void push(int v, int l, int r) {
		if (toset[v]) {
			if (l != r) {
				toset[lc] = toset[rc] = true;
				lazy[lc] = lazy[v];
				lazy[rc] = lazy[v];
			}
			st[v] = lazy[v];
			toset[v] = false;
		}
	}
	void upd(int l, int r, ll val) { upd(1, 0, n-1, l, r, val); }
	void upd(int v, int l, int r, int x, int y, ll val) {
		push(v, l, r);
		if (r < x || y < l) return;
		if (x <= l && r <= y) {
			toset[v] = true;
			lazy[v] = val;
			push(v, l, r);
		} else {
			upd(lc, l, m, x, y, val);
			upd(rc, m+1, r, x, y, val);
			st[v] = max(st[lc], st[rc]);
		}
	}
	ll qry(int x, int y) { return qry(1, 0, n-1, x, y); }
	ll qry(int v, int l, int r, int x, int y) {
		push(v, l, r);
		if (r < x || y < l) return 0;
		if (x <= l && r <= y) {
			return st[v];
		} else {
			auto v1 = qry(lc, l, m, x, y);
			auto v2 = qry(rc, m+1, r, x, y);
			return max(v1, v2);
		}
	}
#undef lc
#undef rc
#undef m
};

