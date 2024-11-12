/**
 * Author: cp-algos
 * Date: 2024-02-23
 * Source: Unknown
 * Description: 
 * License: Unknown
 * Time: "Tree" of all palindromic substrings (there are two roots).
 * Also has suffix links.
 * Status: not tested
 */
#pragma once

struct eertree {
    struct node {
        array<int, 26> nxt;
        int sufflink, len, cnt;
        vector<int> edges;
    };

    string s;
    vector<node> tree;
    int suff, num;

    eertree(const string &_s) : s(_s), tree(sz(s)+2), suff(2), num(2)  {
        tree[1].len = -1, tree[1].sufflink = 1;
        tree[2].len = 0, tree[2].sufflink = 1;
        tree[1].edges.pb(2);
        rep(i, 0, sz(s)) add(i);
    }

    void add(int pos) {
        int cur = suff, cur_len = 0;
        char c = s[pos];

        while (true) {
            cur_len = tree[cur].len;
            if (pos - 1 - cur_len > -1 && s[pos - 1 - cur_len] == s[pos]) break;
            cur = tree[cur].sufflink;
        }

        if (tree[cur].nxt[c]) {
            suff = tree[cur].nxt[c];
            tree[suff].cnt++;
            return;
        }

        suff = ++num;
        tree[num].len = tree[cur].len + 2;
        tree[num].cnt = 1;
        tree[cur].nxt[c] = num;

        if (tree[num].len == 1) {
            tree[num].sufflink = 2;
            tree[2].edges.pb(num);
            return;
        }

        while (true) {
            cur = tree[cur].sufflink;
            cur_len = tree[cur].len;
            if (pos - 1 - cur_len > -1 && s[pos - 1 - cur_len] == s[pos]) {
                tree[num].sufflink = tree[cur].nxt[c];
                tree[tree[cur].nxt[c]].edges.pb(num);
                break;
            }
        }
    }
};
