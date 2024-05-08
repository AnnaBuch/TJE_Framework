#include "stage.h"
#include "framework/camera.h"
#include "framework/includes.h"
#include "game/world.h"
#include "framework/entities/EntityMesh.h"
#include "framework/entities/EntityPlayer.h"
#include <framework/input.h>

void PlayStage::render() 
{

	// Set the camera as default
	Camera* camera = Camera::current;

	//TODO: set camera position at player




	Camera::current->enable();
	glDisable(GL_DEPTH_TEST);
	World::instance->skybox->model.setTranslation(camera->eye);
	World::instance->skybox->render(camera);
	glEnable(GL_DEPTH_TEST);


	// Set flags
	//glDisable(GL_BLEND);
	//glEnable(GL_DEPTH_TEST);
	//glDisable(GL_CULL_FACE);
	World::instance->player->render(camera);

}

void PlayStage::update(double deltaTime) {

	Camera* camera = Camera::current;
	World::instance->player->update(deltaTime);
	Vector3 eye = World::instance->player->model * Vector3(0.f, 6.f, -15.f);
	Vector3 center = World::instance->player->model * Vector3(0.f, 0.f, 200.f);
	Vector3 up = World::instance->player->model.rotateVector(Vector3(0, 1, 0));

	camera->lookAt(eye, center, up);

}
