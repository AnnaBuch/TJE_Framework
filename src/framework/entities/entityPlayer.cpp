#include "entityPlayer.h"
#include "framework/camera.h"
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "graphics/mesh.h"
#include <algorithm>
#include "game/world.h"
#include "game/game.h"
#include <framework/input.h>


bool checkPlayerCollisions(const Vector3& target_pos,
	std::vector<sCollisionData>& collisions) {

	Vector3 center = target_pos +Vector3(0.f, 0.f, 2.f);
	float sphereRadius = 0.75f;
	Vector3 colPoint, colNormal;
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
			for (const Matrix44 model : collider->models) {
				Vector3 colPoint;
				Vector3 colNormal;
				if (collider->mesh->testSphereCollision(model, center,
					sphereRadius, colPoint, colNormal)) {
					collisions.push_back({ colPoint,
				colNormal.normalize() });
				}

			}
		}
	}
	return !collisions.empty();
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


	//render debug spheres: to check player collisions
	//float sphere_radius = World::instance->sphere_radius;


	//To debug, make spheres visible
	//Mesh* sphere = new Mesh();

	//sphere->createCube();
	

	//std::vector<sCollisionData> coliisions;

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
		//World::instance->root->render(camera);
		//sphere->render(GL_TRIANGLES);


		// Disable shader
		material.shader->disable();
	}
	
	//sphere->~Mesh();
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
		rotation += 30 * deltaTime;
		if (rotation < 30)
			toRotate = 30 * deltaTime;
		//rotation = 30 / deltaTime;
	}
	if (Input::isKeyPressed(SDL_SCANCODE_D) || Input::isKeyPressed(SDL_SCANCODE_RIGHT)) {
		move.x = -1.f;
		rotation -= 30* deltaTime;
		//rotation = rotation - (30 / deltaTime) < -30 ? -30 : rotation - (30 / deltaTime);
		if (rotation >= -30) {
			toRotate = -30 * deltaTime;
			//model.rotate((-30 * deltaTime) * DEG2RAD, model.frontVector().normalize());
			std::cout << "rotation: " <<  rotation << std::endl;

		}
	}
	
	//TODO: try smooth spaeceship movement, aka: rebot 
	move.normalize();
	move *= velocity * deltaTime;
	//model.rotate(toRotate * DEG2RAD, Vector3(0, 0, 1));
	model.translate(move);
	std::vector<sCollisionData> collisions;
	if (checkPlayerCollisions(model.getTranslation(), collisions)) {
		std::cout << "collided" << std::endl;

	}

	//TODO: Player collisions


}






