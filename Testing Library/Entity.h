#pragma once
#include "GCData.h"

#include "Collider.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Sprite.h"
#include "Lifecycle.h"
#include "PlayerController.h"
#include "Health.h"
#include "Stamina.h"

struct Entity : public GCData<Entity>
{
	Handle<Transform> transform;
	Handle<RigidBody> rigidbody;
	Handle<Collider> collider;
	Handle<Sprite> sprite;
	Handle<Lifecycle> lifecycle;
	Handle<PlayerController> controller;
	Handle<Health> health;
	Handle<Stamina> stamina;

	void onFree()
	{
		Transform::free(transform.index);
		RigidBody::free(rigidbody.index);
		Collider::free(collider.index);
		Sprite::free(sprite.index);
		Lifecycle::free(lifecycle.index);
		PlayerController::free(controller.index);
		Health::free(health.index);
		Stamina::free(stamina.index);
	}
};