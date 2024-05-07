#include "entityPlayer.h"
#include "framework/camera.h"
#include "graphics/shader.h"
#include "graphics/mesh.h"
#include <algorithm>
#include "game/world.h"





void EntityPlayer::render()
{


	//render debug spheres: to check player collisions
	float sphere_radius = World::instance->sphere_radius;
	float sphere_ground_radius = World::instance->sphere_ground_radius;


	//To debug, make spheres visible

	//std::vector<sCollisionData> coliisions;


   
}



void EntityPlayer::update(float deltaTime)
{
	//TODO: Player move
	// 
	// 
	//TODO: Player collisions


}



