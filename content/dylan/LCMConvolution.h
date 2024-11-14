/**
 * Author: Dylan Smith
 * Date: 2024-11-13
 * License: CC0
 * Source: idk
 * Description: LCM Convolution
 * Time: about $O(n \log(n))$
 * Status: Tested on https://judge.yosupo.jp/problem/lcm_convolution
 */
#pragma once

// 1-indexed
vector<ll> lcmMult(vector<ll> a, vector<ll> b) {
	vector<ll> l(sz(a), 0), r(sz(a), 0), c(sz(a), 0);
	for (int i = 1; i <= sz(a); i++)
		for (int j = i; j <= sz(a); j += i)
			l[j-1] += a[i-1], r[j-1] += b[i-1];
	for (int g = 1; g <= sz(a); g++) {
		c[g-1] += (l[g-1] % mod) * (r[g-1] % mod) % mod;
		c[g-1] = (c[g-1] % mod + mod) % mod;
		for (int i = g*2; i <= sz(a); i += g) c[i-1] -= c[g-1];
	}
	return c;
}
