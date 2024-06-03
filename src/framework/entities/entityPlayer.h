#pragma once

#include "entityMesh.h"
 


class EntityPlayer : public EntityMesh
{
public:
	EntityPlayer();
	//void render(Camera* camera) override;
	void update(float elapsed_time) override;
	void render(Camera* camera) override;
	void renderSphere(Camera* camera, Vector3 translation, float radius); //TODO: delete before submitting

	float velocity;
	Vector3 position;
	float rotation = 0.f;

	float sphere_radius = 1.f;
	int health = 100;
	float collision_time = 0.f;
	bool has_collided = false;


};
