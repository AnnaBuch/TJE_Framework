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
	if (int(forward_distance) % 30 == 0) {
		last_forward_added += 50.f; //més o menys per on anem -> on s'ha de carregar la nova escena
		EntityMesh* forward_root = new EntityMesh(new Mesh(), Material(), "");
		forward_root->model.translate(0, 0, last_forward_added);
		bool sceneCheck = World::instance->parseScene("data/myscene.scene", forward_root, 0.f);
		Game::instance->play_stage->scene_roots.push_back(forward_root);
		//La meva idea: no tenir mes de 7 escenes carreageds, quan es el cas -> eliminar la mes antiga-> no acaba de funcionar, 
		//si es treu aixo, funciona, pero els FPS baixen molt!
		if (Game::instance->play_stage->scene_roots.size() > 7) {
			//aqui estic intentant 
			delete Game::instance->play_stage->scene_roots.front();
			Game::instance->play_stage->scene_roots.erase(Game::instance->play_stage->scene_roots.begin());
		}	

	}
}
