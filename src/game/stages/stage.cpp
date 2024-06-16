#include "stage.h"
#include "framework/camera.h"
#include "framework/includes.h"
#include "game/world.h"
#include "game/game.h"
#include "game/stages/playStage.h"
#include "framework/entities/EntityMesh.h"
#include "framework/entities/EntityPlayer.h"
#include "framework/entities/entityMissile.h"
#include "framework/entities/entityHealth.h"
#include "framework/entities/entityPower.h"


#include <framework/input.h>

#include <iostream>
#include <iomanip> 


IntroStage::IntroStage() {

    int world_width = Game::instance->window_width;
    int world_height = Game::instance->window_height;

    camera2d = World::instance->camera2D;

    // Background image
    Material background_mat;
    background_mat.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
    background_mat.diffuse = Texture::Get("data/ui/test_menu.png"); 
    background = new EntityUI(Vector2(world_width * 0.5, world_height * 0.5), Vector2(world_width, world_height), background_mat);

    // Play button
    Material play_mat;
    play_mat.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
    play_mat.diffuse = Texture::Get("data/ui/noraml.png"); 
    play_button = new EntityUI(Vector2(world_width * 0.5, 390), Vector2(240, 60), play_mat, eButtonId::PlayButton);

    // Exit button
    Material exit_mat;
    exit_mat.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
    exit_mat.diffuse = Texture::Get("data/ui/endless.png"); 
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

            World::instance->gameMode = REGULAR;
            Game::instance->goToStage(PLAY_STAGE);
        }
        if (exit_button &&
            mouse_pos.x > (exit_button->position.x - exit_button->size.x * 0.5f) &&
            mouse_pos.x < (exit_button->position.x + exit_button->size.x * 0.5f) &&
            mouse_pos.y >(exit_button->position.y - exit_button->size.y * 0.5f) &&
            mouse_pos.y < (exit_button->position.y + exit_button->size.y * 0.5f)) {

            //change gameode 
            World::instance->gameMode = ENDLESS;
            Game::instance->goToStage(PLAY_STAGE);
            
        }
    }
}


VictoryStage::VictoryStage() {
    const int numFrames = 200; 
    int world_width = Game::instance->window_width;
    int world_height = Game::instance->window_height;

    for (int i = 36; i <= numFrames; ++i) {
        std::string filename = "data/ui/cinematic/output_" + std::to_string(i) + ".png";
        printf("Loading frame %s\n", filename.c_str());
        Texture* texture = Texture::Get(filename.c_str());

        Material frameMat;
        frameMat.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
        frameMat.diffuse = texture;

        EntityUI* frameEntity = new EntityUI(Vector2(world_width * 0.5, world_height * 0.5),
            Vector2(world_width, world_height), frameMat);
        frames.push_back(frameEntity);
    }

    currentFrameIndex = 0;
    frameTimer = 0.0;
    frameInterval = 0.163; // Interval between frames in seconds 
}

void VictoryStage::render() {
    // Render the current frame
    if (currentFrameIndex < frames.size()) {
        // printf("currentFrameIndex: %d\n", currentFrameIndex);
        frames[currentFrameIndex]->render(World::instance->camera2D);

        if (currentFrameIndex == frames.size() - 1) {
            drawText(200, 100, "   RESULTS", Vector3(0.729, 0.511, 1), 6);

            EntityPlayer* player = World::instance->player;
            int asteroidsDestroyed = player->asteroids_destorid;
            int health = player->health;
            int power = player->power;

            double destructionPercentage = ((static_cast<double>(health) / 100) * 0.30 + (static_cast<double>(asteroidsDestroyed) / 15) * 0.30 + (static_cast<double>(power) / 8) * 0.40) * 100;

            // Convert the number to a string and draw it
            std::string resultsText = "Asteroids Destroyed: " + std::to_string(asteroidsDestroyed);
            std::string resultsText2 = "Health: " + std::to_string(health);
            std::string resultsText3 = "Power Containers Collected: " + std::to_string(power);
            drawText(50, 200, resultsText2.c_str(), Vector3(0.729, 0.511, 1), 4); 
            drawText(50, 240, resultsText.c_str(), Vector3(0.729, 0.511, 1), 4);
            drawText(50, 280, resultsText3.c_str(), Vector3(0.729, 0.511, 1), 4);
            drawText(50, 340, "----------------------------", Vector3(0.729, 0.511, 1), 4);

            std::stringstream ss;
            ss << std::fixed << std::setprecision(2) << destructionPercentage;
            std::string destructionPercentageStr = ss.str();


            drawText(50, 380, "Destruction Percentage: " + destructionPercentageStr + "%", Vector3(0.729, 0.511, 1), 4);


        }

    }
}

void VictoryStage::update(double deltaTime) {
    Stage::update(deltaTime);

    frameTimer += deltaTime;

    // Check if it's time to advance to the next frame
    if (frameTimer >= frameInterval) {
        frameTimer = 0.0;
        if (currentFrameIndex < frames.size() - 1) {
            currentFrameIndex++;
        }
    }
}

VictoryStage::~VictoryStage() {
    for (EntityUI* frame : frames) {
        delete frame;
    }
    frames.clear();
}


LosingStage::LosingStage(){

    int world_width = Game::instance->window_width;
    int world_height = Game::instance->window_height;

    camera2d = World::instance->camera2D;

    // Background image
    Material end_mat;
    end_mat.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
    end_mat.diffuse = Texture::Get("data/ui/game_over.png");
    end = new EntityUI(Vector2(world_width * 0.5, world_height * 0.5), Vector2(world_width, world_height), end_mat);
}

void LosingStage::render()
{
    end->render(World::instance->camera2D);
    drawText(200, 100, "   RESULTS", Vector3(0.729, 0.511, 1), 6);

    /* If gamemode noraml print GAME OVER/ else print resuts*/

    EntityPlayer* player = World::instance->player;
    int asteroidsDestroyed = player->asteroids_destorid;
    int health = player->health;
    int power = player->power;
    float time = dynamic_cast<PlayStage*>(Game::instance->stages[PLAY_STAGE])->time_played;
    

    // Convert the number to a string and draw it
    std::string resultsText = "Asteroids Destroyed: " + std::to_string(asteroidsDestroyed);
    std::string resultsText3 = "Power Containers Collected: " + std::to_string(power);

    drawText(50, 240, resultsText.c_str(), Vector3(0.729, 0.511, 1), 4);
    drawText(50, 280, resultsText3.c_str(), Vector3(0.729, 0.511, 1), 4);
    drawText(50, 340, "----------------------------", Vector3(0.729, 0.511, 1), 4);
    
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << time;
    std::string time_aa = ss.str();


    drawText(50, 380, "Total time: " + time_aa + "s", Vector3(0.729, 0.511, 1), 4);
    
}

void LosingStage::update(double deltaTime)
{
    Stage::update(deltaTime);
}


void IntroStage::onEnter() {
    theme = Audio::Play("data/audio/idle.wav", 1, BASS_SAMPLE_LOOP);
}

void IntroStage::onExit() {
    Audio::Stop(theme);
}

void VictoryStage::onEnter() {
    theme = Audio::Play("data/audio/v_1.wav", 1, BASS_SAMPLE_MONO);
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


