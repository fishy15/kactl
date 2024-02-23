/**
 * Author: fishy15
 * Date: 2024-02-23
 * License: Unknown
 * Source: Suffix automaton
 * Description: Builds suffix automaton for a string.
 * Each node corresponds to a class of substrings
 * which end at the same indices.
 * Time: O(n)
 * Status: stress-tested
 */
#pragma once

struct suffix_automaton {
    struct node {
        int len;
        int link;
        ll cnt;
        array<int, 26> nxt;
        node() : len{0}, link{-1}, cnt{1} {
            nxt.fill(-1);
        }
    };

    int root;
    int last;

    suffix_automaton() {
        root = last = new_node();
        buf[root].cnt = 0;
    }

    suffix_automaton(const string &s) : suffix_automaton{} {
        for (auto c : s) {
            add_char(c);
        }
        compute_counts();
    }

    void add_char(char nxt_char) {
        auto c = nxt_char - 'a';
        auto cur = new_node();
        buf[cur].len = buf[last].len + 1;

        auto p = last;
        while (p != -1 && buf[p].nxt[c] == -1) {
            buf[p].nxt[c] = cur;
            p = buf[p].link;
        }

        if (p == -1) {
            buf[cur].link = 0;
        } else {
            auto q = buf[p].nxt[c];
            if (buf[p].len + 1 == buf[q].len) {
                buf[cur].link = q;
            } else {
                auto clone = new_node(buf[q]);
                buf[clone].len = buf[p].len + 1;
                buf[clone].cnt = 0;
                while (p != -1 && buf[p].nxt[c] == q) {
                    buf[p].nxt[c] = clone;
                    p = buf[p].link;
                }
                buf[q].link = buf[cur].link = clone;
            }
        }
        
        last = cur;
    }

    void compute_counts() {
        vector<int> idx(buf.size());
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [this](int i, int j) { return buf[i].len > buf[j].len; });
        for (auto i : idx) {
            if (buf[i].link != -1) {
                buf[buf[i].link].cnt += buf[i].cnt;
            }
        }

        // dont care about empty string
        buf[root].cnt = 0;
    }

    vector<node> buf;
    template<typename ...Args>
    int new_node(Args ...args) {
        buf.emplace_back(args...);
        return buf.size() - 1;
    }
};
