/**
 * Author: Simon Lindholm
 * Date: 2017-04-17
 * License: CC0
 * Source: folklore
 * Description: Finds all biconnected components in an undirected graph, and
 *  runs a callback for the edges in each. In a biconnected component there
 *  are at least two distinct paths between any two nodes. Note that a node can
 *  be in several components. An edge which is not in a component is a bridge,
 *  i.e., not part of any cycle.
 * Usage:
 *  int eid = 0; ed.resize(N);
 *  for each edge (a,b) {
 *    ed[a].emplace_back(b, eid);
 *    ed[b].emplace_back(a, eid++); }
 *  bicomps([\&](const vi\& edgelist) {...});
 * Time: O(E + V)
 * Status: tested during MIPT ICPC Workshop 2017
 */
#pragma once

template<class F>
void bicomps(vector<vector<pii>> &ed, F f) {
	vi num(sz(ed)), st;
	int t=0;
	auto dfs = [&](auto &&self, int at, int par) -> int {
		int me = num[at] = ++t, top = me;
		for (auto [y, e] : ed[at]) if (e != par) {
			if (num[y]) {
				top = min(top, num[y]);
				if (num[y] < me)
					st.pb(e);
			} else {
				int si = sz(st);
				int up = self(self, y, e);
				top = min(top, up);
				if (up == me) {
					st.pb(e);
					f(vi(st.begin() + si, st.end()));
					st.resize(si);
				}
				else if (up < me) st.pb(e);
				else { /* e is a bridge */ }
			}
		}
		return top;
	};
	rep(i,0,sz(ed)) if (!num[i]) dfs(dfs, i, -1);
}
