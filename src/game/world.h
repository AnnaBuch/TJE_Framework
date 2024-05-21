#pragma once

#include "framework/includes.h"
#include "framework/utils.h"
#include "graphics/material.h"
#include <map>

class Entity;
class EntityMesh;
class EntityPlayer;
class Camera;

class World {
public:
	static World* instance;
	
	Entity* root = nullptr;
	std::map<std::string, sRenderData> meshes_to_load;

	EntityMesh* skybox = nullptr;

	float sphere_radius;
	float sphere_ground_radius;
	EntityPlayer* player = nullptr; 

	World();
	//void render();

	//void update(double deltaTime);
	bool parseScene(const char* filename, EntityMesh* root, float translation);
};