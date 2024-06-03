#include "entityMissile.h"
#include "graphics/texture.h"
#include "graphics/shader.h"
#include "graphics/mesh.h"
#include "game/world.h"
#include "game/game.h"
#include "framework/camera.h"


void EntityMissile::checkMissileCollisions(const Vector3& target_pos) {

	for (EntityMesh* sr : Game::instance->play_stage->scene_roots) {
		if (!sr) {
			std::cerr << "Scene root is null" << std::endl;
			continue;
		}
		for (Entity* s : sr->children)
		{
			EntityMesh* collider = dynamic_cast<EntityMesh*>(s);
			if (!collider) continue;
			for (auto it = collider->models.begin(); it != collider->models.end();) {
				Vector3 colPoint;
				Vector3 colNormal;
				if (collider->mesh->testSphereCollision((*it) * collider->getGlobalMatrix(), target_pos + Vector3(0.f, 0.5f, 5.f), 1.f, colPoint, colNormal)) {
					// DELETE ASTEROID: delete model from collider
					it = collider->models.erase(it);
					collided = true;
					//TODO: show fuel/power up
				}
				else {
					++it;
				}
			}
		}
	
	}
}

void EntityMissile::renderSphere(Camera* camera, Vector3 translation, float radius) {
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


EntityMissile::EntityMissile()
{
	material = Material();
	material.diffuse = Texture::Get("data/meshes/misil.tga");
	material.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	mesh = Mesh::Get("data/meshes/misil.ASE");
}

EntityMissile::EntityMissile(Matrix44 starting_pos)
{
	material = Material();
	material.diffuse = Texture::Get("data/meshes/misil.tga");
	material.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	mesh = Mesh::Get("data/meshes/misil.ASE");

	model.translate(starting_pos.getTranslation() + Vector3(0.f,0.5f,2.f));
	model.scale(0.3f, 0.3f, 1.f);
	//model.rotate(180 * DEG2RAD, Vector3(0.f, 1.f, 0.f));
}

void EntityMissile::update(float elapsed_time)
{
	// Calculate the translation vector
	Vector3 translation = Vector3(0,0,1) * velocity * elapsed_time;
	// Update the model matrix with the translation
	distance_run += velocity * elapsed_time;
	model.translate(translation);
	checkMissileCollisions(model.getTranslation());
}

void EntityMissile::render(Camera* camera)
{
	renderSphere(camera, Vector3(0.f, 0.5f, 5.f), 1.f);
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
