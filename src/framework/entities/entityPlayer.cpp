#include "entityPlayer.h"
#include "framework/camera.h"
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "graphics/mesh.h"
#include <algorithm>
#include "game/world.h"
#include "game/game.h"
#include <framework/input.h>
#include "entityHealth.h"



bool checkPlayerCollisions(const Vector3& target_pos) {
	bool collided = false;
	for (EntityMesh* sr : Game::instance->play_stage->scene_roots) {
		if (!sr) {
			std::cerr << "Scene root is null" << std::endl;
			continue;
		}
		for (Entity* s : sr->children)
		{

			EntityMesh* collider = dynamic_cast<EntityMesh*>(s);
			if (!collider) continue;
			int i = 0;
			for (auto it = collider->models.begin(); it != collider->models.end();) {
				Vector3 colPoint;
				Vector3 colNormal;
				if (collider->mesh->testSphereCollision(*it*collider->getGlobalMatrix(), target_pos + Vector3(0.f, 0.5f, 5.f), 1.f, colPoint, colNormal)
					|| collider->mesh->testSphereCollision(*it * collider->getGlobalMatrix(), target_pos + Vector3(2.f, 0.5f, 2.f), 1.f, colPoint, colNormal)
					|| collider->mesh->testSphereCollision(*it * collider->getGlobalMatrix(), target_pos + Vector3(-2.f, 0.5f, 2.f), 1.f, colPoint, colNormal)
					|| collider->mesh->testSphereCollision(*it * collider->getGlobalMatrix(), target_pos + Vector3(0.f, 0.5f, -2.f), 2.f, colPoint, colNormal)
					|| collider->mesh->testSphereCollision(*it * collider->getGlobalMatrix(), target_pos + Vector3(4.f, 0.5f, -1.f), 1.5f, colPoint, colNormal)
					|| collider->mesh->testSphereCollision(*it * collider->getGlobalMatrix(), target_pos + Vector3(-4.f, 0.5f, -1.f), 1.5f, colPoint, colNormal)
					
					) {
					collided = true;
					it = collider->models.erase(it);
				}
				else {
					++it;
				}

			}
		}
	}
	return collided;
}

void EntityPlayer::testHealthCollisions(const Vector3& target_pos) {
	
	for (auto it = Game::instance->play_stage->health.begin(); it != Game::instance->play_stage->health.end();) {
		Vector3 colPoint;
		Vector3 colNormal;
		EntityHealth* h = *it;

		if (h->mesh->testSphereCollision(h->model, target_pos + Vector3(0.f, 0.5f, 5.f), 1.f, colPoint, colNormal)) {
			it = Game::instance->play_stage->health.erase(it);
			if(health < 100)health += 5;
			//TODO:add sound effect
		}
		else {
			++it;
		}
	}
}

//TODO: delete before submission
void EntityPlayer::renderSphere(Camera* camera, Vector3 translation, float radius) {
	Shader* shader = Shader::Get("data/shaders/basic.vs", "data/shaders/flat.fs");
	Mesh* mesh = Mesh::Get("data/meshes/sphere.obj");
	Matrix44 m = model;

	shader->enable();
	m.translate(translation);
	m.scale(radius, radius, radius);

	shader->setUniform("u_color", Vector4(0.0f, 1.0f, 0.0f, 1.0f));
	shader->setUniform("u_viewprojection", camera->viewprojection_matrix);
	shader->setUniform("u_model", m);

	mesh->render(GL_LINES);

	shader->disable();

}



EntityPlayer::EntityPlayer()
{
	material.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	material.diffuse = Texture::Get("data/textures/texture.tga");
	mesh = Mesh::Get("data/meshes/spaceship.obj");
	velocity = 20.f;
}


void EntityPlayer::render(Camera* camera)
{




	//To debug, make spheres visible TODO: delete before submission
	
	/*renderSphere(camera, Vector3(0.f, 0.5f, 5.f), 1.f);
	renderSphere(camera, Vector3(2.f, 0.5f, 2.f), 1.f);
	renderSphere(camera, Vector3(-2.f, 0.5f, 2.f), 1.f);
	renderSphere(camera, Vector3(0.f, 0.5f, -2.f), 2.f);
	renderSphere(camera, Vector3(4.f, 0.5f, -1.f), 1.5f);
	renderSphere(camera, Vector3(-4.f, 0.5f, -1.f), 1.5f);*/

	if (material.shader)
	{
		// Enable shader
		material.shader->enable();

		// Upload uniforms
		material.shader->setUniform("u_color", Vector4(1, 1, 1, 1));
		material.shader->setUniform("u_viewprojection", camera->viewprojection_matrix);
		material.shader->setUniform("u_texture", material.diffuse, 0);
		material.shader->setUniform("u_model", model);
		material.shader->setUniform("u_time", Game::instance->time);

		// Do the draw call
		mesh->render(GL_TRIANGLES);

		// Disable shader
		material.shader->disable();
	}
	
}



void EntityPlayer::update(float deltaTime)
{
	//Camera* camera = Camera::current;
	float toRotate = deltaTime;
	if (rotation < 0)
		toRotate = -deltaTime;
	else if (rotation = 0)
		toRotate = 0;
	Vector3 position = model.getTranslation();
	Vector3 move = Vector3(0.f, 0.f, 1.f);
	if (Input::isKeyPressed(SDL_SCANCODE_W) || Input::isKeyPressed(SDL_SCANCODE_UP)) move.y = 1.f;
	if (Input::isKeyPressed(SDL_SCANCODE_S) || Input::isKeyPressed(SDL_SCANCODE_DOWN)) move.y = -1.f;
	if (Input::isKeyPressed(SDL_SCANCODE_A) || Input::isKeyPressed(SDL_SCANCODE_LEFT)) {
		move.x = 1.f;
		/*rotation += 30 * deltaTime;
		if (rotation < 30)
			toRotate = 30 * deltaTime;*/
		//rotation = 30 / deltaTime;
	}
	if (Input::isKeyPressed(SDL_SCANCODE_D) || Input::isKeyPressed(SDL_SCANCODE_RIGHT)) {
		move.x = -1.f;
		//rotation -= 30* deltaTime;
		////rotation = rotation - (30 / deltaTime) < -30 ? -30 : rotation - (30 / deltaTime);
		//if (rotation >= -30) {
		//	toRotate = -30 * deltaTime;
		//	//model.rotate((-30 * deltaTime) * DEG2RAD, model.frontVector().normalize());
		//	//std::cout << "rotation: " <<  rotation << std::endl;

		//}
	}
	
	//TODO: try smooth spaeceship movement, aka: rebot 
	
	move.normalize();
	move *= velocity * deltaTime;

	//model.rotate(toRotate * DEG2RAD, Vector3(0, 0, 1));
	model.translate(move);
	if (!has_collided && checkPlayerCollisions(model.getTranslation())) {
		//std::cout << "collided" << std::endl;
		health -= 5;
		has_collided = true;
		//TODO: sound effects
	}

	if (has_collided) {
		collision_time += deltaTime;
		if (collision_time >= 3) {
			has_collided = false;
			collision_time = 0.f;
		}
	}
	testHealthCollisions(model.getTranslation());
	

}






