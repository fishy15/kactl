/**
 * Author: Dylan Smith
 * Date: 2024-11-11
 * License: Unknown
 * Source: Suffix automaton
 * Description: Builds suffix automaton for a string.
 * Each node corresponds to a class of substrings
 * which end at the same indices.
 * Time: O(n)
 * Status: tested on String Matching (CSES)
 */
#pragma once

struct SuffixAutomaton {
    struct Node {
        int len = 0, lnk = 0;
        int nxt[26];
    };
    string s;
    vector<Node> t; int last = 0;
    SuffixAutomaton(string _s = "") {
        t.pb({0, -1, {}});
        for (char c : _s) add(c);
    }
    void add(int c) { s += (char) c; c -= 'a'; 
        int u = last; int v = last = sz(t);
        t.pb({t[u].len + 1, 0, {}});
        while (u >= 0 && !t[u].nxt[c])
            t[u].nxt[c] = v, u = t[u].lnk;
        if (u == -1) return;
        int q = t[u].nxt[c];
        if (t[u].len + 1 == t[q].len)
            { t[v].lnk = q; return; }
        int cpy = sz(t); t.pb(t[q]);
        t[cpy].len = t[u].len + 1;
        while (u >= 0 && t[u].nxt[c] == q)
            t[u].nxt[c] = cpy, u = t[u].lnk;
        t[v].lnk = t[q].lnk = cpy;
    }
    vi cnt() {
        vi res(sz(t), 0);
        int cur = 0;
        for (char c : s)
            res[cur = t[cur].nxt[c - 'a']]++;
        vector<pii> srt;
        rep(i, 1, sz(t))
            srt.pb({-t[i].len, i});
        sort(all(srt));
        for (auto &p : srt)
            res[t[p.second].lnk] += res[p.second];
        return res;
    }
    vi first() {
        vi res(sz(t), sz(s));
        int cur = 0;
        for (int i = 0; i < sz(s); i++) {
            cur = t[cur].nxt[s[i] - 'a'];
            res[cur] = min(res[cur], i);
        }
        vector<pii> srt;
        rep(i, 1, sz(t))
            srt.pb({-t[i].len, i});
        sort(all(srt));
        for (auto &p : srt)
            res[t[p.second].lnk] = min(res[t[p.second].lnk], res[p.second]);
        return res;
    }
};
