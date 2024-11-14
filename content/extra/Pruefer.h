/**
 * Author: cp-algos
 * Date: 2024-02-23
 * Source: Unknown
 * Description: Helps construct random tree
 * Choose random n-2 length array, values [0, n-1]
 * License: Unknown
 * Time: O(n)
 * Status: not tested
 */
#pragma once

vector<pii> pruefer_decode(const vi &code) {
	int n = sz(code) + 2;
	vi degree(n, 1);
	for (int i : code)
		degree[i]++;

	set<int> leaves;
	rep(i, 0, n)
		if (degree[i] == 1)
			leaves.insert(i);

	vector<pii> edges;
	for (int v : code) {
		int leaf = *leaves.begin();
		leaves.erase(leaves.begin());

		edges.emplace_back(leaf, v);
		if (--degree[v] == 1)
			leaves.insert(v);
	}
	edges.emplace_back(*leaves.begin(), n-1);
	return edges;
}
