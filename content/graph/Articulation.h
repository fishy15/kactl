/**
 * Author: cp-algos
 * Date: 2024-02-23
 * Source: Unknown
 * Description: Finds articulation points (removal separates graph)
 * License: Unknown
 * Time: O(n + m)
 * Status: tested on CSES
 */
#pragma once

vector<bool> cutpoints(const vector<vi> &adj) {
	int timer=0, n=sz(adj);
	vi tin(n,-1), low(n,-1);
	vector<bool> vis(n);
	vector<bool> iscut(n);
	auto dfs = [&](auto &&self, int v, int p) -> void {
		vis[v] = true;
		tin[v] = low[v] = timer++;
		int ch = 0;
		for (int to : adj[v]) {
			if (to == p) continue;
			if (vis[to])
				low[v] = min(low[v], tin[to]);
			else {
				self(self, to, v);
				low[v] = min(low[v], low[to]);
				if (low[to] >= tin[v] && p!=-1) iscut[v]=1;
				++ch;
			}
		}
		if(p == -1 && ch > 1) iscut[v]=1;
	};
	rep(i,0,n) if (!vis[i]) dfs(dfs, i, -1);
	return iscut;
}
