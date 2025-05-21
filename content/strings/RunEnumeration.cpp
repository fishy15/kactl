/**
 * Author: Dylan Smith
 * Date: 2025-05-19
 * License: CC0
 * Source: ko_osaga blog I think
 * Description: Returns tuples (p, l, r), representing the run [l, r) with period p
 * Time: O(n \log n)
 * Status: Tested on https://judge.yosupo.jp/problem/runenumerate
 */
#pragma once

struct LCP {
    SuffixArray sa;
    vector<int> pos;
    RMQ<int> rmq;
    LCP(string s) : sa(s), rmq(sa.lcp) {
        pos = vector<int>(sz(s) + 1);
        rep(i, 0, sz(s) + 1) pos[sa.sa[i]] = i;
    }
    int lcp(int i, int j) {
        if (i == j) return sz(pos) - i;
        int l = pos[i], r = pos[j];
        if (l > r) swap(l, r);
        return rmq.query(l+1, r+1);
    }
};

vector<vector<int>> run_enumerate(string s) {
    string sI = s;
    for (char &c : sI) c = 127 - c;
    set<vector<int>> runs;
    auto part = [&](string s) {
        string sR = s; reverse(all(sR));
        LCP lcp(s), lcpR(sR);
        vector<int> suf = lcp.sa.sa;
        vector<int> prefix(sz(s));
        set<int> st; st.insert(sz(s));
        rep(i, 1, sz(s)+1) {
        	prefix[suf[i]] = *st.lower_bound(suf[i]) - suf[i];
            st.insert(suf[i]);
        }
        rep(i, 0, sz(s)) {
        	int j = i + prefix[i];
            int k = j + (j == sz(s) ? 0 : lcp.lcp(i, j));
            int l = i - (i == 0 ? 0 : lcpR.lcp(sz(s) - j, sz(s) - i));
            if (k - l >= 2 * (j - i)) runs.insert({j - i, l, k});
        }
    };
    part(s); part(sI);
    vector<vector<int>> res;
    for (auto &v : runs) res.pb(v);
    return res;
}
