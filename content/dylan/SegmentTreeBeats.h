/**
 * Author: Dylan Smith
 * Date: 2024-11-13
 * License: CC0
 * Source: no idea
 * Description: preset to allow range chmin, range chmax, and range add queries all at once
 * Time: All operations are $O(\log N)$.
 * Status: Used in Library Checker problem
 */
#pragma once

struct SegTreeBeats {
	struct Node {
		ll sum = 0, mx = LLONG_MIN, mx2 = LLONG_MIN, mxC = 0, mn = LLONG_MAX, mn2 = LLONG_MAX, mnC = 0;
	};
	struct Upd {
		ll chmin = LLONG_MAX, chmax = LLONG_MIN, add = 0;
	};
	void apply(Node &v, Upd &u, int l, int r) {
		if (v.mx > u.chmin) {
			v.sum -= (v.mx - u.chmin) * v.mxC;
			if (v.mx == v.mn) v.mn = u.chmin;
			if (v.mx == v.mn2) v.mn2 = u.chmin;
			if (v.mx == v.mx2) v.mx2 = u.chmin;
			v.mx = u.chmin;
		}
		if (v.mn < u.chmax) {
			v.sum += (u.chmax - v.mn) * v.mnC;
			if (v.mn == v.mx) v.mx = u.chmax;
			if (v.mn == v.mx2) v.mx2 = u.chmax;
			if (v.mn == v.mn2) v.mn2 = u.chmax;
			v.mn = u.chmax;
		}
		v.sum += u.add * (r - l + 1);
		v.mx += u.add;
		v.mx2 += u.add;
		v.mn += u.add;
		v.mn2 += u.add;
		v.mx2 = min(v.mx2, v.mx);
		v.mn2 = max(v.mn2, v.mn);
	}
	void combine(Upd &a, Upd &b) {
		if (b.chmin != LLONG_MAX) {
			a.chmin = min(a.chmin, b.chmin - a.add);
			a.chmax = min(a.chmax, b.chmin - a.add);
		}
		if (b.chmax != LLONG_MIN) {
			a.chmax = max(a.chmax, b.chmax - a.add);
			a.chmin = max(a.chmin, b.chmax - a.add);
		}
		a.add += b.add;
	}
	Node merge(Node &a, Node &b) {
		Node res;
		res.sum = a.sum + b.sum;
		vector<ll> mxSrt = {a.mx, a.mx2, b.mx, b.mx2};
		vector<ll> mnSrt = {a.mn, a.mn2, b.mn, b.mn2};
		sort(all(mxSrt)); reverse(all(mxSrt)); sort(all(mnSrt));
		res.mx = mxSrt[0];
		int i = 1;
		while (i < 3 && mxSrt[i - 1] == mxSrt[i]) i++;
		res.mx2 = mxSrt[i];
		res.mn = mnSrt[0];
		i = 1;
		while (i < 3 && mnSrt[i - 1] == mnSrt[i]) i++;
		res.mn2 = mnSrt[i];
		if (a.mx == b.mx) res.mxC = a.mxC + b.mxC;
		else if (a.mx > b.mx) res.mxC = a.mxC;
		else res.mxC = b.mxC;
		if (a.mn == b.mn) res.mnC = a.mnC + b.mnC;
		else if (a.mn < b.mn) res.mnC = a.mnC;
		else res.mnC = b.mnC;
		return res;
	}
	bool breakCondition(int L, int R, Upd k, int i, int l, int r) {
		if (r < L || R < l) return true;
		if (k.chmin != LLONG_MAX) return tree[i].mx <= k.chmin;
		if (k.chmax != LLONG_MIN) return tree[i].mn >= k.chmax;
		return false;
	}
	bool tagCondition(int L, int R, Upd k, int i, int l, int r) {
		if (!(L <= l && r <= R)) return false;
		if (k.chmin != LLONG_MAX) return tree[i].mx2 < k.chmin || tree[i].mx == tree[i].mx2;
		if (k.chmax != LLONG_MIN) return tree[i].mn2 > k.chmax || tree[i].mn == tree[i].mn2;
		return true;
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
	SegTreeBeats(vector<Node> arr) {
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
		if (breakCondition(L, R, k, i, l, r)) return;
		if (tagCondition(L, R, k, i, l, r)) { combine(upd[i], k); push(i, l, r); return; }
		updateRec(L, R, k, i * 2, l, (l + r) / 2);
		updateRec(L, R, k, i * 2 + 1, (l + r) / 2 + 1, r);
		tree[i] = merge(tree[i * 2], tree[i * 2 + 1]);
	}
	void rangeUpdate(int l, int r, Upd k) { updateRec(l, r, k, 1, 0, sz(tree) / 2 - 1); }
	Node queryRec(int L, int R, int i, int l, int r) {
		if (l > r) return {};
		push(i, l, r);
		if (breakCondition(L, R, {}, i, l, r)) return {};
		if (tagCondition(L, R, {}, i, l, r)) return tree[i];
		Node left = queryRec(L, R, i * 2, l, (l + r) / 2);
		Node right = queryRec(L, R, i * 2 + 1, (l + r) / 2 + 1, r);
		return merge(left, right);
	}
	Node rangeQuery(int l, int r) { return queryRec(l, r, 1, 0, sz(tree) / 2 - 1); }
};
