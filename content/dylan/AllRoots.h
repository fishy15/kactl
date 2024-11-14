/**
 * Author: Dylan Smith
 * Date: 2024-11-13
 * License: CC0
 * Source: idk
 * Description: Tree rerooting template
 * promote() follows a parent edge of a subtree (from original node u and following original edge e)
 * merge() merges two subtrees that just had promote() called on
 * by default this computes the sum of distances from each node to all other nodes
 * Time: solve() is $O(N)$.
 * Status: Used with success
 */
#pragma once

namespace AllRoots {
	struct Edge { int u, v, cost; };
	struct Node {
		int cost;
		int cnt = 0; ll sum = 0, t = 0, sumT = 0;
		Node merge(Node o) {
			return {0, cnt + o.cnt, sum + o.sum, t + o.t, sumT + o.sumT};
		}
		Node promote(Node u, Edge e) {
			return {0, 1 + cnt, sum + (ll)(1 + cnt) * e.cost, u.cost + t, sumT + (u.cost + t) * e.cost};
		}
	};
	Edge rev(Edge e) { swap(e.u, e.v); return e; }
	static vector<Node> solve(vector<Node> nodes, vector<Edge> edges) {
		int N = sz(nodes);
		vector<vector<int>> adj(N);
		vector<Edge> par(N);
		for (Edge e : edges) {
			adj[e.u].pb(e.v);
			adj[e.v].pb(e.u);
		}
		queue<int> q; q.push(0);
		vector<int> srt, pos(N);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			pos[u] = sz(srt);
			srt.pb(u);
			for (int v : adj[u]) {
				adj[v].erase(find(all(adj[v]), u));
				q.push(v);
			}
		}
		for (Edge e : edges) {
			if (pos[e.u] < pos[e.v]) swap(e.u, e.v);
			par[e.u] = e;
		}
		reverse(all(srt));
		vector<Node> down(N);
		for (int u : srt) for (int v : adj[u])
			down[u] = down[u].merge(down[v].promote(nodes[v], par[v]));
		reverse(all(srt));
		vector<Node> up(N), res(N);
		for (int u : srt) {
			vector<Node> left(sz(adj[u])), right(sz(adj[u]));
			for (int i = 0; i < sz(adj[u]); i++) {
				int v = adj[u][i];
				left[i] = right[i] = down[v].promote(nodes[v], par[v]);
			}
			for (int i = 1; i < sz(adj[u]); i++)
				left[i] = left[i - 1].merge(left[i]);
			for (int i = sz(adj[u]) - 2; i >= 0; i--)
				right[i] = right[i].merge(right[i + 1]);
			Node p = up[u].promote(nodes[par[u].v], rev(par[u]));
			for (int i = 0; i < sz(adj[u]); i++) {
				int v = adj[u][i];
				if (u > 0) up[v] = up[v].merge(p);
				if (i > 0) up[v] = left[i - 1].merge(up[v]);
				if (i + 1 < sz(adj[u])) up[v] = up[v].merge(right[i + 1]);
			}
			res[u] = down[u];
			if (u > 0) res[u] = res[u].merge(p);
		}
		return res;
	}
}
