#include "stage.h"
#include "framework/camera.h"
#include "framework/includes.h"
#include "game/world.h"
#include "game/game.h"
#include "framework/entities/EntityMesh.h"
#include "framework/entities/EntityPlayer.h"
#include "framework/entities/entityMissile.h"

#include <framework/input.h>

void PlayStage::render() 
{
	EntityPlayer* player = World::instance->player;

	// Set the camera as default
	Camera* camera = Camera::current;

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
	player->render(camera);
	/*for (auto it = missiles.begin(); it != missiles.end(); ) {
		it->first->render(camera);
	}*/
	for (EntityMissile* m : missiles) {
		m->render(camera);
	}
	drawText(2, 2, "Health:" + std::to_string(player->health), Vector3(1, 1, 1), 2);


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

	//update scene
	forward_distance += player->velocity * deltaTime;
	if (last_forward_added - forward_distance < 0 ) {
		last_forward_added += 90.f; //més o menys per on anem -> on s'ha de carregar la nova escena
		EntityMesh* forward_root = new EntityMesh(new Mesh(), Material(), "");
		forward_root->model.translate(0, 0, last_forward_added);
		bool sceneCheck = World::instance->parseScene("data/myscene.scene", forward_root, 0.f);
		
		Game::instance->play_stage->scene_roots.push_back(forward_root);
		//if (Game::instance->play_stage->scene_roots.size() > 2) {
			if (Game::instance->play_stage->scene_roots[0]->getGlobalMatrix().getTranslation().z + 40 < player->model.getTranslation().z) {
				delete Game::instance->play_stage->scene_roots[0];
				Game::instance->play_stage->scene_roots.erase(Game::instance->play_stage->scene_roots.begin());
			}
		//}

	}

	//Update missiles positions
	for (auto it = missiles.begin(); it != missiles.end(); /* no increment here */) {
		EntityMissile* m = *it;
		if (m->collided || m->distance_run >= 50.f) {
			delete m;
			it = missiles.erase(it); 
		}
		else {
			m->update(deltaTime);
			++it; 
		}
	}
	if (player->health <= 0) Game::instance->goToStage(END_STAGE);
}

void PlayStage::btnClick(int btn) {
	if (btn == SDL_BUTTON_LEFT) 
	{

		//shoot
		EntityPlayer* player = World::instance->player;
		//if (!player->has_collided) {
			EntityMissile* missile = new EntityMissile(player->model);
			missiles.push_back(missile);
		//}
	}
}

void EndStage::render()
{
	drawText(10, 25, "End stage", Vector3(1, 1, 1), 6);
}

void EndStage::update(double deltaTime)
{

}

void IntroStage::render()
{
	drawText(10, 25, "Press SPACE to start", Vector3(1, 1, 1), 4);
	
}

void IntroStage::update(double deltaTime)
{
	if (Input::isKeyPressed(SDL_SCANCODE_SPACE)) {
		Game::instance->goToStage(PLAY_STAGE);
	}
}
