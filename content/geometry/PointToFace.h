/**
 * Author: Aaryan Prakash
 * Date: 2024-11-13
 * License: CC0
 * Source: self
 * Description: Finds the distance between a point and a 3d hull face
 * Status: tested on Worm in Apple
 */
#pragma once

#include "Point3D.h"
#include "3dHull.h"

typedef Point3D<double> P3;
double pointToFace(P3 p, F f) {
	auto dir = f.q.unit() * -1;
	auto vec = p - pts[f.a];
	return vec.dot(dir);
}
