/**
 * Author: cp-algos
 * Date: 2024-02-23
 * Source: Unknown
 * Description: DP must be in the form 
 * dp(i, j) = min_k(dp(i - 1, k - 1) + C(k, j))
 * such that opt(i, j) <= opt(i, j + 1).
 * True if quadrangle identity holds.
 * License: Unknown
 * Time: O(n log n)
 * Status: not tested
 */

template<class C>
ll solve(int n, int k, C c) {
	vector<ll> dp(n), nxt(n);
	auto comp = [&](auto &&self, int l, int r, int optl, int optr) -> void {
		if (l > r) return;
		int m = (l + r) / 2;
		auto best = pair{LLONG_MAX, -1};
		for (int i = optl; i <= min(m, optr); i++) {
			best = min(best, {(i ? dp[i - 1] : 0) + c(i, m), i});
		}
		nxt[m] = best.first;
		int opt = best.second;
		self(self, l, m-1, optl, opt);
		self(self, m+1, r, opt, optr);
	};
	rep(i, 0, n) dp[i] = C(0, i);
	rep(i, 0, k) comp(comp, 0, n-1, 0, n-1), nxt = dp;
	return dp.back();
}
