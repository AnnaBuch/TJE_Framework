#include "stage.h"
#include "playStage.h"
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

#define MAX_BULLETS = 10;

int PlayStage::amo = 10;
std::array<EntityHealth*, 5> PlayStage::health;
std::array<EntityPower*, 5> PlayStage::power;
std::array<EntityMissile*, 10> PlayStage::missiles;

PlayStage::PlayStage()
{
	missiles.fill(nullptr);
	health.fill(nullptr);
	power.fill(nullptr);

}


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

	for (int i = 0; i < scene_roots.size(); ++i) {
		scene_roots[i]->Entity::render(camera);
	}
	player->render(camera);

	for (EntityMissile* m : missiles) {
		if (m != nullptr) {
			//if (m->collided) m->expired = true;
			m->render(camera);
		}
	}

	for (EntityHealth* h : health){
		if (h != nullptr) h->render(camera);
	}

	for (EntityPower* p : power) {
		if(p != nullptr)p->render(camera);
	}

	drawText(2, 2, "Health:" + std::to_string(player->health), Vector3(1, 1, 1), 2);
	drawText(300, 2, "Amonition:" + std::to_string(amo), Vector3(1, 1, 1), 2);
	if(recharge_timer != 0) drawText(500, 2, "Recharging amo...", Vector3(1, 1, 1), 2);

}

void PlayStage::update(double deltaTime) {

	EntityPlayer* player = World::instance->player;
	time_played += deltaTime;

	if (player->health <= 0) {
		Game::instance->goToStage(LOSING_STAGE);
		return;
	}
	if (World::instance->gameMode == REGULAR && time_played >= 60.f) {
		Game::instance->goToStage(VICTORY_STAGE);
		return;
	}

	Camera* camera = Camera::current;

	player->update(deltaTime);

	if (!Game::instance->free_cam) {
		Vector3 eye = player->model * Vector3(0.f, 4.f, -15.f);
		Vector3 center =player->model * Vector3(0.f, 0.f, 200.f);
		Vector3 up = player->model.rotateVector(Vector3(0, 1, 0));

		camera->lookAt(eye, center, up);
	}

	//update scene
	forward_distance += player->velocity * deltaTime;
	if (last_forward_added - forward_distance < 0  && time_played < 55) {
		last_forward_added += 90.f; //més o menys per on anem -> on s'ha de carregar la nova escena
		EntityMesh* forward_root = new EntityMesh(new Mesh(), Material(), "");
		forward_root->model.translate(0, 0, last_forward_added);
		bool sceneCheck = World::instance->parseScene("data/myscene.scene", forward_root, 0.f);
		
		Game::instance->play_stage->scene_roots.push_back(forward_root);
		if (Game::instance->play_stage->scene_roots[0]->getGlobalMatrix().getTranslation().z + 40 < player->model.getTranslation().z) {
			delete Game::instance->play_stage->scene_roots[0];
			Game::instance->play_stage->scene_roots.erase(Game::instance->play_stage->scene_roots.begin());
		}

	}

	//Update missiles positions
	for (EntityMissile* m : missiles) {
		if (m != nullptr) {
			if (m->collided || m->distance_run >= 50.0f) {
				m->expired = true;
			}
			else m->update(deltaTime);
		}
	}

	if (amo == 0) {
		recharge_timer += deltaTime;
	}
	if (recharge_timer >= 3) {
		amo = 10;
		recharge_timer = 0.f;
	}

	for (EntityHealth* h : health) {
		if (h != nullptr) {
			if (h->model.getTranslation().z < player->model.getTranslation().z - 10.f) 
				h->expired = true;
			else h->update(deltaTime);
		}
	}

	for (EntityPower* p : power) {
		if (p != nullptr) {
			if (p->model.getTranslation().z < player->model.getTranslation().z - 10.f) 
				p->expired = true;
			else p->update(deltaTime);
		}	
	}

}

void PlayStage::btnClick(int btn) {
	if (btn == SDL_BUTTON_LEFT) 
	{
		if (amo > 0) {

			--amo;
			EntityPlayer* player = World::instance->player;
			EntityMissile* missile = new EntityMissile(player->model);
			addMissile(missile);
		}
		
	}
}

void PlayStage::addMissile(EntityMissile* new_missile)
{
	for (int i = 0; i < missiles.size(); ++i) {
		if (missiles[i] == nullptr) {
			missiles[i] = new_missile;
			return;
		}
	}

	for (int i = 0; i < missiles.size(); ++i) {
		if (missiles[i] != nullptr && missiles[i]->expired) {
			delete missiles[i];
			missiles[i] = new_missile;
			return;
		}
	}

}

void PlayStage::addHealth(EntityHealth* new_health)
{
	for (int i = 0; i < health.size(); ++i) {
		if (health[i] == nullptr) {
			health[i] = new_health;
			return;
		}
	}

	for (int i = 0; i < health.size(); ++i) {
		if (health[i] != nullptr && health[i]->expired) {
			delete health[i];  
			health[i] = new_health;
			return;
		}
	}

}

void PlayStage::addPower(EntityPower* new_power)
{
	for (int i = 0; i < power.size(); ++i) {
		if (power[i] == nullptr) {
			power[i] = new_power;
			return;
		}
	}

	for (int i = 0; i < power.size(); ++i) {
		if (power[i] != nullptr && power[i]->expired) {
			delete power[i];  
			power[i] = new_power;
			return;
		}
	}

}

void PlayStage::onEnter() {
	theme = Audio::Play("data/audio/main_theme.wav", 0.3f, BASS_SAMPLE_LOOP);
}

void PlayStage::onExit() {
	Audio::Stop(theme);
}

