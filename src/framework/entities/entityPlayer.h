#pragma once

#include "entityMesh.h"
 


class EntityPlayer : public EntityMesh
{
public:
	EntityPlayer();
	//void render(Camera* camera) override;
	void update(float elapsed_time) override;
	void render(Camera* camera) override;
	void testHealthCollisions(const Vector3& target_pos);
	void testPowerCollisions(const Vector3& target_pos);

	float velocity;
	Vector3 position;
	float rotation = 0.f;

	float sphere_radius = 1.f;
	int health = 100;
	float collision_time = 0.f;
	bool has_collided = false;
	int power = 0;
	int asteroids_destorid = 0;
	


};
