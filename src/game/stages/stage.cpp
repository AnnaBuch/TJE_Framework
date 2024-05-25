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
	for (int i = 0; i < scene_roots.size(); ++i) {
		scene_roots[i]->Entity::render(camera);
	}
	//scene_root->Entity::render(camera);
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
	forward_distance += player->velocity * deltaTime;
	if (last_forward_added - forward_distance < 20) {
		last_forward_added += 70.f; //més o menys per on anem -> on s'ha de carregar la nova escena
		EntityMesh* forward_root = new EntityMesh(new Mesh(), Material(), "");
		forward_root->model.translate(0, 0, last_forward_added);
		bool sceneCheck = World::instance->parseScene("data/myscene.scene", forward_root, 0.f);
		
		if (Game::instance->play_stage->scene_roots.size() > 3) {
			delete Game::instance->play_stage->scene_roots[0];
			Game::instance->play_stage->scene_roots.erase(Game::instance->play_stage->scene_roots.begin());
		}
		Game::instance->play_stage->scene_roots.push_back(forward_root);
		

	}
}
