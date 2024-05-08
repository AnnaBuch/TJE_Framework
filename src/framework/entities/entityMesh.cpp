#include "entityMesh.h"
#include "framework/camera.h"
#include "graphics/shader.h"
#include "graphics/mesh.h"
#include <algorithm>
#include "game/world.h"



void EntityMesh::render()
{

	if (!mesh) return;

	// Get the last camera that was activated 
	Camera* camera = World::instance->camera;

	//optimization class->draw only if it is being seen
	Vector3 center_world = model * mesh->box.center;
	float abb_radius = mesh->box.halfsize.length();
	if (!camera->testSphereInFrustum(center_world, abb_radius)) {
		return;
	}


	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);


	if (!material.shader) {
		material.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");//Get(isInstanced ? "data/shaders/instanced.vs" : "data/shaders/basic.vs");
	}

	
	// Enable shader and pass uniforms 
	material.shader->enable();

	material.shader->setUniform("u_color", material.color);
	material.shader->setUniform("u_viewprojection", camera->viewprojection_matrix);
	material.shader->setUniform("u_camera_pos", World::instance->camera->eye);


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
	if (isInstanced)
		final_mesh->renderInstanced(GL_TRIANGLES, models.data(), models.size());
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




