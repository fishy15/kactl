#include "../utilities/template.h"
#include "../utilities/utils.h"

#include "../../content/graph/GlobalMinCut.h"
#include "../../content/graph/GomoryHu.h"
#include "../../content/graph/Dinic.h"


void test(int N, int mxFlow, int iters) {
	for (int it = 0; it < iters; it++) {
		int n = rand()%N+1;
		int m = rand()%(N*N);
		vector<Edge> edges;
		vector<vi> mat(n, vi(n));
		rep(it,0,m) {
			int i = rand() % n;
			int j = rand() % n;
			if (i == j) continue;
			int w = rand() % mxFlow;
			edges.push_back({i, j, w});
			mat[i][j] += w;
			mat[j][i] += w;
		}
		auto calc = [&](int s, int t) {
			Dinic flow(n);
			for (auto e : edges) {
				flow.addEdge(e.from, e.to, e.cap, e.cap);
			}
			return flow.calc(s, t);
		};
		vector<Edge> gomoryHuTree = gomoryHu(n, edges);
		vector<vector<array<int, 2>>> adj(n);
		for (auto e : gomoryHuTree) {
			adj[e.from].push_back({e.to, (int) e.cap});
			adj[e.to].push_back({e.from, (int) e.cap});
		}
		auto dfs = make_y_combinator([&](auto dfs, int start, int cur, int p, int mn) -> void {
			if (start != cur) {
				assert(mn == calc(start, cur));
			}
			for (auto i : adj[cur]) {
				if (i[0] != p)
					dfs(start, i[0], cur, min(mn, i[1]));
			}
		});
		dfs(0, 0, -1, INT_MAX);

		// Check that the lightest edge agrees with GlobalMinCut.
		if (n >= 2) {
			ll minCut = LLONG_MAX;
			for (auto e : gomoryHuTree) {
				minCut = min(minCut, e.cap);
			}
			auto mat2 = mat;
			auto pa = globalMinCut(mat2);
			assert(pa.first == minCut);
			vi inCut(n);
			assert(sz(pa.second) != 0);
			assert(sz(pa.second) != n);
			for (int x : pa.second) {
				assert(0 <= x && x < n);
				assert(!inCut[x]);
				inCut[x] = 1;
			}
			int cutw = 0;
			rep(i,0,n) rep(j,0,n) if (inCut[i] && !inCut[j]) {
				cutw += mat[i][j];
			}
			assert(pa.first == cutw);
		}
	}
}
signed main() {
	test(25, 5, 200);
	test(100, 1000, 5);
	test(100, 1, 20);
	test(5, 5, 20000);
	cout<<"Tests passed!"<<endl;
}
