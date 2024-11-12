/**
 * Author: cp-algos
 * Date: 2024-02-23
 * Source: Unknown
 * Description: Fast shortest path algo, negative edges ok
 * License: Unknown
 * Time: O(n) usually, but exponential worst case
 * Status: not tested
 */
#pragma once

constexpr int INF = 1e9;
pair<vi, vi> shortest_paths(int src, vector<vector<pii>> &adj) {
	int n=sz(adj);
	vi d(n, INF), p(n, -1), m(n, 2);
	d[src]=0;
	deque<int> q;
	while (!q.empty()) {
		int u = q.front(); q.pop_front();
		m[u] = 0;
		for (auto [v, w] : adj[u])
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				p[v] = u;
				if (m[v] == 2) {
					m[v] = 1;
					q.push_back(v);
				} else if (m[v] == 0) {
					m[v] = 1;
					q.push_front(v);
				}
			}
	}
	return {d, p};
}
