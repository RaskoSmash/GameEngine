#include "renderShapes.h"
#include "sfwdraw.h"

void drawAABB(const aabb &a, unsigned TINT)
{
	sfw::drawLine(a.min().x, a.min().y, a.max().x, a.min().y, TINT); //Bottom
	sfw::drawLine(a.max().x, a.min().y, a.max().x, a.max().y, TINT); //Right
	sfw::drawLine(a.max().x, a.max().y, a.min().x, a.max().y, TINT); //Top
	sfw::drawLine(a.min().x, a.max().y, a.min().x, a.min().y, TINT); //Left
}

void drawPlane(const plane &a, unsigned TINT)
{
	float pWidth = 300;
	sfw::drawLine(a.p.x, a.p.y, a.p.x + (a.n.x * 20), a.p.y + (a.n.y * 20), TINT); //Normal
	sfw::drawLine(a.p.x + (pWidth * a.n.perp().x), a.p.y + (pWidth * a.n.perp().y), 
				  a.p.x - (pWidth * a.n.perp().x), a.p.y - (pWidth * a.n.perp().y), TINT); //plane
}

void drawRay(const ray &a, unsigned TINT)
{
	sfw::drawLine(a.p.x, a.p.y, a.p.x + (a.d.x * a.l), a.p.y + (a.d.y * a.l), TINT);
}

void drawCircle(const circle &a, unsigned TINT)
{
	sfw::drawCircle(a.p.x, a.p.y, a.r, 6, TINT);
}

void drawMatrix(const mat3 &a)
{
	vec2 &pos = a[2].xy;
	vec2 up = pos + a[1].xy;
	vec2 right = pos + a[0].xy;

	sfw::drawLine(pos.x, pos.y, right.x, right.y, RED);
	sfw::drawLine(pos.x, pos.y, up.x, up.y, GREEN);
}

void drawTransform(const Transform &t) 
{ 
	drawMatrix(t.getGlobalTransform() * mat3::scale({ 30,30 }));
}

void drawRigidbody(const Transform &t, const RigidBody &rb)
{
	vec2 pos = t.getPosition();
	vec2 acc = pos + rb.acceleration;
	vec2 vel = pos + rb.velocity;

	sfw::drawLine(pos.x, pos.y, acc.x, acc.y, CYAN);
	sfw::drawLine(pos.x, pos.y, vel.x, vel.y, YELLOW);
}

void drawCollider(const Transform &t, const Collider  &c)
{
	switch (c.shape)
	{
	case Collider::e_AABB:
		drawAABB(t.getGlobalTransform() * c.AABB, BLUE);
		break;
	case Collider::e_CIRCLE:
		drawCircle(t.getGlobalTransform() * c.Circle, RED);
		break;
	case Collider::e_RAY:
		drawRay(t.getGlobalTransform() * c.Ray, BLACK);
		break;
	case Collider::e_PLANE:
		drawPlane(t.getGlobalTransform() * c.Plane, GREEN);
		break;
	}
}