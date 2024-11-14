/**
 * Author: fishy15
 * Date: 2024-02-23
 * Source: Unknown
 * Description: Centroid decomposition on tree
 * License: Unknown
 * Time: O(n log n)
 * Status: not tested
 */
#pragma once

struct CD {
	vector<vector<int>> adj;
	vector<int> size, vis;

	int dfs_size(int v, int p) {
		size[v] = 1;
		for (int e : adj[v]) {
			if (e != p && !vis[e]) {
				size[v] += dfs_size(e, v);
			}
		}
		return size[v];
	}

	int dfs_root(int v, int p, int n) {
		for (int e : adj[v]) {
			if (e != p && !vis[e] && 2 * size[e] > n) {
				return dfs_root(e, v, n);
			}
		}
		return v;
	}

	void centroid(int v, int p) {
		dfs_size(v, p);
		int c = dfs_root(v, p, size[v]);
		vis[c] = true;

		// do processing here
		// make sure to ignore visited nodes 

		for (int e : adj[c]) {
			if (!vis[e]) {
				centroid(e, c);
			}
		}
	}
};
