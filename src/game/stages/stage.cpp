#include "stage.h"
#include "framework/camera.h"
#include "framework/includes.h"
#include "game/world.h"
#include "game/game.h"
#include "framework/entities/EntityMesh.h"
#include "framework/entities/EntityPlayer.h"
#include "framework/entities/entityMissile.h"
#include "framework/entities/entityHealth.h"
#include "framework/entities/entityPower.h"


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
	for (EntityHealth* h : health) {
		h->render(camera);
	}
	for (EntityPower* p : power) {
		p->render(camera);
	}
	drawText(2, 2, "Health:" + std::to_string(player->health), Vector3(1, 1, 1), 2);
	drawText(300, 2, "Amonition:" + std::to_string(amo), Vector3(1, 1, 1), 2);
	if(recharge_timer != 0) drawText(500, 2, "Recharging amo...", Vector3(1, 1, 1), 2);

}

void PlayStage::update(double deltaTime) {

	Camera* camera = Camera::current;
	EntityPlayer* player = World::instance->player;

	player->update(deltaTime);

	if (!Game::instance->free_cam) {
		Vector3 eye = player->model * Vector3(0.f, 4.f, -15.f);
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
	if (amo == 0) {
		recharge_timer += deltaTime;
	}
	if (recharge_timer >= 3) {
		amo = 10;
		recharge_timer = 0.f;
	}

	for (EntityHealth* h : health) {
		h->update(deltaTime);
	}
	for (EntityPower* p : power) {
		p->update(deltaTime);
	}
}

void PlayStage::btnClick(int btn) {
	if (btn == SDL_BUTTON_LEFT) 
	{
		if (amo > 0) {

			EntityPlayer* player = World::instance->player;
			//if (!player->has_collided) {
			EntityMissile* missile = new EntityMissile(player->model);
			missiles.push_back(missile);
			amo -= 1;
		}
		
	}
}


//MENU STAGE
void Menu::init() {
	Game::instance->mouse_locked = false;
	isEnded = false;
	world_width = World::instance->window_width;
	world_height = World::instance->window_height;

	camera2d = World::instance()->camera2D;

	Material background_mat;
	background_mat.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	background_mat.diffuse = new Texture();
	background_mat.diffuse = Texture::Get("data/ui/menu.png"); //get a menu
	background = new EntityUI(Vector2(world_width * 0.5, world_height * 0.5), Vector2(world_width, world_height), background_mat);


	Material play_mat;
	play_mat.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	play_mat.diffuse = new Texture();
	play_mat.diffuse = Texture::Get("data/ui/"); //get a play button
	play_button = new EntityUI(Vector2(world_width * 0.5, 400), Vector2(240, 60), play_mat, eButtonId::PlayButton);

	Material exit_mat;
	exit_mat.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	exit_mat.diffuse = new Texture();
	exit_mat.diffuse = Texture::Get("data/ui/"); //get exit button
	exit_button = new EntityUI(Vector2(world_width * 0.5, 500), Vector2(240, 60), exit_mat, eButtonId::EndButton);

	//background->addChild(play_button);
	//background->addChild(exit_button);


}

void Menu::restart() {

}

void Menu::render() {
	//glClearColor(0.0, 0.0, 0.0, 1.0);
	//glClear(GL_COLOR_BUFFER_BIT);
	//drawText(world_width/2, world_height /2, "Clica para entarr al juego", Vector3(1, 1, 1), 2);
	//drawText(world_width / 2, (world_height / 2  )+20, "Apreta G para cojer la llave cuando estes cerca de ella", Vector3(1, 1, 1), 2);

	////SDL_GL_SwapWindow(this->window);
	//glDisable(GL_BLEND);
	//glEnable(GL_DEPTH_TEST);
	//glDisable(GL_CULL_FACE);

	background->render(camera2d);
	play_button->render(camera2d);
	exit_button->render(camera2d);
}

void Menu::update(float seconds_elapsed) {
	//if (Input::isMousePressed(SDL_BUTTON_LEFT)) {
	//	World* world = World::get_instance();
	//	world->current_stage = world->game_stage;
	//}
	background->update(seconds_elapsed);
	play_button->update(seconds_elapsed);
	exit_button->update(seconds_elapsed);
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
