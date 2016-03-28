#include "BenEngine.h"


static Handle<Entity> makePlayer(vec2 pos);
static Handle<Entity> makeWall(vec2 pos, vec2 nor);

int main()
{

	auto &window = Window::instance();
	auto &input = Input::instance();
	auto &time = Time::instance();

	window.init();
	input.init();
	time.init();

	Asset::instance().loadTexture("Blue", "./Textures/BezierCircleFigure3.png");
	Asset::instance().loadTexture("Red", "./Textures/yCWYL_7W_400x400.jpeg");

	auto e = makeWall({0,300}, {1,0});
	auto p = makeWall({400,0}, {0,1});
	auto o = makeWall({800,300}, {-1,0});
	auto n = makeWall({400,600}, {0,-1});

	auto c = makePlayer({ 0,0 });

	auto r = Entity::make();
	r->collider = Collider::make();
	r->rigidbody = RigidBody::make();
	r->transform = Transform::make();
	r->health = Health::make();

	r->collider->shape = Collider::e_RAY;
	r->collider->Ray.d = {-.707106769f, -.707106769f };
	r->collider->Ray.l = 30;
	r->transform->setPosition({400,300});

	auto b = Entity::make();
	b->collider = Collider::make();
	b->rigidbody = RigidBody::make();
	b->transform = Transform::make();

	b->sprite = Sprite::make();
	b->health = Health::make();
//	b->lifecycle = Lifecycle::make();

	b->sprite->assetName = "Red";
	b->sprite->dimension = vec2{ 72,72 };

	b->collider->shape = Collider::e_AABB;
	b->collider->AABB.he = { 36,36 };
	b->transform->setPosition({0,0});

	RigidbodyDynamics rigidbodies;
	LifecycleSystem lifetimes;
	CollisionDetection collisioner;
	DynamicResolution dynamic;
	StaticResolution staticRe;
	PlayerControllerSystem controlsystem;
	RenderSystem render;
	HealthSystem healthsystem;
	StaminaSystem staminasystem;
	DebugDraw debug;

//	circle d = { { 400,100 }, 50 };

	mat4 id = mat4::identity();
	id *= id.translate({ 0,0, 0 });
	id *= id.scale({50,50,0});

	while (window.step())
	{

		input.step();
		time.step();

		controlsystem.step();


		rigidbodies.step();
		lifetimes.step();

		collisioner.step();
		dynamic.step();
		staticRe.step();
		render.step();
		debug.step();

		healthsystem.step();
		staminasystem.step();

		std::cout << c->health->curHealth << std::endl;
			
	}

	time.term();
	input.term();
	window.term();

	return 0;
}

static Handle<Entity> makePlayer(vec2 pos)
{
	auto e = Entity::make();
	e->collider = Collider::make();
	e->rigidbody = RigidBody::make();
	e->transform = Transform::make();
	e->controller = PlayerController::make();
	e->sprite = Sprite::make();
	e->stamina = Stamina::make();
	e->health = Health::make();

	e->sprite->assetName = "Blue";
	e->sprite->dimension = vec2{ 72,72 };

	e->collider->shape = Collider::e_CIRCLE;
	e->collider->Circle.r = 25;
	e->transform->setPosition(pos);

	return e;
}

static Handle<Entity> makeWall(vec2 pos, vec2 nor)
{
	auto e = Entity::make();
	e->collider = Collider::make();
	e->transform = Transform::make();
	e->collider->shape = Collider::e_PLANE;
	e->collider->Plane.n = nor;
	e->transform->setPosition(pos);

	return e;
}


//before game engine

//#include "sfwdraw.h"
//#include "MathLibrary\MathLib.h"
//#include "renderShapes.h"
//#include <iostream>
//#include <cassert>
//
//using std::cout;
//using std::endl;
//
//int main()
//{
//	circle c = { {0,0}, 25 };
//	aabb a = { { 200,160 }, { 60,30 } };
//	aabb b = { { 0,200 },{ 60,30 } };
//	plane p = { {200,200},{ 0.5f,0.5f } };
//	ray r = { { 400, 300 },{0,.5f }, 60 };
//
//	float speed = 180;
//	p.n.normalise();
//	r.d.normalise();
//
//	sfw::initContext(800, 600);
//	while (sfw::stepContext())
//	{
//		if (sfw::getKey('W')) { c.p.y += speed * sfw::getDeltaTime(); }
//		if (sfw::getKey('S')) { c.p.y -= speed * sfw::getDeltaTime(); }
//		if (sfw::getKey('D')) { c.p.x += speed * sfw::getDeltaTime(); }
//		if (sfw::getKey('A')) { c.p.x -= speed * sfw::getDeltaTime(); }
//		if (sfw::getKey('E')) { r.d.x -= sfw::getDeltaTime(); }
//		if (sfw::getKey('Q')) { r.d.x += sfw::getDeltaTime(); }
//		r.d.normalise();
//		CollisionData cd = mtv_circle_plane(c, p);
//		cout << "Collides? " << cd.collides << endl
//			<< "Penetration Depth: " << cd.penDepth << endl
//			<< "Collision Normal: " << cd.CollNorm.x << ", " << cd.CollNorm.y << endl
//			<< "MTV: " << cd.Mtv.x << ", " << cd.Mtv.y << endl;
//
//		c.p += cd.Mtv;
//		//		a.p += cd.Mtv / 2;
//		drawCircle(c, RED);
//		//		sfw::drawCircle(b.p.x, b.p.y, b.r, 100, BLUE);
//		drawAABB(a, BLUE);
//		drawAABB(b, YELLOW);
//		drawPlane(p, GREEN);
//		drawRay(r, BLACK);
//
//
//		/*	if (iTest_aabb_ray(a,r))
//			{
//				cout << "Melee" << endl;
//			}
//			else
//			{
//				cout << "Bruh you ain't playin' maylay" << endl;
//			}*/
//
//	}
//	sfw::termContext();
//
//	system("pause");
//	return 0;
//}