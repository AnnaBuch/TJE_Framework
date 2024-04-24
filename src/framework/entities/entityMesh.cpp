#include "entityMesh.h"
#include "framework/camera.h"
#include "graphics/shader.h"
#include "graphics/mesh.h"



void EntityMesh::render()
{
	// Get the last camera that was activated 
	Camera* camera = Camera::current;

	// Enable shader and pass uniforms 
	material.shader->enable();

	material.shader->setUniform("u_color", material.color);
	material.shader->setUniform("u_viewproj", camera->viewprojection_matrix);

	if (material.diffuse)
		material.shader->setUniform("u_texture", material.diffuse, 0); //TODO: change the 0 when necessary

	if(!isInstanced)
		material.shader->setUniform("u_model", getGlobalMatrix());

	if (isInstanced)
		mesh->renderInstanced(GL_TRIANGLES, models.data(), 1);
	else
		mesh->render(GL_TRIANGLES);
		
	// Disable shader after finishing rendering
	material.shader->disable();

	Entity::render(camera);

}

void EntityMesh::update(float deltaTime) 
{
	Entity::update(deltaTime);
}

