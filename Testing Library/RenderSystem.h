#pragma once
#include "System.h"
#include "Assets.h"

class RenderSystem : public System
{
	// sprite and transform
	bool condition(Handle<Entity> i)
	{
		return i->sprite > -1 && i->transform > -1;
	}

	// the actual draw call
	void update(Handle<Entity> i)
	{
		mat3 m =
			i->transform->getGlobalTransform()
			* mat3::translate(i->sprite->offset)
			* mat3::rotate(i->sprite->angle)
			* mat3::scale(i->sprite->dimension);

		Asset::instance().drawTexture(i->sprite->assetName, m.transpose());
	}
};