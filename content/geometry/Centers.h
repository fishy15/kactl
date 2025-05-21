/**
 * Author: zhtluo, fishy15
 * Date: 2025-05-20
 * Source: derived from https://github.com/zhtluo/cp-reference/blob/main/src/geometry/2d-geometry/triangle-center.cpp
 * Description: Common triangle centers
 * Time: fast
 * Status: untested
 */
#pragma once

#include "Point.h"

typedef Point<double> P;

P incenter(P a, P b, P c) {
    double p = (a - b).dist() + (b - c).dist() + (c - a).dist();
    return (a * (b - c).dist() + b * (c - a).dist() + c * (a - b).dist()) / p;
}

P circumcenter(P a, P b, P c) {
  P p = b - a, q = c - a,
        s(p.dist2() / 2, q.dist() / 2);
  return a + P(s.cross(P(p.y, q.y)), P(p.x, q.x).cross(s)) / p.cross(q);
}

P orthocenter(P a, P b, P c) {
  return a + b + c - circumcenter(a, b, c) * 2;
}
