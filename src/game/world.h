#pragma once

#include "framework/includes.h"
#include "framework/utils.h"
#include "graphics/material.h"
#include <map>

class Entity;
class Camera;

class World {
public:
	static World* instance;
	
	Entity* root = nullptr;
	std::map<std::string, sRenderData> meshes_to_load;
	Camera* camera = nullptr;

	float sphere_radius;
	float sphere_ground_radius;
	//EntityPlayer* player = nullptr; //TODO: implement player calss

	World(Camera* camera, Entity* root);
	//void render();

	//void update(double deltaTime);
	bool parseScene(const char* filename);
};