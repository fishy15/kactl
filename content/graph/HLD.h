/**
 * Author: Aaryan Prakash
 * Date: 2024-11-11
 * License: Unknown
 * Source: https://codeforces.com/blog/entry/53170, Benq
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 * edges such that the path from any leaf to the root contains at most $\log(n)$
 * light edges. Takes as input the full adjacency list. op edges being
 * true means that values are stored in the edges, as opposed to the nodes.
 * Time: $O(\log N)$
 * Status: Used before
 */
#pragma once

template<bool op_edges = false>
struct hld {
	vector<vi> adj;
	vi par, size, in, head, d;
	hld(int n) : adj(n), par(n), size(n), in(n), head(n), d(n) {}

	void add_edge(int u, int v) {
		adj[u].pb(v);
		adj[v].pb(u);
	}

	void dfs_size(int v = 0, int p = 0) {
		size[v] = 1;
		for (int &e : adj[v]) {
			if (e != p) {
				d[e] = d[v] + 1;
				par[e] = v;
				dfs_size(e, v);
				size[v] += size[e];
				if (size[e] > size[adj[v][0]] || adj[v][0] == p) swap(e, adj[v][0]);
			}
		}
	}

	void dfs_hld(int v = 0, int p = 0) {
		static int t = 0;
		in[v] = t++;
		for (int e : adj[v]) {
			if (e != p) {
				if (e == adj[v][0]) {
					head[e] = head[v];
				} else {
					head[e] = e;
				}
				dfs_hld(e, v);
			}
		}
	}

	template<typename F>
	void op_path(int x, int y, F op) {
		while (head[x] != head[y]) {
			if (d[head[x]] > d[head[y]]) swap(x, y);
			op(in[head[y]], in[y] + 1);
			y = par[head[y]];
		}
		if (d[x] > d[y]) swap(x, y);
		op(in[x] + (op_edges ? 1 : 0), in[y] + 1);
	}

	template<typename F>
	void op_subtree(int x, F op) { 
		op(in[x] + (op_edges ? 1 : 0), in[x] + size[x]);
	}
};
