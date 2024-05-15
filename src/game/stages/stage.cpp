#include "stage.h"
#include "framework/camera.h"
#include "framework/includes.h"
#include "game/world.h"
#include "game/game.h"
#include "framework/entities/EntityMesh.h"
#include "framework/entities/EntityPlayer.h"

#include <framework/input.h>

void PlayStage::render() 
{

	// Set the camera as default
	Camera* camera = Camera::current;

	//TODO: set camera position at player




	camera->enable();
	glDisable(GL_DEPTH_TEST);
	World::instance->skybox->model.setTranslation(camera->eye);
	World::instance->skybox->render(camera);
	glEnable(GL_DEPTH_TEST);


	// Set flags
	//glDisable(GL_BLEND);
	//glEnable(GL_DEPTH_TEST);
	//glDisable(GL_CULL_FACE);
	scene_root->Entity::render(camera);
	World::instance->player->render(camera);

}

void PlayStage::update(double deltaTime) {

	Camera* camera = Camera::current;
	EntityPlayer* player = World::instance->player;

	player->update(deltaTime);
	if (!Game::instance->free_cam) {
		Vector3 eye = player->model * Vector3(0.f, 6.f, -15.f);
		Vector3 center =player->model * Vector3(0.f, 0.f, 200.f);
		Vector3 up = player->model.rotateVector(Vector3(0, 1, 0));

		camera->lookAt(eye, center, up);


	}
}
