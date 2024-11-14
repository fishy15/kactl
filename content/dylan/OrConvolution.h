/**
 * Author: Dylan Smith
 * Date: 2024-11-13
 * License: CC0
 * Source: idk
 * Description: Bitwise OR Convolution and Bitwise AND Convolution
 * Time: $O(n \log(n))$
 * Status: Tested on https://judge.yosupo.jp/problem/bitwise_and_convolution
 */
#pragma once

void orfft(vector<ll> &v) {
	for (int j = bits - 1; j >= 0; j--)
		for (int i = 0; i < 1 << bits; i++, i += i & 1 << j)
			v[i ^ 1 << j] += v[i];
	for (int i = 0; i < 1 << bits; i++) v[i] %= mod;
}
void orifft(vector<ll> &v) {
	for (int j = 0; j < bits; j++)
		for (int i = 0; i < 1 << bits; i++, i += i & 1 << j)
			v[i ^ 1 << j] -= v[i];
	for (int i = 0; i < 1 << bits; i++) v[i] = (v[i] % mod + mod) % mod;
}
vector<ll> orMult(vector<ll> a, vector<ll> b) {
	orfft(a); orfft(b); vector<ll> c(1 << bits);
	for (int i = 0; i < 1 << bits; i++) c[i] = a[i] * b[i] % mod;
	orifft(c); return c;
}
vector<ll> andMult(vector<ll> a, vector<ll> b) {
	reverse(all(a)); reverse(all(b));
	vector<ll> c = orMult(a, b);
	reverse(all(c)); return c;
}
