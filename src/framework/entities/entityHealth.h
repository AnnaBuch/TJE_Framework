#pragma once

#include "entityMesh.h"
#include "framework/includes.h"


class EntityHealth : public EntityMesh
{
public:
	EntityHealth();
	EntityHealth(Vector3 position);
	void update(float elapsed_time) override;
	void render(Camera* camera) override;
	bool expired = false;
	

};
