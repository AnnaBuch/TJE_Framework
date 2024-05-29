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
}

void PlayStage::btnClick(int btn) {
	if (btn == SDL_BUTTON_LEFT) 
	{
		Camera* camera = Camera::current;
		// get mouse position
		//Vector2 mouse_pos = Input::mouse_position;
		Vector3 ray_origin = World::instance->player->model.getTranslation();

		//Vector3 ray_direction = camera->getRayDirection(mouse_pos.x, mouse_pos.y, Game::instance->window_width, Game::instance->window_height);
		Vector3 ray_direction = World::instance->player->model.frontVector().normalize();
		bool collision_found = false;

		std::vector<Vector3> collisions;
		for (EntityMesh* sr : scene_roots) {
			if (!sr) {
				std::cerr << "Scene root is null" << std::endl;
				continue;
			}
			for (Entity* s : sr->children)
			{
				EntityMesh* collider = dynamic_cast<EntityMesh*>(s);
				if (!collider) continue;

				for (auto it = collider->models.begin(); it != collider->models.end();)
				{
					Vector3 collision_point;
					Vector3 collision_normal;
					if (collision_found) break;
					if (collider->mesh->testRayCollision(*it * collider->getGlobalMatrix(), ray_origin, ray_direction, collision_point, collision_normal, 500.f))
					{
						// Add the collision point to the list of collisions
						//collisions.push_back(collision_point);
						it = collider->models.erase(it);
						collision_found = true;
						break;
					}
					else ++it;
				}
				if (collision_found) break;
			}

		}

		//TODO: do something with the collisions found
		//std::cout << "collisions: " << collisions.size() << std::endl;

	}
}
