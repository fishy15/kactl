/**
 * Author: Riley Borgard
 * Date: 2021-01-01
 * License: CC0
 * Source: folklore
 * Description: Online queue-like deletion from a data structure supporting stack-like deletion
 * Time: $O(T(n) log(n))$
 */
#pragma once

struct update {
    bool type;
    update() { type = 0; }
};
template<typename D, typename U>
struct noam : public D {
    vector<U> s;
    void push(const U &u) { D::push(u); s.push_back(u); }
    void pop() {
        auto i = s.end(); int c = 0;
        do {
            c += (--i)->type ? 1 : -1; D::pop();
        } while (c < 0 && i != begin(s));
        auto j = stable_partition(i, s.end(), [](auto &x) { return !x.type; });
        if (i == begin(s)) {
            reverse(i, j);
            for_each(i, j, [](auto &x) { x.type = 1; });
        }
        s.pop_back();
        while (i != s.end()) D::push(*i), i++;
    }
};
