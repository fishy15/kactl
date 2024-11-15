/**
 * Author: fishy15
 * Date: 2024-02-23
 * Source: Unknown
 * Description: Matrix
 * License: Unknown
 * Time: O(n^3) MM, * log(e) for power
 * Status: not tested
 */
#pragma once

#include "ModInt.h"

struct M {
	const static int n = 20;
	mi m[n][n]; 
	M operator*(const M &m2) {
		M res;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int a = 0; a < n; a++) {
					res[i][j] += m[i][a] * m2[a][j];
				}
			}
		}
		return res;
	}
	mi *operator[](const int x) { return m[x]; }
	const mi *operator[](const int x) const { return m[x]; }
	static M pow(M m, ll e) {
		M res = I();
		while (e > 0) {
			if (e & 1) res = res * m;
			m = m * m;
			e >>= 1;
		}
		return res;
	}
	static M I() {
		M m;
		for (int i = 0; i < n; i++) m[i][i] = 1;
		return m;
	}
};
