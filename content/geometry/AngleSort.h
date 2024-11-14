/**
 * Author: Mark Wen
 * Date: 2024-11-11
 * License: Unknown
 * Source: https://codeforces.com/blog/entry/72815
 * Description: Sorts points radially across the origin.
 * To sort around a point, sort a-p and b-p.
 * Status: tested on https://codeforces.com/gym/104901/problem/M
 */

#pragma once

#include "Point.h"

template<class P>
void anglesort(vector<P> &v, P p=P(0, 0)) {
	sort(all(v), [p](P a, P b) {
		a = a - p, b = b - p;
		return a.half() == b.half() ? a.cross(b) > 0 : a.half() < b.half();
	});
}
