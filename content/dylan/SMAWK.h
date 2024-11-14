/**
 * Author: Dylan Smith
 * Date: 2024-11-13
 * License: CC0
 * Source: the SMAWK paper
 * Description: Outputs row minima of nxm totally monotone matrix
 * f(r, c1, c2) should output 1 if a[r][c1] <= a[r][c2]
 * Time: $O(n)$
 * Status: Used on Library Checker and Balatro
 */
#pragma once

template<typename F>
vector<int> smawk(F f, vector<int> rows, vector<int> cols) {
	vector<int> row_mins;
	if (sz(rows) <= 2 && sz(cols) <= 2) {
		for (int r : rows) {
			int mn = -1;
			for (int c : cols) {
				if (mn == -1 || f(r, c, mn)) mn = c;
			}
			row_mins.pb(mn);
		}
	} else if (sz(rows) < sz(cols)) {
		// Reduce
		vector<int> st;
		for (int j : cols) {
			while (!st.empty()) {
				if (f(rows[sz(st) - 1], j, st.back())) st.pop_back();
				else if (sz(st) == sz(rows)) break;
				else { st.push_back(j); break; }
			}
			if (st.empty()) st.pb(j);
		}
		row_mins = smawk(f, rows, st);
	} else {
		// Interpolate
		vector<int> half_rows;
		for (int i = 1; i < sz(rows); i += 2) half_rows.pb(rows[i]);
		vector<int> half_row_mins = smawk(f, half_rows, cols);
		vector<int> mn_index;
		for (int i = 0, j = 0; j < sz(cols); j++) {
			while (i < sz(half_row_mins) && cols[j] == half_row_mins[i]) {
				mn_index.pb(j);
				i++;
			}
		}
		for (int i = 0; i < sz(rows); i++) {
			if (i % 2) row_mins.pb(half_row_mins[i / 2]);
			else {
				int l = i == 0 ? 0 : mn_index[i / 2 - 1];
				int r = i == sz(rows) - 1 ? sz(cols) - 1 : mn_index[i / 2];
				int mn = cols[l];
				for (int j = l + 1; j <= r; j++) {
					if (f(rows[i], cols[j], mn)) mn = cols[j];
				}
				row_mins.pb(mn);
			}
		}
	}
	return row_mins;
}

// Min-plus Convolution (b must be convex)
vector<ll> min_plus(vector<ll> a, vector<ll> b) {
	int n = sz(a), m = sz(b);
	auto get = [&](int r, int c) { return a[c] + b[r - c]; };
	auto comp = [&](int r, int c1, int c2) {
		if (r - max(c1, c2) < 0) return c1 < c2;
		if (r - min(c1, c2) >= m) return c2 < c1;
		return get(r, c1) <= get(r, c2);
	};
	vector<int> rows, cols;
	for (int i = 0; i < n + m - 1; i++) rows.pb(i);
	for (int j = 0; j < n; j++) cols.pb(j);
	vector<int> row_mins = smawk(comp, rows, cols);
	vector<ll> res;
	for (int i = 0; i < n + m - 1; i++) res.pb(get(i, row_mins[i]));
	return res;
}

// Min-plus Convolution (b must be concave)
vector<ll> max_plus(vector<ll> a, vector<ll> b) {
	for (ll &i : a) i = -i;
	for (ll &i : b) i = -i;
	vector<ll> res = min_plus(a, b);
	for (ll &i : res) i = -i;
	return res;
}
