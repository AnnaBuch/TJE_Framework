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


void EndStage::render()
{
	drawText(10, 25, "End stage", Vector3(1, 1, 1), 6);
}

void EndStage::update(double deltaTime)
{

}




void IntroStage::init() {
    static bool menuInitialized = false;
    static Entity* background = nullptr;
    static Entity* play_button = nullptr;
    static Entity* exit_button = nullptr;
    static Camera* camera2d = nullptr;

    int world_width = Game::instance->window_width;
    int world_height = Game::instance->window_height;

    camera2d = World::instance->camera2D;

    // Background image
    Material background_mat;
    background_mat.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
    background_mat.diffuse = Texture::Get("data/ui/test_menu.png"); // Replace with your menu image
    background = new EntityUI(Vector2(world_width * 0.5, world_height * 0.5), Vector2(world_width, world_height), background_mat);

    // Play button
    Material play_mat;
    play_mat.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
    play_mat.diffuse = Texture::Get("data/ui/start.png"); // Replace with your play button image
    play_button = new EntityUI(Vector2(world_width * 0.5, 400), Vector2(240, 60), play_mat, eButtonId::PlayButton);

    // Exit button
    Material exit_mat;
    exit_mat.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
    exit_mat.diffuse = Texture::Get("data/ui/end.png"); // Replace with your exit button image
    exit_button = new EntityUI(Vector2(world_width * 0.5, 500), Vector2(240, 60), exit_mat, eButtonId::EndButton);

    menuInitialized = true;
}


void IntroStage::render() {
    drawText(10, 25, "Menu", Vector3(1, 1, 1), 4);

    
    //background->render(camera2d);
    //play_button->render(camera2d);
    //exit_button->render(camera2d);
}
void IntroStage::update(double deltaTime) {

    if (Input::isKeyPressed(SDL_SCANCODE_SPACE)) {
        Game::instance->goToStage(PLAY_STAGE);
    }

    /*
    // Check for button press
    if (Input::isMousePressed(SDL_BUTTON_LEFT)) {
        // Check if play button is pressed
        if (play_button->contains(Input::mouse_position)) {
            Game::instance->goToStage(PLAY_STAGE);
        }
        // Check if exit button is pressed
        else if (exit_button->contains(Input::mouse_position)) {
            // Perform exit action (not implemented here)
            // For simplicity, you might want to add an exit function
        }
    }
    background->update(seconds_elapsed);
	play_button->update(seconds_elapsed);
	exit_button->update(seconds_elapsed);
    // Render menu components

    */
}



