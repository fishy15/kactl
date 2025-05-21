/**
 * Author: Dylan Smith
 * Date: 2025-05-19
 * License: CC0
 * Source: CP-Algorithms probably
 * Description: Returns a list of starting indices of the strings in the Lyndon factorization of s
 * Time: O(n)
 * Status: Tested on https://judge.yosupo.jp/problem/lyndon_factorization
 */
#pragma once

vi duval(string s) {
	int i = 0;
	vi res;
	while (i < sz(s)) {
		int j = i, k = i + 1;
		while (k < sz(s) && s[k] >= s[j]) {
			if (s[k] > s[j]) j = i;
			else j++;
			k++;
		}
		while (i <= j) res.pb(i), i += k - j;
	}
	return res;
}
