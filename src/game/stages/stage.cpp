#include "stage.h"
#include "framework/camera.h"
#include "framework/includes.h"
#include "game/world.h"
#include "game/game.h"
#include "framework/entities/EntityMesh.h"
#include "framework/entities/EntityPlayer.h"
#include "framework/entities/entityMissile.h"
#include "framework/entities/entityHealth.h"
#include "framework/entities/entityPower.h"


#include <framework/input.h>

//MENU STAGE
void Menu::init() {
	Game::instance->mouse_locked = false;
	isEnded = false;
	world_width = Game::instance->window_width;
	world_height = Game::instance->window_height;

	camera2d = World::instance->camera2D;

	Material background_mat;
	background_mat.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	background_mat.diffuse = new Texture();
	background_mat.diffuse = Texture::Get("data/ui/menu.png"); //get a menu
	background = new EntityUI(Vector2(world_width * 0.5, world_height * 0.5), Vector2(world_width, world_height), background_mat);


	Material play_mat;
	play_mat.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	play_mat.diffuse = new Texture();
	play_mat.diffuse = Texture::Get("data/ui/"); //get a play button
	play_button = new EntityUI(Vector2(world_width * 0.5, 400), Vector2(240, 60), play_mat, eButtonId::PlayButton);

	Material exit_mat;
	exit_mat.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	exit_mat.diffuse = new Texture();
	exit_mat.diffuse = Texture::Get("data/ui/"); //get exit button
	exit_button = new EntityUI(Vector2(world_width * 0.5, 500), Vector2(240, 60), exit_mat, eButtonId::EndButton);

	//background->addChild(play_button);
	//background->addChild(exit_button);


}

void Menu::restart() {

}

void Menu::render() {
	//glClearColor(0.0, 0.0, 0.0, 1.0);
	//glClear(GL_COLOR_BUFFER_BIT);
	//drawText(world_width/2, world_height /2, "Clica para entarr al juego", Vector3(1, 1, 1), 2);
	//drawText(world_width / 2, (world_height / 2  )+20, "Apreta G para cojer la llave cuando estes cerca de ella", Vector3(1, 1, 1), 2);

	////SDL_GL_SwapWindow(this->window);
	//glDisable(GL_BLEND);
	//glEnable(GL_DEPTH_TEST);
	//glDisable(GL_CULL_FACE);

	background->render(camera2d);
	play_button->render(camera2d);
	exit_button->render(camera2d);
}

void Menu::update(float seconds_elapsed) {
	//if (Input::isMousePressed(SDL_BUTTON_LEFT)) {
	//	World* world = World::get_instance();
	//	world->current_stage = world->game_stage;
	//}
	background->update(seconds_elapsed);
	play_button->update(seconds_elapsed);
	exit_button->update(seconds_elapsed);
}


void EndStage::render()
{
	drawText(10, 25, "End stage", Vector3(1, 1, 1), 6);
}

void EndStage::update(double deltaTime)
{

}

void IntroStage::render()
{
	drawText(10, 25, "Press SPACE to start", Vector3(1, 1, 1), 4);
	
}

void IntroStage::update(double deltaTime)
{
	if (Input::isKeyPressed(SDL_SCANCODE_SPACE)) {
		Game::instance->goToStage(PLAY_STAGE);
	}
}
