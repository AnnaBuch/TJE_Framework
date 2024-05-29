#include "entityMesh.h"
#include "framework/camera.h"
#include "graphics/shader.h"
#include "graphics/mesh.h"
#include <algorithm>
#include "game/world.h"
#include "entityPlayer.h"

/* Canvi a entiny mesh
void EntityMesh::Init(Mesh* mesh, Texture* texture, Shader* shader) {
	this->mesh = mesh;
	this->texture = texture;
	this->shader = shader;
}
*/
void EntityMesh::render(Camera* camera)
{

	if (!mesh) return;

	// Get the last camera that was activated 
	//Camera* camera = World::instance->camera;

	//optimization class->draw only if it is being seen
	if (!isInstanced) {
		Vector3 center_world = model * mesh->box.center;
		float abb_radius = mesh->box.halfsize.length();
		if (!camera->testSphereInFrustum(center_world, abb_radius)) {
			return;
		}
	}

	//TODO: si hi ha problemes de rendiment fer frustrum amb instancing 

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);


	if (!material.shader) {
		material.shader = Shader::Get(isInstanced ? "data/shaders/instanced.vs" : "data/shaders/basic.vs" , "data/shaders/texture.fs");
	}

	
	// Enable shader and pass uniforms 
	material.shader->enable();

	material.shader->setUniform("u_color", material.color);
	material.shader->setUniform("u_viewprojection", camera->viewprojection_matrix);
	material.shader->setUniform("u_camera_pos", camera->eye);


	if (material.diffuse)
		material.shader->setUniform("u_texture", material.diffuse, 0); //TODO: change the 0 when necessary

	if(!isInstanced)
		material.shader->setUniform("u_model", getGlobalMatrix());


	//load the correct mesh for LOD: level of detail
	Mesh* final_mesh = mesh;
	float distance = camera->eye.distance(model.getTranslation());

	for (sMeshLOD mesh_lod : mesh_lods) {

		if (mesh_lod.distance < distance) {
			final_mesh = mesh_lod.mesh;
		}
	}
	
	
	//if not LOD used change final_mesh to mesh
	if (isInstanced) {
		//Translate els meteorits utilitzant la global de la root que els conté
		std::vector<Matrix44> new_models;
		for (int i = 0; i < models.size(); ++i) {

			Matrix44 new_mat = models[i] * getGlobalMatrix();
			Vector3 asteroid_pos = new_mat.getTranslation();
			Vector3 player_pos = World::instance->player->model.getTranslation();

			//no renderitzar els asteroides per radere de l'avió
			if (asteroid_pos.z < player_pos.z - 10.f) {
				continue;
			}
			new_models.push_back(models[i] * getGlobalMatrix());
		}
		final_mesh->renderInstanced(GL_TRIANGLES, new_models.data(), new_models.size()); 


	}
	else
		final_mesh->render(GL_TRIANGLES);
		
	// Disable shader after finishing rendering
	material.shader->disable();

	Entity::render(camera);

}

EntityMesh::EntityMesh(Mesh* mesh, const Material& material, const std::string& name)
{
	this->mesh = mesh;
	this->material = material;
	this->name = name;
}

void EntityMesh::update(float deltaTime)
{
	Entity::update(deltaTime);
}

void EntityMesh::addInstance(Matrix44 model)
{
	models.push_back(model);
}

void EntityMesh::addLOD(sMeshLOD mesh_lod) {

	mesh_lods.push_back(mesh_lod);

	std::sort(mesh_lods.begin(), mesh_lods.end(), [](sMeshLOD a, sMeshLOD b) {
		return a.distance < b.distance;
	});
}




