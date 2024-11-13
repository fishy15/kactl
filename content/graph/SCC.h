/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source: Czech graph algorithms book, by Demel. (Tarjan's algorithm)
 * Description: Finds strongly connected components in a
 * directed graph. If vertices $u, v$ belong to the same component,
 * we can reach $u$ from $v$ and vice versa.
 * Usage: scc(graph, [\&](vi\& v) { ... }) visits all components
 * in reverse topological order. comp[i] holds the component
 * index of a node (a component only has edges to components with
 * lower index). ncomps will contain the number of components.
 * Time: O(E + V)
 * Status: Bruteforce-tested for N <= 5
 */
#pragma once

template<class G, class F> vi scc(G& g, F f) {
	int n = sz(g);
    vi val(n, 0), comp(n, -1), z, cont;
    int t=0, ncomps=0;
    auto dfs = [&](auto &&self, int j) -> int {
        int low = val[j] = ++t, x; z.pb(j);
        for (auto e : g[j]) if (comp[e] < 0)
            low = min(low, val[e] ?: self(self,e,g,f));
        if (low == val[j]) {
            do {
                x = z.back(); z.pop_back();
                comp[x] = ncomps;
                cont.pb(x);
            } while (x != j);
            f(cont); cont.clear();
            ncomps++;
        }
        return val[j] = low;
    };
	rep(i,0,n) if (comp[i] < 0) dfs(i, g, f);
    return comp;
}
