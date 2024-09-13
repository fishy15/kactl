/**
 * Author: chilli, Andrew He, Adamant
 * Date: 2019-04-27
 * Description: Calculate the first $|a|$ coefficients of $a^{-1}$.
 * Time: $O(n \log n)$.
 */
#pragma once

#include "PolyBase.h"

poly modK(poly a, int k) { return {a.begin(), a.begin() + min(k, sz(a))}; }
poly inverse(poly A) {
	poly B = poly({num(1) / A[0]});
	while (sz(B) < sz(A))
		B = modK(B * (poly({num(2)}) - modK(A, 2*sz(B)) * B), 2 * sz(B));
	return modK(B, sz(A));
}
