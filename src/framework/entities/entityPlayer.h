#pragma once

#include "entityMesh.h"
 


class EntityPlayer : public EntityMesh
{
public:
	EntityPlayer();
	//void render(Camera* camera) override;
	void update(float elapsed_time) override;
	void render(Camera* camera) override;
	float velocity;
	Vector3 position;
	float rotation = 0.f;

	float sphere_radius = 10.f;


};
