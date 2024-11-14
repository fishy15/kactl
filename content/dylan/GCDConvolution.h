/**
 * Author: Dylan Smith
 * Date: 2024-11-13
 * License: CC0
 * Source: idk
 * Description: GCD Convolution
 * Time: ~ $O(n \log(n))$
 * Status: Tested on https://judge.yosupo.jp/problem/gcd_convolution
 */
#pragma once

// 1-indexed
vector<ll> gcdMult(vector<ll> a, vector<ll> b) {
	vector<ll> c(sz(a), 0);
	for (int g = sz(a); g >= 1; g--) {
		ll l = 0, r = 0;
		for (int i = g; i <= sz(a); i += g)
			l += a[i-1], r += b[i-1], c[g-1] -= c[i-1];
		c[g-1] += (l % mod) * (r % mod) % mod;
		c[g-1] = (c[g-1] % mod + mod) % mod;
	}
	return c;
}
