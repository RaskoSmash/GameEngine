#pragma once
#include "MathLibrary\MathLib.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Collider.h"

void drawAABB(const aabb &a, unsigned TINT);
void drawPlane(const plane &a, unsigned TINT);
void drawRay(const ray &a, unsigned TINT);
void drawCircle(const circle &a, unsigned TINT);

void drawTransform(const Transform &);
void drawRigidbody(const Transform &, const RigidBody &);
void drawCollider(const Transform &, const Collider &);

void drawMatrix(const mat3 &);