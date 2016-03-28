#include "Curves.h"

vec2 Bezier(vec2 a_A, vec2 a_B, vec2 a_C, vec2 a_D, float a_t)
{
	//vec2 mid1 = interp(a_A, a_B, a_t);
	//vec2 mid2 = interp(a_B, a_C, a_t);

	//return interp(mid1, mid2, a_t);

	vec2 ab, bc, cd, abbc, bccd;
	ab = interp(a_A, a_B, a_t);
	bc = interp(a_B, a_C, a_t);
	cd = interp(a_C, a_D, a_t);
	abbc = interp(ab, bc, a_t);
	bccd = interp(bc, cd, a_t);
	return interp(abbc, bccd, a_t);
}

vec2 Hermite(vec2 point1, vec2 point2, vec2 tangent1, vec2 tangent2, float t)
{
	float tsq = t * t;
	float tcub = tsq * t;
	float h00 = 2 * tcub - 3 * tsq + 1;
	float h01 = -2 * tcub + 3 * tsq;
	float h10 = tcub - 2 * tsq + t;
	float h11 = tcub - tsq;

	vec2 point = h00 * point1 + h10 * tangent1 + h01 * point2 + h11 * tangent2;
	return point;
}
