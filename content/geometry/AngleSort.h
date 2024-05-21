/**
 * Author: Alpha_Q
 * Date: 2024-05-21
 * License: Unknown
 * Source: https://codeforces.com/blog/entry/72815
 * Description: Sorts points radially across the origin.
 * To sort around a point, sort a-p and b-p.
 * Status: tested on https://codeforces.com/gym/104901/problem/M
 */

#pragma once

#include "Point.h"

bool up(P p) {
 	return p.y > 0 or (p.y == 0 and p.x >= 0);
}

sort(v.begin(), v.end(), [](P a, P b) {
 	return up(a) == up(b) ? a.x * b.y > a.y * b.x : up(a) < up(b);
});
