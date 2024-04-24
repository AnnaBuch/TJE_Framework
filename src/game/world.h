#pragma once

#include "framework/includes.h"
#include "framework/utils.h"
#include <graphics/material.h>
#include <map>

class Entity;
class Camera;

class World {
public:

	//TODO: move to world class DO NOT LEAVE HERE!!
	Entity* root = nullptr;
	std::map<std::string, sRenderData> meshed_to_load;
	Camera* camera = nullptr;
	//Player* player = nullptr; //TODO: implement player calss

	void world() {};
	void render() {};

	void update(double deltaTime);
};