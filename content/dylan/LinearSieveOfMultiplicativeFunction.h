/**
 * Author: Dylan Smith
 * Date: 2024-11-13
 * License: CC0
 * Source: idk
 * Description: computes f(1) ... f(n) for multiplicative function f
 * Time: $O(n)$
 * Status: May or may not be tested
 */
#pragma once

vector<ll> sieve(int n, ll (*fp)(int, int)) {
	vector<bool> prime(n, 1);
	vector<int> primes;
	vector<int> cnt(n, 1), part(n, 1);
	vector<ll> f(n, 1);
	for (int i = 2; i < n; i++) {
		if (prime[i]) {
			primes.pb(i);
			f[i] = fp(i, 1);
		}
		for (int j = 0; j < sz(primes) && i * primes[j] < n; j++) {
			prime[i * primes[j]] = 0;
			if (!(i % primes[j])) {
				cnt[i * primes[j]] = cnt[i] + 1;
				part[i * primes[j]] = part[i];
				f[i * primes[j]] = fp(primes[j], cnt[i * primes[j]]) * f[part[i * primes[j]]];
				break;
			}
			part[i * primes[j]] = i;
			f[i * primes[j]] = f[i] * f[primes[j]];
		}
	}
	return f;
}
