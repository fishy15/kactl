/**
 * Author: Dylan Smith
 * Date: 2024-11-13
 * License: CC0
 * Source: my head
 * Description: 2D BIT that is semi-offline (requires update positions ahead of time)
 * addUpdate() must be called ahead of time with all update positions
 * then query() and update() may be called arbitrarily
 * Time: Operations are $O(log^2(n))$
 * Status: Used on Library Checker successfully
 */
#pragma once

struct HalfCompressedBIT2D {
	int N;
	bool built = 0;
	vector<pair<int, int>> updates;
	HalfCompressedBIT2D(int N) : N(N) {}
	void addUpdate(int r, int c) {
		updates.pb({r, c});
	}
	vector<vector<int>> compress;
	vector<vector<ll>> tree;
	static bool cmp(pair<int, int> &a, pair<int, int> &b) {
		return a.second < b.second;
	}
	void build() {
		sort(all(updates), cmp);
		compress = vector<vector<int>>(N, {0});
		for (auto &p : updates)
			for (int rr = p.first; rr < sz(compress); rr += rr & -rr)
				compress[rr].pb(p.second);
		tree = vector<vector<ll>>(sz(compress));
		for (int i = 0; i < sz(compress); i++) {
			tree[i] = vector<ll>(sz(compress[i]), 0);
		}
		built = 1;
	}
	void update(int r, int c, int k) {
		if (!built) build();
		for (int rr = r; rr < sz(compress); rr += rr & -rr)
			for (int cc = lb(compress[rr], c); cc < sz(compress[rr]); cc += cc & -cc)
				tree[rr][cc] += k;
	}
	ll query(int r, int c) {
		if (!built) build();
		ll res = 0;
		for (int rr = r; rr; rr -= rr & -rr)
			for (int cc = lb(compress[rr], c + 1) - 1; cc; cc -= cc & -cc)
				res += tree[rr][cc];
		return res;
	}
};
