#pragma once
#include "vector2.h"

vec2 Bezier(vec2 a_A, vec2 a_b, vec2 a_C, vec2 a_D, float a_t);

vec2 Hermite(vec2 point1, vec2 point2, vec2 tangent1, vec2 tangent2, float t);