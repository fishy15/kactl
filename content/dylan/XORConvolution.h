/**
 * Author: Dylan Smith
 * Date: 2024-11-13
 * License: CC0
 * Source: idk
 * Description: Bitwise XOR Convolution
 * Time: $O(n \log(n))$
 * Status: Tested on https://judge.yosupo.jp/problem/bitwise_xor_convolution
 */
#pragma once

void xorfft(vector<ll> &v, bool inv = 0) {
	for (int k = 0; k < bits; k++) {
		for (int i = 0; i < 1 << bits; i++, i += i & 1 << k) {
			ll a = v[i], b = v[i ^ 1 << k];
			v[i] = a + b, v[i ^ 1 << k] = a - b;
		}
	}
	for (int i = 0; i < 1 << bits; i++) v[i] = (v[i] % mod + mod) % mod;
	if (inv) {
		ll n = 1; for (int i = 0; i < bits; i++) n = n * 2 % mod;
		n = mInv(n);
		for (int i = 0; i < 1 << bits; i++) v[i] = v[i] * n % mod;
	}
}
vector<ll> mult(vector<ll> a, vector<ll> b) {
	xorfft(a); xorfft(b); vector<ll> c(1 << bits);
	for (int i = 0; i < 1 << bits; i++) c[i] = a[i] * b[i] % mod;
	xorfft(c, 1); return c;
}
