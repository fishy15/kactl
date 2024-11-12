/**
 * Author: SYury, fishy15
 * Date: 2024-05-21
 * License: CC BY-SA
 * Source: https://cp-algorithms.com/geometry/minkowski.html
 * Description: Returns the set of all sums of points of two
 * convex polygons.
 * Status: tested on https://contest.ucup.ac/contest/1382/problem/7569
 * Time: O(n + m)
 */
#pragma once
#include "Point.h"

typedef Point<ll> P;
void reorder_polygon(vector<P> &p) {
    int pos = 0;
    for (int i = 1; i < sz(p); i++) {
        if (p[i].y < p[pos].y || (p[i].y == p[pos].y && p[i].x < p[pos].x))
            pos = i;
    }
    rotate(p.begin(), p.begin() + pos, p.end());
}

vector<P> minkowski(vector<P> p, vector<P> q) {
    reorder_polygon(p);
    reorder_polygon(q);

    p.pb(p[0]);
    p.pb(p[1]);
    q.pb(q[0]);
    q.pb(q[1]);

    vector<P> result;
    int i = 0, j = 0;
    while (i < sz(p) - 2 || j < sz(q) - 2) {
        result.pb(p[i] + q[j]);
        auto cross = (p[i + 1] - p[i]).cross(q[j + 1] - q[j]);
        if (cross >= 0 && i < sz(p) - 2) ++i;
        if (cross <= 0 && j < sz(q) - 2) ++j;
    }
    return result;
}
