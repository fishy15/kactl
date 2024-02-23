/**
 * Author: cp-algos
 * Date: 2024-02-23
 * Source: Unknown
 * Description: DP must be in the form 
 * dp(i, j) = min[dp(i, k) + dp(k + 1, j) + C(i, j)]
 * such that opt(i, j - 1) <= opt(i, j) <= opt(i + 1, j).
 * True if for a <= b <= c <= d, then C(b, c) <= C(a, d)
 * and C(a, c) + C(b, d) <= C(a, d) + C(b, c).
 * License: Unknown
 * Time: O(n^2)
 * Status: not tested
 */
#pragma once

int solve() {
    int N;
    ... // read N and input
    int dp[N][N], opt[N][N];

    auto C = [&](int i, int j) {
        ... // Implement cost function C.
    };

    for (int i = 0; i < N; i++) {
        opt[i][i] = i;
        ... // Initialize dp[i][i] according to the problem
    }

    for (int i = N-2; i >= 0; i--) {
        for (int j = i+1; j < N; j++) {
            int mn = INT_MAX;
            int cost = C(i, j);
            for (int k = opt[i][j-1]; k <= min(j-1, opt[i+1][j]); k++) {
                if (mn >= dp[i][k] + dp[k+1][j] + cost) {
                    opt[i][j] = k; 
                    mn = dp[i][k] + dp[k+1][j] + cost; 
                }
            }
            dp[i][j] = mn; 
        }
    }

    return dp[0][N-1];
}