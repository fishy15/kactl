/**
 * Author: Dylan Smith
 * Date: 2024-11-13
 * License: CC0
 * Source: idk
 * Description: Solves Ax + By = C, outputs a solution to x and y, outputs step size to dx and dy
 * Time: $O(fast)$
 * Status: Used successfully, but the sign of dx and dy is sometimes wrong
 */
#pragma once

bool diophantine(ll A, ll B, ll C, ll &x, ll &y, ll &dx, ll &dy) {
	ll g = exGCD(abs(A), abs(B), x, y);
	if (C % g != 0) return false;
	x *= C / g; y *= C / g;
	if (A < 0) x = -x;
	if (B < 0) y = -y;
	dx = B / g; dy = A / g;
	if (B < 0) dx = -dx;
	if (A < 0) dy = -dy;
	return true;
}
