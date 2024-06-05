#include "entityHealth.h"
#include "graphics/texture.h"
#include "graphics/shader.h"
#include "graphics/mesh.h"
#include "game/world.h"
#include "game/game.h"
#include "framework/camera.h"




//void EntityMissile::renderSphere(Camera* camera, Vector3 translation, float radius) {
//	Shader* shader = Shader::Get("data/shaders/basic.vs", "data/shaders/flat.fs");
//	Mesh* mesh = Mesh::Get("data/meshes/sphere.obj");
//	Matrix44 m = model;
//
//	shader->enable();
//	m.translate(translation);
//	m.scale(radius, radius, radius);
//
//	shader->setUniform("u_color", Vector4(0.0f, 1.0f, 0.0f, 1.0f));
//	shader->setUniform("u_viewprojection", camera->viewprojection_matrix);
//	shader->setUniform("u_model", m);
//
//	mesh->render(GL_LINES);
//
//	shader->disable();
//
//}


EntityHealth::EntityHealth()
{
	material = Material();
	material.diffuse = Texture::Get("data/meshes/misil.tga");
	material.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	mesh = Mesh::Get("data/meshes/misil.ASE");
}

EntityHealth::EntityHealth(Vector3 position)
{
	material = Material();
	material.diffuse = Texture::Get("data/meshes/FirstAid.png");
	material.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	mesh = Mesh::Get("data/meshes/first_aid.obj");

	model.translate(position);
	model.scale(5, 5, 5);

}

void EntityHealth::update(float elapsed_time)
{
	model.rotate(360 * DEG2RAD * elapsed_time, Vector3(0, 1, 0));
}

void EntityHealth::render(Camera* camera)
{
	//TODO:delete this: only for debugging
	//renderSphere(camera, Vector3(0.f, 0.5f, 5.f), 1.f);
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
