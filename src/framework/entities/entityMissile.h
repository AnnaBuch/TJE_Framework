#pragma once

#include "entityMesh.h"
 


class EntityMissile : public EntityMesh
{
public:
	EntityMissile();
	//void render(Camera* camera) override;
	void update(float elapsed_time) override;
	void render(Camera* camera) override;
	float velocity = 70.f;
	


};
