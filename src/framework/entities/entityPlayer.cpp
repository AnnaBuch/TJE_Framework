#include "entityPlayer.h"
#include "framework/camera.h"
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "graphics/mesh.h"
#include <algorithm>
#include "game/world.h"
#include "game/game.h"
#include <framework/input.h>





EntityPlayer::EntityPlayer()
{
	material.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	material.diffuse = Texture::Get("data/textures/texture.tga");
	mesh = Mesh::Get("data/meshes/spaceship.obj");
	velocity = 20.f;
}

/*
void EntityPlayer::render(Camera* camera)
{


	//render debug spheres: to check player collisions
	float sphere_radius = World::instance->sphere_radius;
	float sphere_ground_radius = World::instance->sphere_ground_radius;


	//To debug, make spheres visible

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



		// Disable shader
		material.shader->disable();
	}

   
}*/



void EntityPlayer::update(float deltaTime)
{
	//Camera* camera = Camera::current;

	Vector3 position = model.getTranslation();
	Vector3 move = Vector3(0.f, 0.f, 1.f);

	if (Input::isKeyPressed(SDL_SCANCODE_W) || Input::isKeyPressed(SDL_SCANCODE_UP)) move.y = 1.f;
	if (Input::isKeyPressed(SDL_SCANCODE_S) || Input::isKeyPressed(SDL_SCANCODE_DOWN)) move.y = -1.f;
	if (Input::isKeyPressed(SDL_SCANCODE_A) || Input::isKeyPressed(SDL_SCANCODE_LEFT)) {
		move.x = 1.f;
	}
	if (Input::isKeyPressed(SDL_SCANCODE_D) || Input::isKeyPressed(SDL_SCANCODE_RIGHT)) {
		move.x = -1.f;

	}
	//TODO: try smooth spaeceship movement, aka: rebot 
	move.normalize();
	move *= velocity * deltaTime;
	model.translate(move);
	

	//TODO: Player collisions


}




