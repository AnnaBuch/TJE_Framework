#pragma once

#include "entityMesh.h"


class EntityPlayer : public EntityMesh
{
public:
	void render();
	void update(float elapsed_time);
	float velocity;

};
