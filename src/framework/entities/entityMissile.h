#pragma once

#include "entityMesh.h"
#include "framework/includes.h"


class EntityMissile : public EntityMesh
{
public:
	EntityMissile();
	EntityMissile(Matrix44 starting_pos);

	//void render(Camera* camera) override;
	void update(float elapsed_time) override;
	void render(Camera* camera) override;
	void renderSphere(Camera* camera, Vector3 translation, float radius); //TODO: delete before submitting
	void checkMissileCollisions(const Vector3& target_pos);
	float velocity = 100.f;
	bool collided = false;
	float distance_run = 0.f;
	bool expired = false;

};
