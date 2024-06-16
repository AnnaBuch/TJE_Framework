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



void EntityUI::render(Camera* camera2d) {

	glDisable(GL_DEPTH_TEST);

	glDisable(GL_CULL_FACE);

	material.shader->enable();

	World* world = World::instance;

	material.shader->setUniform("u_color", material.color);
	material.shader->setUniform("u_viewprojection", camera2d->viewprojection_matrix);
	material.shader->setUniform("u_model", model); 
	material.shader->setUniform("u_texture", material.diffuse, 0);


	quad->render(GL_TRIANGLES);

	material.shader->disable();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	Entity::render(camera2d);


}

void EntityUI::update(float seconds_elapsed) {

	Entity::update(seconds_elapsed);

}