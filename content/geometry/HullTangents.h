/**
 * Author: Kevin Wan
 * Date: 2024-08-12
 * License: unclear
 * Source: took it from cf
 * Description: Finds the two tangent vertices on the convex hull
 * to some point. Point must be outside. Appears to be left then
 * right.
 * Status: tested on WF 2016J
 */

#include "Point.h"

template<typename P, typename F>
int extremeVertex(const P& poly, F direction) {
  int n = sz(poly), l = 0, ls;
  auto vertexCmp = [&](int i, int j) {
	return sgn(direction(poly[j]).cross(poly[j] - poly[i])); };
  auto isExtreme = [&](int i, int& is) {
	return (is = vertexCmp((i+1)%n, i)) >= 0 && vertexCmp(i, (i+n-1)%n) < 0; };
  for (int r = isExtreme(0, ls) ? 1 : n; l + 1 < r;) {
	int m = (l + r) / 2, ms;
	if (isExtreme(m, ms)) return m;
	if (ls != ms ? ls < ms : ls == vertexCmp(l, m)) r = m;
	else l = m, ls = ms;
  }
  return l;
}

template<typename P>
pair<int, int> tangentsConvex(const P &point, const vector<P>& poly) {
  return {
	extremeVertex(poly, [&](const P& q) { return q - point; }),
	extremeVertex(poly, [&](const P& q) { return point - q; })};
}
