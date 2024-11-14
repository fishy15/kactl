/**
 * Author: Dylan Smith
 * Date: 2024-11-13
 * License: CC0
 * Source: Ronit
 * Description: Subset Convolution
 * Time: $O(n \log^2(n))$
 * Status: Tested on https://judge.yosupo.jp/problem/subset_convolution
 */
#pragma once

struct yint {
	int B = 22; ll a[22];
	yint() { for (int i = 0; i < B; i++) a[i] = 0; }
	yint(ll k) { *this = yint(); a[0] = k; }
	yint& operator+=(yint o) {
		for (int i = 0; i < B; i++)
			if ((a[i] += o.a[i]) >= mod) a[i] -= mod;
		return *this; }
	yint& operator-=(yint o) {
		for (int i = 0; i < B; i++)
			if ((a[i] -= o.a[i]) < 0) a[i] += mod;
		return *this; }
	yint& operator*=(int k) {
		for (int i = 0; i < B; i++)
			a[i] = a[i] * k % mod;
		return *this; }
	yint& operator*=(yint o) {
		ll a2[22]; for (int i = 0; i < B; i++) a2[i] = 0;
		for (int i = 0; i < B; i++) for (int j = 0; i + j < B; j++) {
			a2[i + j] += a[i] * o.a[j] % mod;
			if (a2[i + j] >= mod) a2[i + j] -= mod; }
		swap(a, a2); return *this; }
	yint& operator-() {
		for (int i = 0; i < B; i++)
			if ((a[i] = -a[i]) < 0) a[i] += mod;
		return *this; }
	yint& shiftY(int k) {
		if (k > 0) {
			for (int i = B-1; i - k >= 0; i--) a[i] = a[i - k];
			for (int i = 0; i < k; i++) a[i] = 0;
		} else { k = -k;
			for (int i = 0; i + k < B; i++) a[i] = a[i + k];
			for (int i = B - k; i < B; i++) a[i] = 0;
		} return *this; }
	yint& multY() {
		for (int i = B-1; i > 0; i--) a[i] = a[i - 1];
		a[0] = 0; return *this; }
	yint& divY() {
		for (int i = 0; i < B-1; i++) a[i] = a[i + 1];
		a[B-1] = 0; return *this; }
	friend yint operator+(yint a, yint b) { return a += b; }
	friend yint operator-(yint a, yint b) { return a -= b; }
	friend yint operator*(yint a, yint b) { return a *= b; }
};

void subsetfft(vector<yint> &v) {
	for (int i = 0; i < 1 << bits; i++) v[i].shiftY(__builtin_popcount(i));
	for (int j = 0; j < bits; j++) {
		for (int i = 0; i < 1 << bits; i++, i += i & 1 << j) {
			yint a = v[i], by = v[i ^ 1 << j];
			v[i] = a - by; v[i ^ 1 << j] = a + by;
		}
	}
}
void subsetifft(vector<yint> &v) {
	for (int j = 0; j < bits; j++) {
		for (int i = 0; i < 1 << bits; i++, i += i & 1 << j) {
			yint a = v[i], b = v[i ^ 1 << j];
			v[i] = a + b; v[i ^ 1 << j] = (b - a);
		}
	}
	for (int i = 0; i < 1 << bits; i++) v[i].shiftY(-__builtin_popcount(i));
	ll p = 1; for (int j = 0; j < bits; j++) p = p * 2 % mod; p = mInv(p);
	for (int i = 0; i < 1 << bits; i++) v[i] *= p;
}
vector<ll> subsetMult(vector<ll> a, vector<ll> b) {
	vector<yint> aY(1 << bits), bY(1 << bits), cY(1 << bits);
	for (int i = 0; i < 1 << bits; i++) aY[i] = yint(a[i]), bY[i] = yint(b[i]);
	subsetfft(aY); subsetfft(bY);
	for (int i = 0; i < 1 << bits; i++) cY[i] = aY[i] * bY[i];
	subsetifft(cY);
	vector<ll> c(1 << bits);
	for (int i = 0; i < 1 << bits; i++) c[i] = cY[i].a[0];
	return c;
}
