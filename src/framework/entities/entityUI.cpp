#include "framework/entities/entityUI.h"
#include "framework/entities/entityPlayer.h"

#include "framework/input.h"
#include "game/world.h"
#include "game/game.h"
#include "game/stages/stage.h"

#include <iostream>
#include <fstream>


EntityUI::EntityUI(Vector2 size, const Material& material) {
	this->size = size;
	this->material = material;

}

EntityUI::EntityUI(Vector2 position, Vector2 size, const Material& material, eButtonId buttonId) {
	this->position = position;
	this->size = size;
	this->material = material;
	this->buttonId = buttonId;
	quad = new Mesh();
	quad->createQuad(position.x, position.y, size.x, size.y, true);

}

void EntityUI::render_energy(Camera* camera2d, float  current_energy_charged) {

	glDisable(GL_DEPTH_TEST);

	glDisable(GL_CULL_FACE);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC0_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	material.shader->enable();

	World* world = World::instance;
	//Matrix44 viewProj = camera2d->viewprojection_matrix;

	material.shader->setUniform("u_color", material.color);
	material.shader->setUniform("u_viewprojection", camera2d->viewprojection_matrix);
	material.shader->setUniform("u_model", model); //sino getGlobalMatrix()
	material.shader->setUniform("u_texture", material.diffuse, 0);

	material.shader->setFloat("Energy_charged", current_energy_charged);

	quad->render(GL_TRIANGLES);

	material.shader->disable();

	//quad.render(GL_TRIANGLES);

	//glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	Entity::render(camera2d);


}


void EntityUI::render_lifes(Camera* camera2d, int current_lifes) {

	glDisable(GL_DEPTH_TEST);

	glDisable(GL_CULL_FACE);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC0_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	material.shader->enable();

	World* world = World::instance;
	//Matrix44 viewProj = camera2d->viewprojection_matrix;

	material.shader->setUniform("u_color", material.color);
	material.shader->setUniform("u_viewprojection", camera2d->viewprojection_matrix);
	material.shader->setUniform("u_model", model); //sino getGlobalMatrix()
	material.shader->setUniform("u_texture", material.diffuse, 0);

	material.shader->setInt("lifes", current_lifes);

	quad->render(GL_TRIANGLES);

	material.shader->disable();

	//quad.render(GL_TRIANGLES);

	//glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	Entity::render(camera2d);


}


void EntityUI::render(Camera* camera2d) {

	glDisable(GL_DEPTH_TEST);

	glDisable(GL_CULL_FACE);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC0_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	material.shader->enable();

	World* world = World::instance;
	//Matrix44 viewProj = camera2d->viewprojection_matrix;

	material.shader->setUniform("u_color", material.color);
	material.shader->setUniform("u_viewprojection", camera2d->viewprojection_matrix);
	material.shader->setUniform("u_model", model); //sino getGlobalMatrix()
	material.shader->setUniform("u_texture", material.diffuse, 0);


	quad->render(GL_TRIANGLES);

	material.shader->disable();

	//quad.render(GL_TRIANGLES);

	//glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	Entity::render(camera2d);


}

void EntityUI::update(float seconds_elapsed) {

	if (buttonId == Energy_charged) {
		//material.color = Vector4::YELLOW;
		//float energy_charged = GamePlay::get_instance()->player->energy_charged;
	}
	else if (buttonId == Life) {
		//material.color = Vector4::RED;
	}
	else {
		//material.color = Vector4::WHITE;

	}
	Entity::update(seconds_elapsed);

}