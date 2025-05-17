/**
 * Author: Kuroni
 * Date: 2023-10-14
 * Source: me
 * Description: Minkowski sum of set of convex ccw polygons.
 * Time: $O(P \log N)$, where $P$ is number of points and $N$ is number of polygons.
 * Status: Tested on wf21:K, cf:87E.
 */
#pragma once

#include "Point.h"

typedef Point<ll> P;
vector<P> minkowskiSum(vector<vector<P>> hs) {
	auto cmp = [](P a, P b) {
		return make_pair(a.x < 0 || a.x == 0 && a.y < 0, a.y * (ll)b.x)
			< make_pair(b.x < 0 || b.x == 0 && b.y < 0, a.x * (ll)b.y);
	};
	typedef tuple<P, int, int> T;
	auto cmp_tup = [&cmp](T a, T b) {
		auto& [pa, ja, ia] = a;
		auto& [pb, jb, ib] = b;
		if (cmp(pa, pb)) return false;
		if (cmp(pb, pa)) return true;
		return make_pair(ja, ia) < make_pair(jb, ib);
	};
	priority_queue<T, vector<T>, decltype(cmp_tup)> pq(cmp_tup);
	P cur = P();
	int s = 0, t = 0;
	rep(i, 0, sz(hs)) {
		auto& v = hs[i];
		rotate(begin(v), min_element(all(v)), end(v));
		if (sz(v) > 1) pq.push({v[1] - v[0], 0, i}), s += sz(v);
		cur = cur + v[0];
	}
	vector<P> h(s + 1);
	for (h[t++] = cur; sz(pq);) {
		auto [p, j, i] = pq.top(); pq.pop();
		t -= (t >= 2 && !cmp(h[t - 1] - h[t - 2], p));
		h[t++] = (cur = cur + p);
		auto& v = hs[i];
		if (++j < sz(v)) pq.push({v[(j + 1) % sz(v)] - v[j], j, i});
	}
	return {h.begin(), h.begin() + t - (t >= 2 && h[0] == h[t - 1])};
}
