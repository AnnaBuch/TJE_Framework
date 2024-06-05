#include "game.h"
#include "framework/utils.h"
#include "graphics/mesh.h"
#include "graphics/texture.h"
#include "graphics/fbo.h"
#include "graphics/shader.h"
#include "framework/input.h"
#include "world.h"
#include "framework/entities/entityMesh.h"
#include "framework/entities/entityPlayer.h"

#include "framework/entities/entityCollider.h"
#include "game/stages/stage.h"

#include <cmath>

#include "framework/audio.h"



float angle = 0;
float mouse_speed = 100.0f;;
EntityMesh* missil;

Game* Game::instance = NULL;
World* World::instance = NULL;

Game::Game(int window_width, int window_height, SDL_Window* window)
{
	this->window_width = window_width;
	this->window_height = window_height;
	this->window = window;
	instance = this;
	must_exit = false;

	fps = 0;
	frame = 0;
	time = 0.0f;
	elapsed_time = 0.0f;
	mouse_locked = false;
	Camera::current = new Camera();

	// OpenGL flags
	glEnable( GL_CULL_FACE ); //render both sides of every triangle
	glEnable( GL_DEPTH_TEST ); //check the occlusions using the Z buffer

	World::instance = new World();

	play_stage = new PlayStage();
	play_stage->scene_roots.push_back(new EntityMesh(new Mesh(), Material(), ""));
	play_stage->scene_roots[0]->model.translate(0, 0, 100.f);

	bool sceneCheck = World::instance->parseScene("data/myscene.scene", play_stage->scene_roots[0], 0.f);
	stages[PLAY_STAGE] = play_stage;
	stages[END_STAGE] = new EndStage();
	IntroStage* intro_stage = new IntroStage();
	stages[INTRO_STAGE] = intro_stage;
	current_stage = dynamic_cast<Stage*>(intro_stage);

	Audio::Init();

	// Hide the cursor
	SDL_ShowCursor(!mouse_locked); //hide or show the mouse
}

void Game::goToStage(eStages new_stage)
{
	
	Stage* stage = stages[new_stage];
	if (current_stage) {
		current_stage->onExit();

		current_stage = stage;

		current_stage->onEnter();
	}
}

//what to do when the image has to be draw
void Game::render(void)
{
	// Set the clear color (the background color)
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	current_stage->render();
	// Draw the floor grid
	//drawGrid();

	// Render the FPS, Draw Calls, etc
	//drawText(2, 2, getGPUStats(), Vector3(1, 1, 1), 2);

	// Swap between front buffer and back buffer
	SDL_GL_SwapWindow(this->window);
}

void Game::update(double seconds_elapsed)
{
	Camera* camera = Camera::current;
	float speed = seconds_elapsed * mouse_speed; //the speed is defined by the seconds_elapsed so it goes constant
	
	if(free_cam){
		// Example
		angle += (float)seconds_elapsed * 10.0f;

		// Mouse input to rotate the cam
		if (Input::isMousePressed(SDL_BUTTON_LEFT) || mouse_locked) //is left button pressed?
		{
			camera->rotate(Input::mouse_delta.x * 0.005f, Vector3(0.0f, -1.0f, 0.0f));
			camera->rotate(Input::mouse_delta.y * 0.005f, camera->getLocalVector(Vector3(-1.0f, 0.0f, 0.0f)));
		}

		// Async input to move the camera around
		if (Input::isKeyPressed(SDL_SCANCODE_LSHIFT)) speed *= 10; //move faster with left shift
		if (Input::isKeyPressed(SDL_SCANCODE_W) || Input::isKeyPressed(SDL_SCANCODE_UP)) camera->move(Vector3(0.0f, 0.0f, 1.0f) * speed);
		if (Input::isKeyPressed(SDL_SCANCODE_S) || Input::isKeyPressed(SDL_SCANCODE_DOWN)) camera->move(Vector3(0.0f, 0.0f, -1.0f) * speed);
		if (Input::isKeyPressed(SDL_SCANCODE_A) || Input::isKeyPressed(SDL_SCANCODE_LEFT)) camera->move(Vector3(1.0f, 0.0f, 0.0f) * speed);
		if (Input::isKeyPressed(SDL_SCANCODE_D) || Input::isKeyPressed(SDL_SCANCODE_RIGHT)) camera->move(Vector3(-1.0f, 0.0f, 0.0f) * speed);
	}
	current_stage->update(seconds_elapsed);
	/*
	Vector3 eye;
	Vector3 center;

	float orbit_dist = 0.8f;
	eye = space_ship->model.getTranslation();// -front * orbit_dist;
	center = space_ship->model.getTranslation();
	//World::instance->camera->lookAt(eye, center, Vector3(1.f, 1.f, 1.f));
	Matrix44 mYaw;*/
	
/*
	if (Input::isKeyPressed(SDL_SCANCODE_LSHIFT)) speed *= 10; //move faster with left shift
	if (Input::isKeyPressed(SDL_SCANCODE_W) || Input::isKeyPressed(SDL_SCANCODE_UP)) camera->move(Vector3(0.0f, 0.0f, 1.0f) * speed);
	if (Input::isKeyPressed(SDL_SCANCODE_S) || Input::isKeyPressed(SDL_SCANCODE_DOWN)) camera->move(Vector3(0.0f, 0.0f, -1.0f) * speed);
	if (Input::isKeyPressed(SDL_SCANCODE_A) || Input::isKeyPressed(SDL_SCANCODE_LEFT)) camera->move(Vector3(1.0f, 0.0f, 0.0f) * speed);
*/



}


//Keyboard event handler (sync input)
void Game::onKeyDown( SDL_KeyboardEvent event )
{
	switch(event.keysym.sym)
	{
		case SDLK_ESCAPE: must_exit = true; break; //ESC key, kill the app
		case SDLK_F1: Shader::ReloadAll(); break; 
		case SDLK_F5: free_cam = !free_cam;
	}
}

void Game::onKeyUp(SDL_KeyboardEvent event)
{

}

void Game::onMouseButtonDown( SDL_MouseButtonEvent event )
{
	current_stage->btnClick(event.button);
	if (event.button == SDL_BUTTON_MIDDLE) //middle mouse
	{
		mouse_locked = !mouse_locked;
		SDL_ShowCursor(!mouse_locked);
		SDL_SetRelativeMouseMode((SDL_bool)(mouse_locked));
	}

	if (event.button == SDL_BUTTON_LEFT)
	{
		
	}
}

void Game::onMouseButtonUp(SDL_MouseButtonEvent event)
{

}

void Game::onMouseWheel(SDL_MouseWheelEvent event)
{
	mouse_speed *= event.y > 0 ? 1.1f : 0.9f;
}

void Game::onGamepadButtonDown(SDL_JoyButtonEvent event)
{

}

void Game::onGamepadButtonUp(SDL_JoyButtonEvent event)
{

}

void Game::onResize(int width, int height)
{
	Camera* camera = Camera::current;

    std::cout << "window resized: " << width << "," << height << std::endl;
	glViewport( 0,0, width, height );
	camera->aspect =  width / (float)height;
	window_width = width;
	window_height = height;
}

