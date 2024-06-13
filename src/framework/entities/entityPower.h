#pragma once

#include "entityMesh.h"
#include "framework/includes.h"


class EntityPower : public EntityMesh
{
public:
	EntityPower();
	EntityPower(Vector3 position);

	//void render(Camera* camera) override;
	void update(float elapsed_time) override;
	void render(Camera* camera) override;
	//void renderSphere(Camera* camera, Vector3 translation, float radius); //TODO: delete before submitting
	bool expired = false;

};
