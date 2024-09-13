/**
 * Author: Kuroni
 * Date: 2023-10-13
 * Source: https://arxiv.org/abs/2008.08822
 * Description: Calculate $[x^k]\frac{p(x)}{q(x)}$.
 * Time: $O(n \log n \log k)$.
 * Status: Tested on library-checker: https://judge.yosupo.jp/submission/166193
 */
#pragma once
#include "PolyBase.h"

num BostanMori(poly p, poly q, ll k) {
	if (k == 0) return p[0] / q[0];
	poly nq = q;
	for (int i = 1; i < sz(nq); i += 2) nq[i] = num(0) - nq[i];
	poly u = p * nq, v = q * nq;
	poly nu, nv;
	for (int i = k % 2; i < sz(u); i += 2) nu.push_back(u[i]);
	for (int i = 0; i < sz(v); i += 2) nv.push_back(v[i]);
	return BostanMori(nu, nv, k / 2);
};
