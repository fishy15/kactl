/**
 * Author: Mark Wen
 * Date: 2024-11-13
 * License: CC0
 * Source: https://math.stackexchange.com/questions/2213165/find-shortest-distance-between-lines-in-3d/2217845#2217845
 * Description: returns closest two points from each 3D segment
 * Status: tested on Avoiding Asteroids
 */
#pragma once

#include "P3oint3D.h"

typedef Point3D<double> P3;
//returns closest two points from each 3d segment
pair<P3, P3> segmentDistance3d(P3 s1, P3 e1, P3 s2, P3 e2) {
	pair<P3, P3> res{s1, s2};
	auto check = [&res](P3 a, P3 b) {
		if((b-a).dist() < (res.second-res.first).dist())
			res = {a, b};
	};
	//check endpoint-endpoint
	check(s1, s2);
	check(s1, e2);
	check(e1, s2);
	check(e1, e2);

	P3 d1 = (e1-s1).unit();
	double t1Max = (e1-s1).dist();
	P3 d2 = (e2-s2).unit();
	double t2Max = (e2-s2).dist();
	//check endpoint-segment, dist from p to the line segment s + t*d
	auto pointLine = [&](P3 p, P3 s, P3 d, double tMax) {
		P3 v = p-s;
		double t = v.dot(d);
		if(0 <= t && t <= tMax)
			check(s+d*t, p);
	};
	pointLine(s1, s2, d2, t2Max);
	pointLine(e1, s2, d2, t2Max);
	pointLine(s2, s1, d1, t1Max);
	pointLine(e2, s1, d1, t1Max);
	
	//check segment-segment
	P3 n = d1.cross(d2);
	if(n.dist2() != 0) { //only check if not parallel; parallel case is handled by pointLine checks
		double t1 = (d2.cross(n)).dot(s2-s1)/n.dot(n);
		double t2 = (d1.cross(n)).dot(s2-s1)/n.dot(n);
		if(0 <= t1 && t1 <= t1Max && 0 <= t2 && t2 <= t2Max)
			check(s1+d1*t1, s2+d2*t2);
	}
	return res;
}
