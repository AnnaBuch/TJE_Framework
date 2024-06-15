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


IntroStage::IntroStage() {

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
    play_mat.diffuse = Texture::Get("data/ui/noraml.png"); // Replace with your play button image
    play_button = new EntityUI(Vector2(world_width * 0.5, 390), Vector2(240, 60), play_mat, eButtonId::PlayButton);

    // Exit button
    Material exit_mat;
    exit_mat.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
    exit_mat.diffuse = Texture::Get("data/ui/endless.png"); // Replace with your exit button image
    exit_button = new EntityUI(Vector2(world_width * 0.5, 470), Vector2(240, 60), exit_mat, eButtonId::EndButton);




    menuInitialized = true;

}


void IntroStage::render() {
    //drawText(10, 25, "Menu", Vector3(1, 1, 1), 4);

    background->render(World::instance->camera2D);
    play_button->render(World::instance->camera2D);
    exit_button->render(World::instance->camera2D);

    drawText(230, 270, "   Test your skills!", Vector3(0.729, 0.511, 1), 3);
    drawText(230, 305, "Choose Challenge Mode", Vector3(0.729, 0.511, 1), 3);

}

void IntroStage::update(double deltaTime) {

    Stage::update(deltaTime);

    // Check if the left mouse button is pressed
    if (Input::isMousePressed(SDL_BUTTON_LEFT)) {
        Vector2 mouse_pos = Input::mouse_position;

        // Check if the mouse click is within the bounds of the play_button
        if (play_button &&
            mouse_pos.x > (play_button->position.x - play_button->size.x * 0.5f) &&
            mouse_pos.x < (play_button->position.x + play_button->size.x * 0.5f) &&
            mouse_pos.y >(play_button->position.y - play_button->size.y * 0.5f) &&
            mouse_pos.y < (play_button->position.y + play_button->size.y * 0.5f)) {


            Game::instance->goToStage(PLAY_STAGE);
        }
        if (exit_button &&
            mouse_pos.x > (exit_button->position.x - exit_button->size.x * 0.5f) &&
            mouse_pos.x < (exit_button->position.x + exit_button->size.x * 0.5f) &&
            mouse_pos.y >(exit_button->position.y - exit_button->size.y * 0.5f) &&
            mouse_pos.y < (exit_button->position.y + exit_button->size.y * 0.5f)) {

            //change gameode 
            Game::instance->goToStage(PLAY_STAGE);
            
        }
    }
}


VictoryStage::VictoryStage()
{
}

void VictoryStage::render()
{
}

void VictoryStage::update(double deltaTime)
{
}

LosingStage::LosingStage()
{
}

void LosingStage::render()
{
}

void LosingStage::update(double deltaTime)
{
}
void IntroStage::onEnter() {
    theme = Audio::Play("data/audio/idle.wav", 1, BASS_SAMPLE_LOOP);
}

void IntroStage::onExit() {
    Audio::Stop(theme);
}

void VictoryStage::onEnter() {
    theme = Audio::Play("data/audio/idle.wav", 1, BASS_SAMPLE_LOOP);
}

void VictoryStage::onExit() {
    Audio::Stop(theme);
}
void LosingStage::onEnter() {
    theme = Audio::Play("data/audio/idle.wav", 1, BASS_SAMPLE_LOOP);
}

void LosingStage::onExit() {
    Audio::Stop(theme);
}


